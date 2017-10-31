#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <uv.h>
#include <http_parser.h>
#include <string.h>
//#ifdef DEBUG
#define LOG(fmt, params...)  printf("\x1b[33m" fmt "\x1b[0m\n", ## params)
//#endif
#define LOGE(fmt, params...) fprintf(stderr, "\x1b[31m" fmt "\x1b[0m\n", ## params)

#define RESPONSE                   \
    "HTTP/1.1 200 OK\r\n"          \
    "Content-Type: text/plain\r\n" \
    "Content-Length: 12\r\n"       \
    "\r\n"                         \
    "hello world\n"


static uv_loop_t *loop;

typedef struct {
    uv_tcp_t handle;
    uv_write_t write_req;
    http_parser parser;
} client_t;

void print_ip_port(client_t *client)
{
    char ip[17] = {0};
    struct sockaddr_in addr = {0};
    int alen = 0;

    uv_tcp_getsockname(&client->handle, (struct sockaddr *)&addr, &alen);
    uv_ip4_name((const struct sockaddr_in *)&addr, ip, sizeof(ip));
    LOGE("client INFO:%s:%d", ip, addr.sin_port);
}

void check(const char *msg, int err)
{
    if (err) {
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(err));
        exit(1);
    }
}


void on_close(uv_handle_t *handle) {
    LOG("   [on_close]\n");
    client_t *client = (client_t *) handle->data;
    free(client);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    *buf = uv_buf_init((char *) malloc(suggested_size), suggested_size);
}


int on_http_body(http_parser *_, const char *at, size_t length)
{
    // TODO
    LOG("   [on_http_body]");
    LOG("%.*s", (int)length, at);
    return 0;
}

http_parser_settings *get_http_settings()
{
    static http_parser_settings *parser_settings = NULL;

    if (!parser_settings) {
        parser_settings = (http_parser_settings *)malloc(sizeof(http_parser_settings));
        memset(parser_settings, 0, sizeof(http_parser_settings));
        // parser_settings->on_url              = on_http_url;
        // parser_settings->on_header_field     = on_http_header_field;
        // parser_settings->on_header_value     = on_http_header_value;
        // parser_settings->on_headers_complete = on_http_headers_complete;
        parser_settings->on_body                = on_http_body;
    }

    return parser_settings;
}

int do_http_parse(http_parser *parser, const char *at, size_t length)
{
    http_parser_init(parser, HTTP_BOTH);

    size_t nparsed = http_parser_execute(parser, get_http_settings(), at, length);

    if (nparsed != length) {
        LOGE("%zu!=%zu: %s", nparsed, length, http_errno_description(HTTP_PARSER_ERRNO(parser)));
        return -1;
    }
    return 0;
}

void on_read(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf) {
    LOG("   [on_read]");

    int is_error = 0;
    client_t *client = (client_t *) tcp->data;
    print_ip_port(client);

    if (nread > 0) {
        // TODO: need append data and then parse
        is_error = do_http_parse(&client->parser, buf->base, nread);

        if (!is_error) {
            uv_buf_t send_bufs[] = {
                //{ .len  = strlen(RESPONSE), .base = RESPONSE }
					{RESPONSE,strlen(RESPONSE)}
			};
            uv_write(&client->write_req, tcp, send_bufs, sizeof(send_bufs)/sizeof(uv_buf_t), NULL);
        } else {
            LOGE("HTTP parse error");
        }
    } else if (nread < 0) {
        if (nread == UV_EOF) {
            LOG("EOF[%zd]: client closed", nread);
        } else {
            LOGE("nread < 0: %zd", nread);
        }
        is_error = 1;
    }

    if (buf->base)
        free(buf->base);
    else if (buf->len == 0)
        is_error = 1;

    if (is_error)
        uv_close((uv_handle_t *) &client->handle, on_close);
}


void on_connect(uv_stream_t *server_handle, int status) {
    LOG("   [on_connect]");
    check("connect", status);

    client_t *client    = (client_t *) malloc(sizeof(client_t));
    uv_tcp_init(loop, &client->handle);
    client->parser.data = client;
    client->handle.data = client;

    check("accept", uv_accept(server_handle, (uv_stream_t *) &client->handle));

    uv_read_start((uv_stream_t *) &client->handle, alloc_buffer, on_read);
}

void tcp_server_start(const char *ip, int port)
{
    struct sockaddr_in addr;
    uv_tcp_t server;
    loop = uv_default_loop();

    check("tcp_init",     uv_tcp_init(loop, &server));
    check("Ipv4 convert", uv_ip4_addr(ip, port, &addr));
    check("tcp_bind",     uv_tcp_bind(&server, (const struct sockaddr *) &addr, 0));
    check("listen",       uv_listen((uv_stream_t *) &server, 128, on_connect));

    LOG("listening on %s:%d", ip, port);
    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
    free(loop);
}

int main() {
    tcp_server_start("0.0.0.0", 8000);
    return 0;
}