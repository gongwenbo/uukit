//date 11.15 by gong

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <assert.h>
#define BUFBACK 1
using namespace std;

uv_loop_t *loop;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size,uv_buf_t* buf) {
  //uv_buf_t* buf=uv_buf_init((char*) malloc(suggested_size), suggested_size);
	buf->base = (char*)malloc(suggested_size);
	assert(buf->base != NULL);
	buf->len = suggested_size;  
}

void echo_write(uv_write_t *req, int status) {
  if (status == -1) {
    fprintf(stderr, "Write error!\n");
  }
  
  char *base = (char*) req->data;
  cout<<"base:"<<base<<endl;
  free(base);
  free(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf) {
  	if (nread == -1) {
    	fprintf(stderr, "Read error!\n");
    	uv_close((uv_handle_t*)client, NULL);
    	return;
 	 }

  	uv_write_t *write_req = (uv_write_t*)malloc(sizeof(uv_write_t));
  	write_req->data = (void*)buf->base;
  	cout<<__FILE__<<"::"<<__FUNCTION__<<":"<<__LINE__<<":->"<<"echo_read:"<<buf->base<<endl;
		
  	uv_buf_t buf_back[BUFBACK];
	
  	//strcpy(buf_back[0].base,(const char*)write_req->data);
  	cout<<"(const char*)write_req->data:"<<(const char*)write_req->data<<endl;
 	buf_back[0].len = nread;
	char temp[50];
	sprintf(temp,"test server");
	buf_back[0].base=temp;
  
  	uv_write(write_req, client, buf_back, BUFBACK, echo_write);
  	
}

void on_new_connection(uv_stream_t *server, int status) {
  if (status == -1) {
    return;
  }

  uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

int main() {
  	loop = uv_default_loop();
  	uv_tcp_t server;
  	uv_tcp_init(loop, &server);

  	struct sockaddr_in bind_addr;
  	uv_ip4_addr("0.0.0.0", 8888,&bind_addr);
  	uv_tcp_bind(&server, (const struct sockaddr*)&bind_addr,0);
  	int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);
  	if (r) {
    	fprintf(stderr, "Listen error!\n");
    	return 1;
  	}
  	return uv_run(loop, UV_RUN_DEFAULT);
}

