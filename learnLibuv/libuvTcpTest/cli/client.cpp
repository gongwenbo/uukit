//data 11.16 by gong
#include <stdio.h>
#include <uv.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <assert.h>
using namespace std;

static void on_close(uv_handle_t* handle);
static void on_connect(uv_connect_t* req, int status);
static void on_write(uv_write_t* req, int status);

static uv_loop_t *loop;

void alloc_cb(uv_handle_t *handle, size_t suggested_size,uv_buf_t* buf) {
  	//buf=uv_buf_init((char*) malloc(suggested_size), suggested_size);
	buf->base = (char*)malloc(suggested_size);
	assert(buf->base != NULL);
	buf->len = suggested_size;  
}

void on_close(uv_handle_t* handle)
{
  printf("closed.");
}

void on_write(uv_write_t* req, int status)
{
  if (status) {
    //uv_err_t err = uv_last_error(loop);
    fprintf(stderr, "uv_write error\n");
		return;
  }
	printf("wrote.\n");
	//uv_close((uv_handle_t*)req->handle, on_close);
}

void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
	cout<<"test on_read"<<endl;
	if(nread >= 0) {
		printf("read: %s\n", buf->base);
		printf("read size:%d\n",buf->len);
	}
	else {
		cout<<"on_read error"<<endl;
    	uv_close((uv_handle_t*)tcp, on_close);
	}

	free(buf->base);
}

void on_connect(uv_connect_t* connection, int status)
{
	printf("connected.\n");

	uv_stream_t* stream = connection->handle;

	uv_buf_t buffer[] = {
		{.base = "hello", .len = 5},
		{.base = "world", .len = 5}
	};

	uv_write_t request;

	uv_write(&request, stream, buffer, 2, on_write);
	uv_read_start(stream, alloc_cb, on_read);
	
}


int main(int argc, char **argv) {
	loop = uv_default_loop();

	uv_tcp_t socket;
	uv_tcp_init(loop, &socket);
	uv_tcp_keepalive(&socket, 1, 60);

	struct sockaddr_in dest;
	uv_ip4_addr("0.0.0.0", 8888,&dest);

	uv_connect_t connect;
	uv_tcp_connect(&connect, &socket, (struct sockaddr*)&dest, on_connect);
	
  uv_run(loop, UV_RUN_DEFAULT);
}










