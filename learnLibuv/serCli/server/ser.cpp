//date 11.17 by gong

#include "tcp_sock.h"
#include "log.h"
using namespace std;

uv_loop_t *loop = NULL;

int main() {
    	
	cout<<"start ser!"<<endl;
	
	loop = uv_default_loop();
	uv_tcp_t server;	
	TcpInit(&server,loop);

    struct timespec rqtp;
    while (true) {
        int ret = uv_run(loop, UV_RUN_NOWAIT);
        //debug(__func__,__LINE__,"ret:%d\n",ret);
        rqtp.tv_sec = 0;
        rqtp.tv_nsec = 1000 * 1000 * 900;
        nanosleep(&rqtp, NULL);
    }
} 


