#ifndef	_NM_OSAL_QUEUE_H
#define 	_NM_OSAL_QUEUE_H

#ifdef __cplusplus
#include "nmOsalType.h"
extern "C"
{
#endif

extern NMRESULT nmosalQueueOpen(
		NM_String				strName,		/* I: name of the queue 	*/
		NM_U32					maxPackets, /* I: queue size in packets */
		NM_U32					maxPacketSize, /* I: packet size in bytes	*/
		nmosalQueueHandle_pt	pQueueHandle,	/* O: handle pointer		*/
		NM_U32					flags			/* I: reserved				*/
	);

extern NMRESULT nmosalQueueClose(
	nmosalQueueHandle_t Handle	   /* I: queue handle */
);

extern NMRESULT nmosalQueueSend(
		  nmosalQueueHandle_t		Handle, 		/* I: queue handle	  */
		  const void					*pBuffer,	/* I: packet pointer	*/
		  NM_U32					packetSize,  /* I: packet size	   */
		  const NM_U32				*pTimeout,	/* I: timeout pointer */
		  NM_U32					flags		/* I: reserved 	   */
);



extern NMRESULT nmosalQueueReceive(
		nmosalQueueHandle_t		Handle, 			/* I: queue handle	  */
		NM_Pointer					pBuffer,	 		/* O: pointer reception buffer 	 */
		NM_U32				   		*pPacketSize, 	/*I/O: received packet size 		 */
		const NM_S32 				*pTimeout,	 	/* I: pointer to timeout value 	 */
		NM_U32 						flags		 	/* I: flags reserved for future use */
);

extern NMRESULT nmosalQueueGetPacketSize(
    nmosalQueueHandle_t Handle,  /* I: handler to queue  */
    NM_U32             *pPacketSize   /* O: queue packet size */
);

#ifdef __cplusplus
}
#endif
#endif
