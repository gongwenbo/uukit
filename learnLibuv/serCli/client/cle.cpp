#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <iostream>
using namespace std;

void debuf(char* msg) {
	printf("%s::%d:%s\n", __func__,__LINE__,msg);
}

void on_connect(uv_connect_t *req, int status);
void on_write_end(uv_write_t *req, int status);

void echo_read(uv_stream_t *server, ssize_t nread, const uv_buf_t* buf) {
  if (nread == -1) {
    fprintf(stderr, "error echo_read");
    return;
  }

  printf("result: %s\n", buf->base);
}

void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf) {
    size = 1024;
    printf("alloc_buffer(%zd)\n", size);
    buf->base = (char*)malloc(size);
    buf->len = size;
}


void on_write_end(uv_write_t *req, int status) {
  if (status == -1) {
    fprintf(stderr, "error on_write_end");
    return;
  }

  uv_read_start(req->handle, alloc_buffer, echo_read);
}

void on_connect(uv_connect_t *req, int status) {
	if (status == -1) {
		fprintf(stderr, "error on_write_end");
		return;
	}	

	char message[20] = "hello.txt";
	int len = strlen(message);

	/*
   * uv_buf_t buf[1];
   * buf[0].len = len;
   * buf[0].base = message;
   */

	char buffer[100];
	uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));
	buf.len = len;
	buf.base = message;

	uv_stream_t* tcp = req->handle;

	uv_write_t write_req;

	int buf_count = 1;
  
	uv_write(&write_req, tcp, &buf, buf_count, on_write_end);
}

int main(void) {

  
	uv_tcp_t client;
	uv_loop_t *loop;
	loop = uv_default_loop();
	uv_tcp_init(loop, &client);

	struct sockaddr_in req_addr;
	uv_ip4_addr("127.0.0.1",8888,&req_addr);

	uv_connect_t connect_req;
	uv_tcp_connect(&connect_req, &client, (const struct sockaddr*)&req_addr, on_connect);

	return uv_run(loop,UV_RUN_DEFAULT);
}