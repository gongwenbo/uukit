#include "stdafx.h"
#include <uv.h>
#include "udpPublic.h"

#include "rcvMsg.h"

typedef struct _udp_task_struct
{
	uv_work_t hWork;
	unsigned int seqNum;
	unsigned int respCode;
	struct sockaddr rmtAddr;
	int  dateLen;
	U8 	pData[4];
}UdpRcvTask_T,*UdpRcvTask_PT;


static uv_udp_send_t _hDevSnd;

static NetMsgHeader_t	stMsg;




static void work_cbfn(uv_work_t* req)
{
	UdpRcvTask_PT pTask = (UdpRcvTask_PT)req;
	TaskArg_PT pArg = GetTaskArg(pthread_self());

	if(NULL == pArg)
	{
		fprintf(stderr,"ERROR\n");
		return ;
	}
	//NetMsgHeader_t *message_from_dev=(NetMsgHeader_t*)pTask.pData;
	//sprintf("message_from_dev:%s",message_from_dev.dwSrcSessionID);
	
	
	fprintf(stderr, "D-A[%u]::[%u]task multask_work recv %d data at %s_%d\n",pthread_self(),pTask->seqNum,pTask->dateLen, __FILE__,__LINE__);
}
static void after_work_cbfn(uv_work_t* req, int status)
{
	UdpRcvTask_PT pTask = (UdpRcvTask_PT)req;
	
	fprintf(stderr, "D-B[%u]::[%u] multask_after_work recv %d data at %s_%d\n",pthread_self(),pTask->seqNum,pTask->dateLen, __FILE__,__LINE__);
	mkfree(pTask);
}

static void my_snd_cbfn(uv_udp_send_t* req, int status)
{
	printf("my_snd_cbfn(%d)\n",status);
}

void on_dev_read(uv_udp_t *req, ssize_t nread, const uv_buf_t * pBuf, const struct sockaddr *addr, unsigned flags) 
{
	unsigned int sum =0;
	if(nread > 0)
	{
		if(nread!= sizeof(NetMsgHeader_t))
		{
			//
			static U32 dwTmp = 0;
			memcpy(&stMsg,pBuf->base,nread);
			dwTmp = stMsg.dwSrcSessionID;
			stMsg.dwSrcSessionID = stMsg.dwDesSessionID ;
			stMsg.dwDesSessionID = dwTmp;
			stMsg.dwTransNumber |=0x80000000;
		}
		uv_buf_t stBuf;
		UdpRcvTask_PT pTask = (UdpRcvTask_PT)mkmalloc(sizeof(UdpRcvTask_T)+nread);
		pTask->seqNum = sum;
		memcpy(&(pTask->rmtAddr),addr,sizeof(struct sockaddr));
		pTask->dateLen = nread;
		memcpy(pTask->pData,pBuf->base,nread);
		uv_queue_work(req->loop,(uv_work_t *)pTask,work_cbfn,after_work_cbfn);
		stBuf.base = (char*)&stMsg;
		stBuf.len = nread;
		uv_udp_send(&_hDevSnd,req,&stBuf,1,addr,my_snd_cbfn);

		
	}
}

