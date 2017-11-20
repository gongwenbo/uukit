#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <imp/imp_common.h>
#include <imp/imp_system.h>
#include <imp/imp_encoder.h>

#include "common.h"
#include "rtmp264.h"
#include "cache.h"
#include "play.h"

//system init need
static int g_mainFlag = 1;
extern struct chn_conf chn[];
int hardware_init();
int hardware_free();

#include <thread>
#include <mutex>
#include <condition_variable>

#include "faac.h"
#include "faaccfg.h"

//读文件的回调函数
inline int read_buffer1(unsigned char *buf, int buf_size ){
	//usleep(30 * 1000);
	int retry = 0;
	int true_size = 0;
	
	while(true_size == 0 && retry < 3)
	{
		true_size = cache_poll(buf, buf_size);
		if(true_size != 0){
			printf("true_size: %d\n", true_size);
			return true_size;
		}
	
		usleep(10 * 1000);
		retry++;
	}
	return -1;
}

void send264()  
{  
	//int i = 20000; 
	//sleep(1);
    while(g_mainFlag)
	{
		RTMP264_Send(read_buffer1);
		usleep(30 * 1000);
	}	
}


// void send_aac()
// {
	// sleep(1);
    // while(g_mainFlag)
	// {
		////usleep(30 * 1000);
		// RTMPAAC_Send();;
	// }	
// }

static void QuitMain( int )
{
    g_mainFlag = 0;
}

int start(char *url)
{
	int i, j, ret;

	// 播放器初始化
	ret = hardware_init();
	if (ret < 0) {
		printf("播放器初始化失败！\n");
		return -1;
	}


	//*******************************************************//
	//***********************RTMP****************************//
	//连接RTMP服务器
	ret = RTMP264_Connect(url);
	//ret = RTMP264_Connect("rtmp://192.168.99.203:1935/hls");
	if (ret < 0) {
		printf("Connect RTMP failed\n");
		return -1;
	}
	
	std::thread p_rtmp(send264);
	//std::thread p_aac(send_aac); 
	//RTMPAAC_Send();
	
	// fp_send1 = fopen("test.h264", "rb");
	// RTMP264_Send(read_buffer1);

	signal( SIGINT, QuitMain );
	//g_mainFlag = 0;
	while(g_mainFlag){
	//for (i = 0; i < 1000; i++) {
		ret = IMP_Encoder_PollingStream(0, 1000);
		if (ret < 0) {
			printf("Polling stream timeout\n");
			continue;
		}
		//获取码流
		IMPEncoderStream stream;
		ret = IMP_Encoder_GetStream(0, &stream, 1);
		if (ret < 0) {
			printf("IMP_Encoder_GetStream() failed\n");
			return -1;
		}

		for (j = 0; j < stream.packCount; j++) {
			int num = cache_push((unsigned char *)stream.pack[j].virAddr, stream.pack[j].length);
			//size += stream.pack[j].length;
			//RTMP264_Send((unsigned char *)stream.pack[j].virAddr, stream.pack[j].length);
		}
		
		IMP_Encoder_ReleaseStream(0, &stream);
	}
	
	p_rtmp.join();
	cache_free();
	RTMP264_Close();
	
	//*********************RTMP******************************//
	//*******************************************************//
	
	// 关闭
	ret = hardware_free();
	if (ret < 0) {
		printf("关闭播放器失败\n");
		return -1;
	}
	return 0;
}

int hardware_init()
{
	int i, ret;

	// Step.1 System init
	ret = sample_system_init();
	if (ret < 0) {
		printf("IMP_System_Init() failed\n");
		return -1;
	}

	// Step.2 FrameSource init
	ret = sample_framesource_init();
	if (ret < 0) {
		printf("FrameSource init failed\n");
		return -1;
	}

	for (i = 0; i < FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			ret = IMP_Encoder_CreateGroup(chn[i].index);
			if (ret < 0) {
				printf("IMP_Encoder_CreateGroup(%d) error !\n", i);
				return -1;
			}
		}
	}

	// Step.3 Encoder init
	ret = sample_encoder_init();
	if (ret < 0) {
		printf("Encoder init failed\n");
		return -1;
	}
    sample_jpeg_init();
	// Step.4 Bind
	for (i = 0; i < FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			ret = IMP_System_Bind(&chn[i].framesource_chn, &chn[i].imp_encoder);
			if (ret < 0) {
				printf("Bind FrameSource channel%d and Encoder failed\n",i);
				return -1;
			}
		}
	}
	
	// 开启码流
	ret = sample_framesource_streamon();
	if (ret < 0) {
		printf("ImpStreamOn failed\n");
		return -1;
	}
	
	ret = IMP_Encoder_StartRecvPic(0);
	if (ret < 0) {
		printf("IMP_Encoder_StartRecvPic(0) failed\n");
		return -1;
	}
}

int hardware_free()
{
	int i, ret;
	
	ret = IMP_Encoder_StopRecvPic(0);
	if (ret < 0) {
		printf("IMP_Encoder_StopRecvPic() failed\n");
		return -1;
	}
	
	// 关闭码流
	ret = sample_framesource_streamoff();
	if (ret < 0) {
		printf("StreamOff failed\n");
		return -1;
	}
	
	// Step.A UnBind
	for (i = 0; i < FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			ret = IMP_System_UnBind(&chn[i].framesource_chn, &chn[i].imp_encoder);
			if (ret < 0) {
				printf("UnBind FrameSource channel%d and Encoder failed\n",i);
				return -1;
			}
		}
	}

	// Step.B Encoder exit
	ret = sample_encoder_exit();
	if (ret < 0) {
		printf("Encoder exit failed\n");
		return -1;
	}

	// Step.C FrameSource exit
	ret = sample_framesource_exit();
	if (ret < 0) {
		printf("FrameSource exit failed\n");
		return -1;
	}

	// Step.D System exit
	ret = sample_system_exit();
	if (ret < 0) {
		printf("sample_system_exit() failed\n");
		return -1;
	}
}


int rtmp_start(char *url)
{
	std::thread main_thread(start, url);
	
	while(g_mainFlag)
	{
		sleep(1);
	}
	
	main_thread.join();
}

int rtmp_pause()
{
	g_mainFlag = 0;
}




