#include "stdafx.h"
#include <uv.h>
#include "rcvMsg.h"
#include "udpPublic.h"


typedef struct _udp_task_struct
{
	uv_work_t hWork;
	unsigned int seqNum;
	unsigned int respCode;
	struct sockaddr rmtAddr;
	int  dateLen;
	U8 	pData[4];
}UdpRcvTask_T,*UdpRcvTask_PT;



static void work_cbfn(uv_work_t* req)
{
	UdpRcvTask_PT pTask = (UdpRcvTask_PT)req;
	TaskArg_PT pArg = GetTaskArg(pthread_self());

	if(NULL == pArg)
	{
		fprintf(stderr,"ERROR\n");
	}

	fprintf(stderr, "A-A[%u]::[%u]task multask_work recv %d data at %s_%d\n",pthread_self(),pTask->seqNum,pTask->dateLen, __FILE__,__LINE__);
}
static void after_work_cbfn(uv_work_t* req, int status)
{
	UdpRcvTask_PT pTask = (UdpRcvTask_PT)req;
	
	fprintf(stderr, "A-B[%u]::[%u] multask_after_work recv %d data at %s_%d\n",pthread_self(),pTask->seqNum,pTask->dateLen, __FILE__,__LINE__);
	mkfree(pTask);
}


void on_app_read(uv_udp_t *req, ssize_t nread, const uv_buf_t * pBuf, const struct sockaddr *addr, unsigned flags) 
{
	unsigned int sum =0;
	if(nread > 0)
	{
		UdpRcvTask_PT pTask = (UdpRcvTask_PT)mkmalloc(sizeof(UdpRcvTask_T)+nread);
		pTask->seqNum = sum;
		pTask->hWork.data = req;
		memcpy(&(pTask->rmtAddr),addr,sizeof(struct sockaddr));
		pTask->dateLen = nread;
		memcpy(pTask->pData,pBuf->base,nread);
		uv_queue_work(req->loop,(uv_work_t *)pTask,work_cbfn,after_work_cbfn);
	}
}

