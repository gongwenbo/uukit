#include "common.h"

uv_loop_t* loop=uv_default_loop();
uv_work_t req_work;

int main(int argc,char* argv[]){

	RunEvClient* run_ev_client=new RunEvClient(loop);
	run_ev_client->RunAll(loop);
	//while (true);
	//delete run_ev_client;
	
}


