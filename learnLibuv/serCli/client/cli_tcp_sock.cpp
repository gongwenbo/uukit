#include "cli_tcp_sock.h"
using namespace std;
int debug(const char* f,const int l,const char *format,...){
	va_list arg;
	va_start(arg,format);
	fprintf(stderr,"debug:func:%s line:%d:",f,l);
	vfprintf(stderr,format,arg);  /* 注意这里用的是vfprintf ,而不是printf */
	fprintf(stderr,"\n");

	va_end(arg);
	return 0;
}

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
  cout<<"on_write_end"<<endl;
  
}

void AfterWork(uv_work_t *req,int status){

	fprintf(stderr,"complite AfterWork\n");


}

void DataRS(uv_work_t *req){

	uv_stream_t* tcp_back=(uv_stream_t*)req->data;
	uv_write_t *write_req=(uv_write_t*)malloc(sizeof(uv_write_t));	
	char message[20] = "hello.txt";
	int len = strlen(message);
	char buffer[100];
	int buf_count = 1;	
	uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));
	
	buf.len = len;
	buf.base = message;
	
	uv_write(write_req, tcp_back, &buf, buf_count, on_write_end);
	free(write_req);
}

void on_connect(uv_connect_t *req, int status) {
	if (status == -1) {
		fprintf(stderr, "error on_write_end");
		return;
	}	
	//uv_stream_t* tcp;
	//tcp= req->handle;
	#if 0
	uv_write_t write_req;
	char message[20] = "hello.txt";
	int len = strlen(message);
	char buffer[100];
	int buf_count = 1;
	
	uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));
	buf.len = len;
	buf.base = message;
	
	uv_write(&write_req, tcp, &buf, buf_count, on_write_end);
	#endif
	
	req_work.data=(void*)(req->handle);
		
}

void timer_cb(uv_timer_t* handle){

	debug(__func__,__LINE__,"timer_cb test");
	uv_queue_work(loop,&req_work,DataRS,AfterWork);

}


