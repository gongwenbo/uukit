//date 11.17 by gong

#include <stdio.h>                                                                                
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <uv.h>
#include <stdarg.h>

#define DEFAULT_PORT    8888
#define DEFAULT_BACKLOG 1024

uv_loop_t *loop = NULL;

int debug(const char* f,const int l,const char *format,...){
	va_list arg;
	va_start(arg,format);
	fprintf(stderr,"debug:func:%s line:%d:",f,l);
	vfprintf(stderr,format,arg);  /* 注意这里用的是vfprintf ,而不是printf */
	fprintf(stderr,"\n");

	va_end(arg);
	return 0;
}

void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf) {
    size = 1024;
    buf->base = (char*)malloc(size);
    buf->len = size;
}

void echo_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
    
    if (nread == UV_EOF) {
        printf("<EOF>\n");
    }
	debug(__func__,__LINE__,"echo_read:%s\n",buf->base);
    //printf("return data:%s\n", buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "on_new_connection(%p): error %s\n", server, uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
    } else {
        uv_close((uv_handle_t*)client, NULL);
    }
}

int main() {
    
	
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);
	
	struct sockaddr_in addr;
	
    printf("Running on port %d\n", DEFAULT_PORT);
    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);

    int r = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error: %s\n", uv_strerror(r));
        return 1;
    }

    struct timespec rqtp;
    while (true) {
        int ret = uv_run(loop, UV_RUN_NOWAIT);
        debug(__func__,__LINE__,"ret:%d\n",ret);
        rqtp.tv_sec = 0;
        rqtp.tv_nsec = 1000 * 1000 * 900;
        nanosleep(&rqtp, NULL);
    }
}    