#ifndef TCP_SOCK_H
#define TCP_SOCK_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include <uv.h>
#include <stdarg.h>
#include <iostream>
#include "log.h"

extern uv_loop_t *loop ;

#define DEFAULT_PORT    8888
#define DEFAULT_BACKLOG 1024

void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf);
void echo_read(uv_stream_t *client_stream, ssize_t nread, const uv_buf_t *buf);
void on_write_end(uv_write_t *req, int status);
void on_new_connection(uv_stream_t *server, int status);
int TcpInit(uv_tcp_t* server_socket,uv_loop_t* loop);

#endif 





