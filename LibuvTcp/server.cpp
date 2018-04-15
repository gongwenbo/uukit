/*
libuv服务端测试
2018-04-15
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <uv.h>
#include <iostream>
#define DEBUG 1

#ifdef DEBUG
#define LOG(fmt, params...)  printf("\x1b[33m" fmt "\x1b[0m\n", ## params)
#endif
#define LOGE(fmt, params...) fprintf(stderr, "\x1b[31m" fmt "\x1b[0m\n", ## params)

static uv_loop_t *loop;

typedef struct {
    uv_tcp_t handle;
    uv_write_t write_req;
} client_t;

void print_ip_port(client_t *client)
{
    char ip[17] = {0};
    struct sockaddr_in addr = {0};
    int alen = 0;

	//获取tcp对端ip和port
    uv_tcp_getsockname(&client->handle, (struct sockaddr *)&addr, &alen);
    uv_ip4_name((const struct sockaddr_in *)&addr, ip, sizeof(ip));
    LOGE("%s:%d", ip, addr.sin_port);
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

//读取tcp对端数据
void on_read(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf) {
    LOG("   [on_read]");

    client_t *client = (client_t *) tcp->data;
    print_ip_port(client);

    if (nread > 0) {
		std::cout<<"accept data:"<<buf->base<<"\n";

    } else if (nread < 0) {
		std::cout<<"error:recieve no data\n";
    }
}

void on_connect(uv_stream_t *server_handle, int status) {
    check("connect", status);

    client_t *client    = (client_t *) malloc(sizeof(client_t));
    uv_tcp_init(loop, &client->handle);
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
    check("listen",       uv_listen((uv_stream_t *) &server, 128, on_connect)); //监听服务

    LOG("listening on %s:%d", ip, port);
    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
    free(loop);
}

int main() {
    tcp_server_start("0.0.0.0", 8000);
    return 0;
}
