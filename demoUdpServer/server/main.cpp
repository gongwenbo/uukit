#include "stdafx.h"
#include <uv.h>

#include "udpPublic.h"
#include "udpDevSvr.h"
#include "udpAppSvr.h"

static uv_loop_t *g_pLoop;

unsigned short g_usAppPort = 9999;
unsigned short g_usDevPort = 8888;
UdpSvr_PT g_pAppSvr=NULL;
UdpSvr_PT g_pDevSvr=NULL;

static uv_signal_t g_hSig;
void signal_cb(uv_signal_t* handle, int signum)
{
	printf("signal_cb(%d)\n",signum);

	switch(signum)
	{
	case SIGINT:
		uv_stop(g_pLoop);
		break;
	}
}


int main(int argc,char **argv)
{
	int ret = 0;
	int i=0;

	if(argc <=2)
	{
		printf("input:1- app listen port,2- dev listen port\n");
	//	return 0;
	}

	if(argc > 2)
	{
		g_usAppPort = atoi(argv[1]);
		g_usDevPort = atoi(argv[2]);
		

		printf("input:%u,%u\n",g_usAppPort,g_usDevPort);
	}

	init_taskArg();

	g_pLoop = uv_loop_new();

	uv_signal_init(g_pLoop,&g_hSig);
	uv_signal_start(&g_hSig,signal_cb,SIGINT);

	g_pAppSvr = OpenUdpServer(g_pLoop,g_usAppPort,on_app_read);
	g_pDevSvr = OpenUdpServer(g_pLoop,g_usDevPort,on_dev_read);
	
	uv_run(g_pLoop, UV_RUN_DEFAULT);
	
	uv_signal_stop(&g_hSig);
	uv_loop_close(g_pLoop);

	CloseUdpServer(g_pAppSvr);
	CloseUdpServer(g_pDevSvr);
	deinit_taskArg();
	printf("program EXIT\n");
	return ret ;
}