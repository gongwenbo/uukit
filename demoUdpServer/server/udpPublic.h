#ifndef _UDP_PUBLIC_H
#define _UDP_PUBLIC_H


typedef struct _task_arg_struct
{
	int			bIdle;	
	pthread_t	taskID;
	int  		dateLen;
}TaskArg_T,*TaskArg_PT;

TaskArg_PT GetTaskArg(pthread_t threadID);


typedef struct _udp_server_struct
{
	unsigned int 	dwMagic;
	uv_udp_t		hUdp;
	unsigned short 	usListenPort;
}UdpSvr_T,*UdpSvr_PT;

UdpSvr_PT OpenUdpServer(uv_loop_t * pLoop,const unsigned short usListenPort,uv_udp_recv_cb rcv_cbfn);
int CloseUdpServer(UdpSvr_PT pInst);

void init_taskArg(void);
void deinit_taskArg(void);
#endif

