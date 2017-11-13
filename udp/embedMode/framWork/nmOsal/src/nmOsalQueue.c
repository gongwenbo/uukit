#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>

#include <assert.h>
#include <errno.h>
#include <semaphore.h>
#include "nmOsalType.h"
#include "nmOsalPublicFun.h"

#define	OSAL_QUEUE_MAGIC 	0xF005001

typedef struct _nmOsalQueue_struct *nmOsalQueue_pt;

typedef struct _nmOsalQueue_struct
{
	NM_U32			magic;	//magic
	NM_U32			maxNrPackets;		/* indicates the total amount of packets */
	NM_U32			maxPacketSize;		/* each packet will have this size		 */
	NM_U32			writeIndex; 		/* index where to put packet			 */
	NM_U32			readIndex;			/* index where to get packet			 */
	sem_t			sndSem; 			/* semaphore for putting a packet on the */
	sem_t			rcvSem; 			/* semaphore for getting a packet from */
	NM_U32			*dataSize;			/* 'array' of fillrate of packet		 */
	NM_Address		packet;				/* 'array' of packets					 */
	nmOsalQueue_pt	pPrev;
	nmOsalQueue_pt	pNext;
} nmOsalQueue_t;


static nmOsalQueue_pt gpOsalQueueList = NULL;


static void OsalQueueAddHandle(
	nmOsalQueue_pt pHandle
	)
{

	NM_OSAL_ENTER_CR(); 						  /* ENTER CR */
	if (NULL != gpOsalQueueList)
		gpOsalQueueList->pPrev = pHandle;

	pHandle->pNext	  = gpOsalQueueList;
	pHandle->pPrev	  = NULL;
	gpOsalQueueList = pHandle;
	NM_OSAL_EXIT_CR();							  /* LEAVE CR */
}

static void OsalQueueDeleteHandle(
	nmOsalQueue_pt pHandle
	)
{
	NM_OSAL_ENTER_CR(); 						  /* ENTER CR */

	/* check if it is the first element */
	if (NULL == pHandle->pPrev)
		gpOsalQueueList = pHandle->pNext;
	else
		pHandle->pPrev->pNext = pHandle->pNext;

	/* check if it is not the last element */
	if (NULL != pHandle->pNext)
		pHandle->pNext->pPrev = pHandle->pPrev;

	NM_OSAL_EXIT_CR();							  /* LEAVE CR */
}

unsigned long q_vcreate(
			NM_String				strName,		/* I: name of the queue 	*/
			unsigned long			flags,			/* I: reserved			*/
			unsigned long			maxPackets, /* I: queue size in packets */
			unsigned long			maxPacketSize, /* I: packet size in bytes	*/
			unsigned long			*pQueueHandle	/* O: handle pointer		*/
		)


	
{
	unsigned long		returnVal = NM_OK;
	nmOsalQueue_pt		pQueue = NULL;
	int 				r;
	
	*pQueueHandle = NULL;
	pQueue	= (nmOsalQueue_pt) malloc(sizeof (nmOsalQueue_t));
	assert(NULL != pQueue);
	memset(pQueue,0,sizeof(nmOsalQueue_t));
	pQueue->magic = OSAL_QUEUE_MAGIC;
	pQueue->dataSize = (NM_U32 *) malloc(maxPackets * sizeof (NM_U32));
	assert(NULL != (pQueue->dataSize));
	pQueue->packet	 = (NM_Address ) malloc(maxPackets * maxPacketSize);
	assert(NULL != (pQueue->packet));
	
	r = sem_init(&pQueue->sndSem, 0, maxPackets);
	assert(!r);

	if (r == 0)
	{
		r = sem_init(&pQueue->rcvSem, 0, 0);
		assert(!r);

		if (r == 0)
		{
			/* created both semaphores */
			pQueue->maxNrPackets  = maxPackets;
			pQueue->maxPacketSize = maxPacketSize;
			pQueue->writeIndex	  = 0;
			pQueue->readIndex	  = 0;

			OsalQueueAddHandle(pQueue);

			*pQueueHandle = (unsigned long)pQueue;
		}
		else
		{
			/* failed to create second semaphore */
			r = sem_destroy(&pQueue->rcvSem);
			assert(!r);

			free(pQueue->dataSize);
			free(pQueue->packet);
			free(pQueue);
			returnVal = NM_ERR_FAULT;//TMOSAL_ERR_QUE_FULL;
		}
	}
	else
	{
		/* failed to create first semaphore */
		free(pQueue->dataSize);
		free(pQueue->packet);
		free(pQueue);
		returnVal = NM_ERR_FAULT;//TMOSAL_ERR_QUE_FULL;
	}

	return (returnVal);
}


