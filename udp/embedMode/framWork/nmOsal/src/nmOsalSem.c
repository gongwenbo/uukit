#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "nmOsalType.h"
#include "nmOsalPublicFun.h"

#define	OSAL_SEM_MAGIC 	0xF005012

typedef struct _nmOsalSem_struct *nmOsalSem_pt;

typedef struct _nmOsalSem_struct
{
	NM_U32			magic;	//magic
	sem_t			osHandle;
	pthread_mutexattr_t osMutexAttr;
	nmOsalSem_pt	pPrev;
	nmOsalSem_pt	pNext;
} nmOsalSem_t;



static nmOsalSem_pt gpOsalSemList = NULL;

static void OsalSemAddHandle(
	nmOsalSem_pt pHandle
	)
{

	NM_OSAL_ENTER_CR(); 						  /* ENTER CR */
	if (NULL != gpOsalSemList)
		gpOsalSemList->pPrev = pHandle;

	pHandle->pNext	  = gpOsalSemList;
	pHandle->pPrev	  = NULL;
	gpOsalSemList = pHandle;

	NM_OSAL_EXIT_CR();							  /* LEAVE CR */
}


static void OsalSemDeleteHandle(
	nmOsalSem_pt pHandle
	)
{
	NM_OSAL_ENTER_CR(); 						  /* ENTER CR */

	/* check if it is the first element */
	if (NULL == pHandle->pPrev)
		gpOsalSemList = pHandle->pNext;
	else
		pHandle->pPrev->pNext = pHandle->pNext;

	/* check if it is not the last element */
	if (NULL != pHandle->pNext)
		pHandle->pNext->pPrev = pHandle->pPrev;

	NM_OSAL_EXIT_CR();							  /* LEAVE CR */
}



unsigned long sm_create(
		const char *			strName,
		unsigned long			count,
		unsigned long			flags,
		unsigned long			*pSmID
	)
{
	nmOsalSem_pt		pObject = NULL;
	int	resp =0;
	

	pObject	= (nmOsalSem_pt) malloc(sizeof (nmOsalSem_t));
	assert(NULL != pObject);
	if(NULL == pObject)
	{
		return NM_ERR_FAULT;
	}
	memset(pObject,0,sizeof(nmOsalSem_t));
	pObject->magic = OSAL_SEM_MAGIC;

	resp = sem_init( &(pObject->osHandle), 0, count );
	assert(0== resp);
	if(0 != resp)
	{
		free(pObject);
		return NM_ERR_FAULT;
	}
	OsalSemAddHandle(pObject);

	*pSmID = (unsigned long)pObject;
	return  NM_OK;
}

unsigned long sm_delete(unsigned long	  hSmID )
{
	unsigned long		returnVal = NM_OK;
	nmOsalSem_pt		pObject = NULL;

	pObject = (nmOsalSem_pt)hSmID;

	OsalSemDeleteHandle((nmOsalSem_pt)pObject);

	if(0!=sem_destroy(&(pObject->osHandle)) )
	{
		returnVal = NM_ERR_FAULT;
	}
	free(pObject);
	
	return (returnVal);
}

unsigned long sm_v(unsigned long	  hSmID )
{
	nmOsalSem_pt		pObject = (nmOsalSem_pt)hSmID;

	assert(OSAL_SEM_MAGIC == pObject->magic);
	
	if(OSAL_SEM_MAGIC != pObject->magic)
	{
		return NM_ERR_FAULT;
	}
	if(0==sem_post(&(pObject->osHandle) ) )
	{
		return NM_OK;
	}
	else
	{
		return NM_ERR_FAULT;
	}
}


unsigned long sm_p(unsigned long hSmID,unsigned long flags,unsigned long timeout)
{
	nmOsalSem_pt		pObject = (nmOsalSem_pt)hSmID;

	assert(OSAL_SEM_MAGIC == pObject->magic);
	
	if(OSAL_SEM_MAGIC != pObject->magic)
	{
		return NM_ERR_FAULT;
	}
	if(SM_WAIT==flags)
	{
		if(0 == timeout)
		{
			if(0==sem_wait(&(pObject->osHandle) ) )
			{
				return NM_OK;
			}
			else
			{
				return NM_ERR_FAULT;
			}
		}
		else
		{
			int r=0;
			while (timeout > 0)
			{
				r = sem_trywait(&(pObject->osHandle));
				if(0 == r)
				{
					return NM_OK;
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
						return  NM_ERR_FAULT;
					}
				}
			}
			return NM_ERR_TIMEOUT;
		}
	}
	else
	{
		if(0==sem_trywait(&(pObject->osHandle) ) )
		{
			return NM_OK;
		}
		else
		{
			return NM_ERR_FAULT;
		}
	}
}

//===========================  thread   =============
/*


unsigned long t_create(int priority,FN_THREAD start_rtn,void *arg)
{
	pthread_t			*pThread = NULL;
	pthread_attr_t		stAttr;

	pThread = malloc(sizeof(pthread_t));
	if(NULL == pThread)
	{
		return 0;
	}
	pthread_attr_init(&stAttr);

	pthread_attr_setscope(&stAttr, PTHREAD_SCOPE_SYSTEM);//绑定
	pthread_attr_setdetachstate(&stAttr, PTHREAD_CREATE_DETACHED);//分离
	if(pthread_create(pThread, &stAttr, start_rtn,(void *)arg) == 0)//创建线程
	{
		pthread_attr_destroy(&stAttr);

		return (unsigned long)pThread;
	}
	else
	{
		pthread_attr_destroy(&stAttr);
		free(pThread);
		return 0;
	}
}

unsigned long t_close(unsigned long hTask)
{
	pthread_t			*pThread = (pthread_t *)hTask;

	if(NULL == pThread) return NM_ERR_FAULT;

	free(pThread);

	pThread = NULL;
	return NM_OK;
}
*/

