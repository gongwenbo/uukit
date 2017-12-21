#include "stdafx.h"
#include <uv.h>
#include "udpPublic.h"
#include "rcvMsg.h"

static TaskArg_PT	g_arTaskArg =NULL;
static unsigned int g_nthreads = 8;
static int			g_curTasks = 0;

void init_taskArg(void)
{
	const char* val;
	val = getenv("UV_THREADPOOL_SIZE");
  	if (val != NULL)
    	g_nthreads = atoi(val);

	g_arTaskArg = (TaskArg_PT)mkmalloc(sizeof(TaskArg_T) * g_nthreads);
}

void deinit_taskArg(void)
{
	if(g_arTaskArg)
	{
		mkfree(g_arTaskArg);
		g_arTaskArg = NULL;
	}
}

TaskArg_PT GetTaskArg(pthread_t threadID)
{
	int i=0;
	TaskArg_PT pInst = g_arTaskArg;
	
	for(i=0;i<g_nthreads;i++)
	{
		if(1 == pInst->bIdle)
		{
			if(pInst->taskID == threadID)
			{
				return pInst;
			}
			else
			{
				pInst++;
			}
		}
		else
		{
			pInst->taskID = threadID;
			pInst->bIdle = 1;
			// ³õÊ¼»¯ redis
			return pInst;
		}
	}
	return NULL;
}


static void alloc_buffer(uv_handle_t *handle, size_t suggested_size,uv_buf_t * pBuf) 
{
	static unsigned long g_mallocIndex=0;
	static char _allBuffer[PUB_READ_BUF_SIZE];
	
	g_mallocIndex++;
	
	pBuf->len = PUB_READ_BUF_SIZE;
	pBuf->base = _allBuffer;
	
//	printf("[%ld]:alloc_buffer(%d,%x)\n",g_mallocIndex,suggested_size,(unsigned long)pBuf->base);
}

UdpSvr_PT OpenUdpServer(uv_loop_t * pLoop,const unsigned short usListenPort,uv_udp_recv_cb rcv_cbfn)
{
	UdpSvr_PT pInst = NULL;
	pInst = (UdpSvr_PT)malloc(sizeof(UdpSvr_T));

	assert(pInst!=NULL);
	memset(pInst,0,sizeof(UdpSvr_T));
	pInst->dwMagic = MY_UDPS_MAGIC;
	pInst->usListenPort = usListenPort;
	uv_udp_init(pLoop, &(pInst->hUdp));
	struct sockaddr_in bind_addr ;
	uv_ip4_addr("0.0.0.0", usListenPort,&bind_addr);
	uv_udp_bind(&(pInst->hUdp), (const sockaddr*)&bind_addr, 0);
    uv_udp_recv_start(&(pInst->hUdp), alloc_buffer, rcv_cbfn);

	return pInst;
}
int CloseUdpServer(UdpSvr_PT pInst)
{
	uv_close((uv_handle_t*) &(pInst->hUdp), NULL);

	return 0;
}