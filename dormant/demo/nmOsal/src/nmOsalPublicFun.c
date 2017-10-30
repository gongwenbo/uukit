#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>


#include "nmOsalType.h"
#include "nmOsalPublicFun.h"

//#ifdef NM_WIN32_OSAL

//#else
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <sys/select.h>
pthread_mutex_t			*gpOsalIntMutex = NULL;      /* global shared interrupt mutex */
pthread_mutexattr_t 		gOsalIntMutexAttr;
//#endif
inline void 	select_sleep(NM_U32	u32Milliseconds)
{
	struct timeval mytv;

	mytv.tv_sec = u32Milliseconds/1000;
	u32Milliseconds %= 1000;
	mytv.tv_usec = u32Milliseconds*1000;
	select(0,0,0,0,&mytv);
}
/*
inline void	nmosal_sleep(NM_U32	u32Milliseconds )
{
	#ifdef NM_WIN32_OSAL
	Sleep((DWORD)u32Milliseconds);
	#else
	usleep(u32Milliseconds*1000);
	#endif
}
*/
#ifdef NM_WIN32_OSAL

#else
inline void NM_OSAL_ENTER_CR()
{
	if (NULL== gpOsalIntMutex)
	{
		gpOsalIntMutex = (pthread_mutex_t	*)malloc(sizeof(pthread_mutex_t));
		pthread_mutexattr_init(&gOsalIntMutexAttr);
		pthread_mutexattr_settype(&gOsalIntMutexAttr, PTHREAD_MUTEX_TIMED_NP);
		pthread_mutex_init(gpOsalIntMutex, &gOsalIntMutexAttr);
		assert(NULL!= gpOsalIntMutex);
	}
	pthread_mutex_lock(gpOsalIntMutex);
}


inline void NM_OSAL_EXIT_CR()
{
	assert(NULL!= gpOsalIntMutex);
	pthread_mutex_unlock(gpOsalIntMutex);
}
#endif
