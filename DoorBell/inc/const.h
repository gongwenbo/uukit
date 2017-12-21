#ifndef __CONST_H__
#define __CONST_H__

typedef unsigned int 	uint;
typedef unsigned long 	ulong;
typedef unsigned char 	uchar;
typedef unsigned short  ushort;  
typedef  char 			sharechar; // 用户ShareMalloc
#ifdef WIN32
#include "BaseTsd.h"
typedef UINT64 uint64_t;
#else
//typedef unsigned long long uint64_t;
#endif

#define SIZE_64K				(64*1024)
#define SIZE_256				256
#define SIZE_128				128
#define SIZE_48					48
#define SIZE_64					64
#define SIZE_20					20
#define SIZE_12K				(12*1024)
#define SIZE_32					32
#define SIZE_16					16
#define SIZE_256K				(256*1024)
#define SIZE_1K					1024
#define SIZE_4K					(4*1024)
#define SIZE_8					8
#define SIZE_512K				(512*1024)
#define SIZE_1M					(1024*1024)
#define SIZE_5000				5000
#define SIZE_512				512
#define SIZE_128K				(128*1024)
#define SIZE_132K				(132*1024)
#define	SIZE_2K					(2*1024)
#define	SIZE_12					12
#define	SIZE_52					52
#define	SIZE_16K				(16*1024)
#define	SIZE_84K				(84*1024)
#define	SIZE_32K				(32*1024)
#define	SIZE_8K					(8*1024)
#define SIZE_252K				(252*1024)
#define SIZE_20000				20000
#define SR_MNG_DELAY			15000	// 和管理服务器的交互延时时间;

#define	FI_SUCCESS				0	// 成功
#define	FI_FAIL					-1	// 失败
#define FI_SUCCESSFUL 			FI_SUCCESS
#define FI_FAILED				FI_FAIL
#define	FI_TRUE					1	// 真
#define	FI_FALSE				0	// 假

#define NET_ADDRSIZE 			20		// "192.168.188.168" 给20个bytes;"00:AB:BB:CC:BA:00" 共18个字节
#define MAX_PATH_LEVEL			20		// 最大目录级数
#define COM_BUF_SIZE 			256		// 常用buf 大小
#define MAX_CHANNEL_NUM			16		// 最大通道数
#define MAX_PB_NUM				4		// 回放最大通道数
#define DATE_LEN				12		// "2012-11-18" 的长度
#define TIME_LEN				12		// "10:20:28" 的长度
#define NORMAL_USER_NAME_LEN	32 		// 一般用户名的长度
#define NORMAL_PASSWD_LEN		32 		// 一般密码的长度
#define NORMAL_URL_LEN			128		// 一般域名的长度
#define MAX_WEEK_DAY			7 		//一周有7天
#define MAX_DAY_TIME_SEG		4		//一天提供四个时间段选择
#define MAX_SUPPORT_WIN			64		// 客户端最多支持64 个窗口
#define MAX_UNVARNISHED_TRANSMISSION_SIZE	1168		// 每次透传的最大字节数

#define MTU_SIZE				1000 // ql debug 1200	// 客户端最多支持64 个窗口
#define P2P_SEND_DATA_LEVEL     64
#define ONE_DAY_SECOND 			86400	//(24*3600)


// producer consumer open flag
typedef enum _OpenEn_
{
	OPEN_RDONLY = 0,
	OPEN_WRONLY
} OPEN_EN;

typedef enum _BlockEn_
{
	BLOCK_NO = 0,	// 以非阻塞的方式
	BLOCK_YES		// 以阻塞的方式
} BLOCK_EN;

#endif  // __CONST_H__