unsigned long q_vdelete(unsigned long Handle)
{
	unsigned long		returnVal = NM_OK;
	nmOsalQueue_pt		pQueue = NULL;

	pQueue = (nmOsalQueue_pt)Handle;

	OsalQueueDeleteHandle((nmOsalQueue_pt)Handle);

	if(0!=sem_destroy(&pQueue->rcvSem))
	{
		returnVal = NM_ERR_FAULT;
	}
	if(0!=sem_destroy(&pQueue->sndSem))
	{
		returnVal = NM_ERR_FAULT;
	}
	free(pQueue->dataSize);
	free(pQueue->packet);
	free(pQueue);
	return (returnVal);
}

inline BOOL nmOsalQueue_send(
		nmOsalQueue_pt		pQueue
		,const void *			pBuffer
		,NM_U32				PacketSize
	)
{
	NM_Address 		packet;
	BOOL 				bRet = TRUE;
	
	NM_OSAL_ENTER_CR();	/* ENTER CR */
	if( PacketSize > (pQueue->maxPacketSize) )
	{
		bRet = FALSE;
	}
	else
	{
		pQueue->dataSize[pQueue->writeIndex] = PacketSize;
		
		/* find packet in queue */
		packet = pQueue->packet + (pQueue->writeIndex * pQueue->maxPacketSize);
		memcpy(packet, pBuffer, PacketSize);
		pQueue->writeIndex = (pQueue->writeIndex + 1) % pQueue->maxNrPackets;
	}
	NM_OSAL_EXIT_CR();		/* EXIT CR */
	return bRet;
}

unsigned long q_vsend(
			  unsigned long 			Handle, 		/* I: queue handle	  */
			  const void				*pBuffer,	/* I: packet pointer	*/
			  unsigned long 			packetSize
	)
{
	unsigned long			returnVal = NM_OK;
	nmOsalQueue_pt			pQueue = NULL;
	int 		r;
	
	pQueue = (nmOsalQueue_pt)Handle;

	assert(OSAL_QUEUE_MAGIC == pQueue->magic);
	/*On Linux we do not timeout... */
	r = sem_wait(&pQueue->sndSem);
	assert(!r);

	if (r == 0)
	{
		nmOsalQueue_send(pQueue,pBuffer,packetSize);
		
		r = sem_post(&pQueue->rcvSem);
		assert(!r);
	}
	else
	{
		returnVal = NM_ERR_FAULT;
	}
	return (returnVal);
}


inline unsigned long nmOsalQueue_recv(
		nmOsalQueue_pt		pQueue
		,NM_Pointer			pBuffer
		,NM_U32				dwBufSize
	)
{
	NM_Address 		packet;
	NM_U32				dwPacketSize ;
	unsigned long 		dwMsgLen = 0;
	
	NM_OSAL_ENTER_CR();	/* ENTER CR */
	dwPacketSize = pQueue->dataSize[pQueue->readIndex];
	if( dwBufSize <dwPacketSize)
	{
		dwMsgLen = 0;
	}
	else
	{
		packet = pQueue->packet + (pQueue->readIndex * pQueue->maxPacketSize);
		memcpy(pBuffer, packet, dwPacketSize);
		dwMsgLen = dwPacketSize;
		pQueue->readIndex = (pQueue->readIndex + 1) % pQueue->maxNrPackets;
	}
	NM_OSAL_EXIT_CR();		/* EXIT CR */
	return dwMsgLen;
}

