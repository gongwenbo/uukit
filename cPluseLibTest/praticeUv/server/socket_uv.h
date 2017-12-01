#define DEFAULT_PORT    8888
#define DEFAULT_BACKLOG 1024

#include "common.h"

class TcpHandle{
	private:
		uv_tcp_t* server_;
	public:
		TcpHandle();
		~TcpHandle();
		int TcpInit(uv_loop_t* loop);
		static void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf);
		static void echo_read(uv_stream_t *client_stream, ssize_t nread, const uv_buf_t *buf);
		static void on_write_end(uv_write_t *req, int status);
		static void on_new_connection(uv_stream_t *server, int status);
		
};

class RunLoop{

	private:
		struct timespec rqtp;
		TcpHandle* tcp_del_;
	public:
		RunLoop();
		~RunLoop();
		int Runner(uv_loop_t* loop);

};



