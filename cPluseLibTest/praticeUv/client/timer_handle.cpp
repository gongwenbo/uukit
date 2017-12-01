#include "common.h"

using namespace std;
TimerHandle::TimerHandle(uv_loop_t* loop_p){

	cout<<"TimerHandle!"<<endl;
	timer_=new uv_timer_t();
	uv_timer_init(loop_p,timer_);

}

TimerHandle::~TimerHandle(){

	cout<<"delete timerHandle!"<<endl;
	delete timer_;

}

void TimerHandle::AfterWork(uv_work_t *req,int status){

	fprintf(stderr,"complite AfterWork\n");

}

void TimerHandle::DataRS(uv_work_t *req){

	uv_stream_t* tcp_back=(uv_stream_t*)req->data;
	uv_write_t *write_req=(uv_write_t*)malloc(sizeof(uv_write_t));	
	char message[20] = "hello.txt";
	int len = strlen(message);
	char buffer[100];
	int buf_count = 1;	
	uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));
	
	buf.len = len;
	buf.base = message;
	
	uv_write(write_req, tcp_back, &buf, buf_count, TimerHandle::on_write_end);
	free(write_req);
}

void TimerHandle::TimerCallBack(uv_timer_t* handle){

	Log::debug(__func__,__LINE__,"timer_cb test");
	uv_queue_work(loop,&req_work,TimerHandle::DataRS,TimerHandle::AfterWork);
	

}

int TimerHandle::RunTimer(){

	uv_timer_start(timer_, TimerHandle::TimerCallBack, 0, 1000);
	Log::debug(__func__,__LINE__,"TimerHandle::RunTimer");	
	return 0;

}

void TimerHandle::on_write_end(uv_write_t *req, int status){

	if (status == -1) {
	  fprintf(stderr, "error on_write_end");
	  return;
	}
	
	uv_read_start(req->handle, TimerHandle::alloc_buffer, TimerHandle::echo_read);
	cout<<"on_write_end"<<endl;

}


void TimerHandle::echo_read(uv_stream_t *server, ssize_t nread, const uv_buf_t* buf) {
  if (nread == -1) {
    fprintf(stderr, "error echo_read");
    return;
  }

  printf("result: %s\n", buf->base);
}

void TimerHandle::alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf) {
    size = 1024;
    printf("alloc_buffer(%zd)\n", size);
    buf->base = (char*)malloc(size);
    buf->len = size;
}


