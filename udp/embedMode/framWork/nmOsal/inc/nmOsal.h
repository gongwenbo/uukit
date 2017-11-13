
#ifndef	_NM_OSAL_H
#define 	_NM_OSAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "nmOsalType.h"

extern unsigned long	q_create(NM_String strName
						,unsigned long flag
						,unsigned long maxPackets
						,unsigned long *pQueueHandle
								 );
extern unsigned long  q_delete(
	unsigned long  queueHandle       /* I: queue handle */
				   );

extern unsigned long  q_send(
	unsigned long queueHandle  /* I: queue handle    */
	,const void *pBuffer      /* I: packet pointer  */ 
                          );

extern unsigned long  q_receive(
	unsigned long	queueHandle /* I: handler to queue              */
	,unsigned long	flag
	,unsigned long    wtTimeout
	,void	*pBuffer     /* I: pointer reception buffer.     */
	);

extern unsigned long q_vcreate(
		NM_String				strName,		/* I: name of the queue 	*/
		unsigned long			flags,			/* I: reserved				*/
		unsigned long			maxPackets, /* I: queue size in packets */
		unsigned long			maxPacketSize, /* I: packet size in bytes	*/
		unsigned long			*pQueueHandle	/* O: handle pointer		*/
	);

extern unsigned long q_vdelete(
	unsigned long Handle	   /* I: queue handle */
);

extern unsigned long q_vsend(
		  unsigned long				Handle, 		/* I: queue handle	  */
		  const void					*pBuffer,	/* I: packet pointer	*/
		  unsigned long				packetSize
);



extern unsigned long q_vreceive(
		unsigned long		Handle, 			/* I: queue handle	  */
		unsigned long		flags,
		unsigned long		timeout,
		void					*pBuffer,	/* I: packet pointer	*/
		unsigned long		dwBufLen,
		unsigned long		*pMsgLen
);

extern unsigned long q_vGetPacketSize(
    unsigned long 		Handle,  /* I: handler to queue  */
    unsigned long             *pPacketSize   /* O: queue packet size */
);

extern unsigned long sm_create(
		const char *				strName,		/* I: name of the queue 	*/
		unsigned long			count, 			/* I: queue size in packets */
		unsigned long			flags,			/* I: reserved			*/
		unsigned long			*pSmID			/* O: handle pointer		*/
	);

extern unsigned long sm_delete(
	unsigned long	  hSmID /* I: queue handle */
);

extern unsigned long sm_v(
		  unsigned long	  			hSmID 		/* I: queue handle	  */
);



extern unsigned long sm_p(
		unsigned long	  			hSmID, 			/* I: queue handle	  */
		unsigned long				flags,	 		/* O: pointer reception buffer 	 */
		unsigned long				timeout			//³¬Ê±
);

//extern unsigned long t_create(int priority,FN_THREAD start_rtn,void *arg);
//extern unsigned long t_close(unsigned long hTask);

#ifdef __cplusplus
}
#endif


#endif

