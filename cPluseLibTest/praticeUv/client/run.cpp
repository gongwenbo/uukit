#include "common.h"

RunEvClient::RunEvClient(uv_loop_t* loop_r){

	tcp_client_=new TcpCli(loop_r);
	timer_handle_=new TimerHandle(loop_r);

}

RunEvClient::~RunEvClient(){
	
	delete tcp_client_;
	delete timer_handle_;

}

int RunEvClient::RunAll(uv_loop_t* loop_r){

	timer_handle_->RunTimer();
	Log::debug(__func__,__LINE__,"RunEvClient::RunAll");
	uv_run(loop_r,UV_RUN_DEFAULT);  //start loop
	return 0;

}

