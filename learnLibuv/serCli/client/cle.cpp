#include "cli_tcp_sock.h"

using namespace std;  

uv_loop_t *loop;
uv_timer_t tim_loop;
uv_tcp_t client;
struct sockaddr_in req_addr;
uv_connect_t connect_req;
uv_work_t req_work;

int main(void) {
  
	loop = uv_default_loop();
	uv_tcp_init(loop, &client);
	uv_timer_init(loop,&tim_loop);
	
	uv_ip4_addr("127.0.0.1",8888,&req_addr);
	uv_tcp_connect(&connect_req, &client, (const struct sockaddr*)&req_addr, on_connect);
	
	uv_timer_start(&tim_loop, timer_cb, 0, 1000);
		
	return uv_run(loop,UV_RUN_DEFAULT);
}



