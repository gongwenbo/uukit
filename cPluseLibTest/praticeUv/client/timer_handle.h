#ifndef TIMER_HANDLE_H
#define TIMER_HANDLE_H
#include "common.h"
class TimerHandle{

	private:
		uv_timer_t* timer_;
	public:
		TimerHandle(uv_loop_t* loop_p);
		~TimerHandle();
		static void AfterWork(uv_work_t *req,int status);
		static void DataRS(uv_work_t *req);
		static void TimerCallBack(uv_timer_t* handle);
		static void on_write_end(uv_write_t *req, int status);
		static void echo_read(uv_stream_t *server, ssize_t nread, const uv_buf_t* buf);
		static void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf);
		int RunTimer();
};

#endif






