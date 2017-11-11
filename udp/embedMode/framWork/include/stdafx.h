#ifndef	_STD_AFX_H
#define	_STD_AFX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <assert.h>
#include <linux/input.h>
#include <linux/kernel.h>


#ifndef BOOL
#define BOOL        int
#define FALSE       0
#define TRUE        1
#endif

#define emALIGN(addr, boundary) (((addr) + (boundary) - 1) & ~((boundary) - 1))

#define SOCKET int


#ifndef MYDP
#define	MYDP	printf
#endif

#ifndef ASSERT
#define ASSERT assert
#endif

#if 1
#define MYTRACE()\
{             \
	printf("--- COME IN %s(%d)\n",__FILE__,__LINE__);\
}
#else
#define MYTRACE()
#endif

#define TRACE() printf("-TRACE-[ %s, %d ]=> ",__FILE__,  __LINE__);printf("\r\n");usleep(1000);



#define MK_TRACE_		1

#ifdef	MK_TRACE_
#define MK_ERROR(msg...) fprintf(stderr, "[ %s, %d ]=> ",__FILE__,  __LINE__);printf(msg);printf("\r\n")
#define MK_ASSERT(exp...) assert(exp)	
#define MK_DEBUG(msg...) printf("[ %s, %d ]=> ",__FILE__,  __LINE__);printf(msg);printf("\r\n");
#define MK_TRACE() printf("MK_TRACE---[ %s, %d ]=> ",__FILE__,__LINE__);printf("\r\n");

#define DP_POS() printf("come in--[%s_%d_%s ]=> ",__FUNCTION__,__LINE__,__FILE__);printf("\r\n");

#else
#define MK_ERROR(msg...) (void)(msg)
#define MK_ASSERT(exp...) (void)(exp)
#define MK_DEBUG(msg...) (void)(msg)
#define MK_TRACE() 
#define DP_POS()
#endif

#endif
