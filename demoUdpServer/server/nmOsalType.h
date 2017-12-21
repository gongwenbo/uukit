#ifndef	NM_OSAL_TYPE_H
#define	NM_OSAL_TYPE_H

typedef	unsigned char 	NM_U8;
typedef	unsigned short 	NM_U16; 
typedef	unsigned int 		NM_U32; 
typedef	char 			NM_S8; 
typedef	short 			NM_S16; 
typedef	int 				NM_S32;
typedef  char 			*NM_String;
typedef  unsigned char 	*NM_Address;
typedef void          		*NM_Pointer;

typedef void * (*FN_THREAD)(void *);

#ifndef	NULL
#define NULL 	0L
#endif

#ifndef 	BOOL
#define	BOOL 	int
#endif

#ifndef	FALSE
#define	FALSE	0
#endif

#ifndef	TRUE
#define	TRUE	1
#endif

#if defined(_WIN32) || defined(WIN32)
#define	NM_WIN32_OSAL		1
#else
#define	NM_LINUX_OSAL		1
#endif

#ifdef ULONG_PTR
typedef ULONG_PTR nmosalHandle_t;
#else
typedef NM_U32 nmosalHandle_t;
#endif

typedef nmosalHandle_t nmosalQueueHandle_t, *nmosalQueueHandle_pt;


#define 	NMOSAL_QUEUE_COMP 	0x30000000

//返回值的定义
typedef NM_U32	NMRESULT;

#define	NM_OK				0 		//成功
#define	NM_ERR_FAULT		(-1)		//未知错误
#define	NM_ERR_TIMEOUT	(1)

#define	NMOSAL_NOWAIT	(0)
#define	NMOSAL_WAIT		(1)

#define	SM_NOWAIT		NMOSAL_NOWAIT
#define	SM_WAIT		NMOSAL_WAIT

#define	Q_NOWAIT		NMOSAL_NOWAIT
#define	Q_WAIT			NMOSAL_WAIT

#endif