unsigned long q_vreceive(
			unsigned long		Handle, 			/* I: queue handle	  */
			unsigned long		flags,
			unsigned long		timeout,
			void					*pBuffer,	/* I: packet pointer	*/
			unsigned long		dwBufLen,
			unsigned long		*pMsgLen
	)
{
	NMRESULT				returnVal = NM_ERR_TIMEOUT;
	nmOsalQueue_pt			pQueue = NULL;
	int 		r;
	unsigned long recvMsgLen = 0;
	
	pQueue = (nmOsalQueue_pt)Handle;
	assert(OSAL_QUEUE_MAGIC == pQueue->magic);
	assert(NULL != pMsgLen);
	
	if(NMOSAL_WAIT == flags)//×èÈûµÈ
	{
		if(0 == timeout)
		{
			r = sem_wait(&pQueue->rcvSem);
			assert(!r);
			if(0 == r)
			{
				recvMsgLen = nmOsalQueue_recv(pQueue,pBuffer,dwBufLen);
				r = sem_post(&pQueue->sndSem);
				assert(!r);

				*pMsgLen = recvMsgLen;
				returnVal = NM_OK;
			}
			else
			{
				returnVal = NM_ERR_FAULT;
			}
		}
		else
		{
			while (timeout > 0)
			{
				r = sem_trywait(&(pQueue->rcvSem));
				if(0 == r)
				{
					recvMsgLen = nmOsalQueue_recv(pQueue,pBuffer,dwBufLen);
					r = sem_post(&pQueue->sndSem);
					assert(!r);
					*pMsgLen = recvMsgLen;
					returnVal = NM_OK;
					break;
				}
				else
				{
					if(EAGAIN==errno)
					{
						select_sleep(1);
						timeout--;
					}
					else
					{
						returnVal = NM_ERR_FAULT;
						break;
					}
				}
			}
		}
	}
	else
	{
		r = sem_trywait(&(pQueue->rcvSem));
		if(0 == r)
		{
			recvMsgLen = nmOsalQueue_recv(pQueue,pBuffer,dwBufLen);
			r = sem_post(&pQueue->sndSem);
			assert(!r);
			returnVal = NM_OK;
		}
		else
		{
			if(EAGAIN==errno)
			{
				returnVal = NM_ERR_TIMEOUT;
			}
			else
			{
				returnVal = NM_ERR_FAULT;
			}
		}
	}
	return (returnVal);
}

unsigned long q_vGetPacketSize(
		unsigned long		Handle,  /* I: handler to queue  */
		unsigned long		*pPacketSize	 /* O: queue packet size */
	)
{
	NMRESULT				returnVal = NM_OK;
	nmOsalQueue_pt			pQueue = NULL;
	int 		r;
 
	pQueue = (nmOsalQueue_pt)Handle;
	/* First check if there are packets on the queue */
	r = sem_wait(&pQueue->rcvSem);
	assert(!r);

	if (r == 0)
	{
		/* get datasize of packet */
		*pPacketSize = pQueue->dataSize[pQueue->readIndex];

		/* make sure the receive semaphore keeps the correct value */
		r = sem_post(&pQueue->rcvSem);
		assert(!r);
	}
	else
	{
		/* No packets on the queue */
		returnVal = NM_ERR_FAULT;
	}

	return (returnVal);
}



unsigned long	q_create(NM_String strName
					 ,unsigned long flag
					  ,unsigned long maxPackets
					 ,unsigned long *pQueueHandle
					 )
{
	unsigned long bufSize = 4*sizeof(long);
	
	return q_vcreate(strName,flag,maxPackets,bufSize,pQueueHandle);
}

unsigned long  q_delete(
	unsigned long  queueHandle       /* I: queue handle */
				   )
{
	return q_vdelete(queueHandle);
}

unsigned long  q_send(
	unsigned long queueHandle  /* I: queue handle    */
	,const void *pBuffer      /* I: packet pointer  */ 
                          )
{
	unsigned long bufSize = 4*sizeof(long);
	
	return q_vsend(queueHandle,pBuffer,bufSize);
}

unsigned long  q_receive(
	unsigned long	queueHandle /* I: handler to queue              */
	,unsigned long	flag
	,unsigned long    wtTimeout
	,void	*pBuffer     /* I: pointer reception buffer.     */
	)
{
	unsigned long err = 0;
	unsigned long getSize = 0;
	unsigned long bufSize = 4*sizeof(long);
	
	err =  q_vreceive(queueHandle,flag,wtTimeout,pBuffer,bufSize,&getSize);

	if(NM_OK  != err) return err;

	if(bufSize != getSize)
	{
		return NM_ERR_FAULT;
	}
	return err;
}