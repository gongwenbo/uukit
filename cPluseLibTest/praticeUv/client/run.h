#ifndef RUN_H
#define RUN_H

#include "common.h"
#include "tcp_cli.h"
#include "timer_handle.h"


class RunEvClient{
	private:
		TcpCli* tcp_client_;
		TimerHandle* timer_handle_;
	public:
		RunEvClient(uv_loop_t* loop_r);
		~RunEvClient();
		int RunAll(uv_loop_t* loop_r);
			
	
};

#endif 


