#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


#include "imp/imp_system.h"
#include "imp/imp_common.h"

#include <imp/imp_encoder.h>
#include <imp/imp_isp.h>
#include "common.h"

#define encode_1080p  encode_720p
static const int S_RC_METHOD = ENC_RC_MODE_CBR;

struct chn_conf chn[FS_CHN_NUM] = {
	{
		.index = CH0_INDEX,
		.enable = CHN0_EN,
		.bitRate = 3000,
		.IBiasLvl = 2,
		.fs_chn_attr = {
			.pixFmt = PIX_FMT_NV12,
			.outFrmRateNum = SENSOR_FRAME_RATE_NUM,
			.outFrmRateDen = SENSOR_FRAME_RATE_DEN,
			.nrVBs = 3,
			.type = FS_PHY_CHANNEL,

			.crop.enable = CROP_EN,
			.crop.top = 0,
			.crop.left = 0,
			.crop.width = SENSOR_WIDTH,
			.crop.height = SENSOR_HEIGHT,

			.scaler.enable = 0,

			.picWidth = SENSOR_WIDTH,
			.picHeight = SENSOR_HEIGHT,
		   },
		.framesource_chn =	{ DEV_ID_FS, 0, 0},
		.imp_encoder = { DEV_ID_ENC, 0, 0},
	},
	{
		.index = CH1_INDEX,
		.enable = CHN1_EN,
		.fs_chn_attr = {
			.pixFmt = PIX_FMT_NV12,
			.outFrmRateNum = SENSOR_FRAME_RATE_NUM,
			.outFrmRateDen = SENSOR_FRAME_RATE_DEN,
			.nrVBs = 3,
			.type = FS_PHY_CHANNEL,

			.crop.enable = CROP_EN,
			.crop.top = 0,
			.crop.left = 0,
			.crop.width = SENSOR_WIDTH,
			.crop.height = SENSOR_HEIGHT,

			.scaler.enable = 1,
			.scaler.outwidth = SENSOR_WIDTH_SECOND,
			.scaler.outheight = SENSOR_HEIGHT_SECOND,

			.picWidth = SENSOR_WIDTH_SECOND,
			.picHeight = SENSOR_HEIGHT_SECOND,
		   },
		.framesource_chn =	{ DEV_ID_FS, 1, 0},
		.imp_encoder = { DEV_ID_ENC, 1, 0},
	},
};

/************************************************************************************/


typedef enum resolution_type {
	RES_QCIF	= 0,	/* 176x144 */
	RES_CIF,			/* 352x288 */
	RES_DCIF,			/* 528x384 */
	RES_HD1,			/* 352x576 */
	RES_QVGA,			/* 320x240 */
	RES_D1,				/* 704x576 */
	RES_VGA,			/* 640x480 */
	RES_960H,			/* 960x576 */
	RES_720P,			/* 1280x720 */
	RES_960P,			/* 1280x960 */
	RES_1080P,			/* 1920x1080 */
} resolution_type_t;

//vedio default value
encode_attr encode_1080p = {
	.width = 1920,
	.height = 1080,
	.outFrmRateNum = 25,
	.bitRate = 3000,
	.IBiasLvl = 2,
};


	
int change_chn_param(encode_attr *e_attr)
{
	if(e_attr->width < chn[0].fs_chn_attr.crop.width || e_attr->height < chn[0].fs_chn_attr.crop.height)
	{
		chn[0].fs_chn_attr.scaler.enable = 1;
		chn[0].fs_chn_attr.scaler.outwidth = e_attr->width;
		chn[0].fs_chn_attr.scaler.outheight = e_attr->height;
		chn[0].fs_chn_attr.picWidth = e_attr->width;
		chn[0].fs_chn_attr.picHeight = e_attr->height;
	}
	else
	{
		chn[0].fs_chn_attr.scaler.enable = 0;
		chn[0].fs_chn_attr.picWidth = e_attr->width;
		chn[0].fs_chn_attr.picHeight = e_attr->height;;
	}
	chn[0].fs_chn_attr.outFrmRateNum = e_attr->outFrmRateNum;
	chn[0].bitRate = e_attr->bitRate;
	if(e_attr->IBiasLvl >= -3 || e_attr->IBiasLvl <= 3)
		chn[0].IBiasLvl = e_attr->IBiasLvl;
}


int reload_encoder_init(encode_attr *change_attr)
{
	int i, ret;
	IMPEncoderAttr *enc_attr;
	IMPEncoderRcAttr *rc_attr;
	IMPFSChnAttr *imp_chn_attr_tmp;
	IMPEncoderCHNAttr channel_attr;

	for (i = 0; i <  1; i++) {
		if (chn[i].enable) {
			imp_chn_attr_tmp = &chn[i].fs_chn_attr;
			memset(&channel_attr, 0, sizeof(IMPEncoderCHNAttr));
			enc_attr = &channel_attr.encAttr;
			enc_attr->enType = PT_H264;
			enc_attr->bufSize = 0;
			enc_attr->profile = 1;
			enc_attr->picWidth = change_attr->width;
			enc_attr->picHeight = change_attr->height;
			rc_attr = &channel_attr.rcAttr;
			
			rc_attr->attrRcMode.rcMode = ENC_RC_MODE_CBR;
			printf("Num: %d\n", change_attr->outFrmRateNum);
			rc_attr->attrRcMode.attrH264Cbr.outFrmRate.frmRateNum = change_attr->outFrmRateNum;
			rc_attr->attrRcMode.attrH264Cbr.outFrmRate.frmRateDen = 1;
			rc_attr->attrRcMode.attrH264Cbr.maxGop = 2 * change_attr->outFrmRateNum;
			rc_attr->attrRcMode.attrH264Cbr.outBitRate = change_attr->bitRate;
			rc_attr->attrRcMode.attrH264Cbr.maxQp = 38;
			rc_attr->attrRcMode.attrH264Cbr.minQp = 15;
			//rc_attr->attrRcMode.attrH264Cbr.maxFPS = 100;
			//rc_attr->attrRcMode.attrH264Cbr.minFPS = 1;
			rc_attr->attrRcMode.attrH264Cbr.iBiasLvl = change_attr->IBiasLvl;
			rc_attr->attrRcMode.attrH264Cbr.frmQPStep = 3;
			rc_attr->attrRcMode.attrH264Cbr.gopQPStep = 15;
			rc_attr->attrRcMode.attrH264Cbr.adaptiveMode = false;
			rc_attr->attrRcMode.attrH264Cbr.gopRelation = false;

			ret = IMP_Encoder_CreateChn(chn[i].index, &channel_attr);
			if (ret < 0) {
				printf( "IMP_Encoder_CreateChn(%d) error !\n", i);
				return -1;
			}

			ret = IMP_Encoder_RegisterChn(chn[i].index, chn[i].index);
			if (ret < 0) {
				printf("IMP_Encoder_RegisterChn(%d, %d) error: %d\n",
						chn[i].index, chn[i].index, ret);
				return -1;
			}
		}
	}

    //JPEG初始化
	sample_jpeg_init();
	return 0;
}



//
int change_resolutiong(encode_attr *e_attr,  int chn_num)   //需要添加一个形参，音视频线程ID
{
	int i;
	int ret;
	IMPFSChnAttr fs_chn_attr_t;
	//停止视频接收线程，音频接收线程也需要停止
	//pthread_cancel(tid);

	//pthread_join(tid, NULL);    //等待线程结束
	IMP_Encoder_StopRecvPic(0); //停止接收图像
	IMP_FrameSource_DisableChn(chn_num);
	IMP_Encoder_UnRegisterChn(chn_num);
	IMP_Encoder_DestroyChn(chn_num);

	//JPEG
	IMP_FrameSource_DisableChn(2+chn_num);
	IMP_Encoder_UnRegisterChn(2+chn_num);
	IMP_Encoder_DestroyChn(2+chn_num);
	
	for(i = 0; i < 1; i++)
	{	
        IMP_FrameSource_GetChnAttr(i, &fs_chn_attr_t);
		fs_chn_attr_t.outFrmRateNum = e_attr->outFrmRateNum;
		if(e_attr->width < chn[i].fs_chn_attr.crop.width || e_attr->height  < chn[i].fs_chn_attr.crop.height)
		{
			fs_chn_attr_t.scaler.enable = 1,
			fs_chn_attr_t.scaler.outwidth = e_attr->width;
			fs_chn_attr_t.scaler.outheight = e_attr->height;
			fs_chn_attr_t.picWidth = e_attr->width;
			fs_chn_attr_t.picHeight = e_attr->height;			
		}
		else
			fs_chn_attr_t.scaler.enable = 0;    //不需要裁剪
	}
	
	ret = IMP_FrameSource_SetChnAttr(i, &fs_chn_attr_t);
	if(ret != 0)
	{
		printf("setchnAttr failed...\n");
		return -1;
	}
	
	reload_encoder_init(e_attr);

	return 0;
}


//reload_all_param

void reload_all_param(void)
{
	//step1 读取配置文件函数

	//step2 修改参数
	change_chn_param(&encode_720p);
	 
	change_resolutiong(&encode_720p, 0);

	IMP_FrameSource_EnableChn(0);

}

static int save_stream(int fd, IMPEncoderStream *stream)
{
	int ret, i, nr_pack = stream->packCount;

	for (i = 0; i < nr_pack; i++) {
		ret = write(fd, (void *)stream->pack[i].virAddr,
					stream->pack[i].length);
		if (ret != stream->pack[i].length) {
			printf( "stream write error\n");
			return -1;
		}
		//IMP_LOG_DBG(TAG, "stream->pack[%d].dataType=%d\n", i, ((int)stream->pack[i].dataType.h264Type));
	}

	return 0;
}

int sample_jpeg_init()
{
	int i, ret;
	IMPEncoderAttr *enc_attr;
	IMPEncoderCHNAttr channel_attr;
	IMPFSChnAttr *imp_chn_attr_tmp;

	for (i = 0; i <  FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			imp_chn_attr_tmp = &chn[i].fs_chn_attr;
			memset(&channel_attr, 0, sizeof(IMPEncoderCHNAttr));
			enc_attr = &channel_attr.encAttr;
			enc_attr->enType = PT_JPEG;
			enc_attr->bufSize = 0;
			enc_attr->profile = 0;
			enc_attr->picWidth = imp_chn_attr_tmp->picWidth;
			enc_attr->picHeight = imp_chn_attr_tmp->picHeight;

			/* Create Channel */
			ret = IMP_Encoder_CreateChn(2 + chn[i].index, &channel_attr);
			if (ret < 0) {
				printf("IMP_Encoder_CreateChn(%d) error: %d\n",
							chn[i].index, ret);
				return -1;
			}

			/* Resigter Channel */
			ret = IMP_Encoder_RegisterChn(i, 2 + chn[i].index);
			if (ret < 0) {
				printf("IMP_Encoder_RegisterChn(0, %d) error: %d\n",
							chn[i].index, ret);
				return -1;
			}
		}
	}

	return 0;
}

int sample_get_jpeg_snap()
{
	int i, ret;
	char snap_path[64];

	for (i = 0; i < FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			ret = IMP_Encoder_StartRecvPic(2 + chn[i].index);
			if (ret < 0) {
				printf("IMP_Encoder_StartRecvPic(%d) failed\n", 2 + chn[i].index);
				return -1;
			}

			sprintf(snap_path, "%s/snap-%d.jpg",
					SNAP_FILE_PATH_PREFIX, chn[i].index);

			printf( "Open Snap file %s ", snap_path);
			int snap_fd = open(snap_path, O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (snap_fd < 0) {
				printf( "failed: %s\n", "open snap");
				return -1;
			}
			printf( "OK\n");

			/* Polling JPEG Snap, set timeout as 1000msec */
			ret = IMP_Encoder_PollingStream(2 + chn[i].index, 1000);
			if (ret < 0) {
				printf("Polling stream timeout\n");
				continue;
			}

			IMPEncoderStream stream;
			/* Get JPEG Snap */
			ret = IMP_Encoder_GetStream(chn[i].index + 2, &stream, 1);
			if (ret < 0) {
				printf( "IMP_Encoder_GetStream() failed\n");
				return -1;
			}

			ret = save_stream(snap_fd, &stream);
			if (ret < 0) {
				close(snap_fd);
				return ret;
			}

			IMP_Encoder_ReleaseStream(2 + chn[i].index, &stream);

			close(snap_fd);

			ret = IMP_Encoder_StopRecvPic(2 + chn[i].index);
			if (ret < 0) {
				printf( "IMP_Encoder_StopRecvPic() failed\n");
				return -1;
			}
		}
	}
	return 0;
}

/**************************************************************************************/

//系统初始化
IMPSensorInfo sensor_info;
int sample_system_init()
{
	int ret = 0;

	memset(&sensor_info, 0, sizeof(IMPSensorInfo));
	memcpy(sensor_info.name, SENSOR_NAME, sizeof(SENSOR_NAME));
	sensor_info.cbus_type = SENSOR_CUBS_TYPE;
	memcpy(sensor_info.i2c.type, SENSOR_NAME, sizeof(SENSOR_NAME));
	sensor_info.i2c.addr = SENSOR_I2C_ADDR;

	//printf("[sample_system_init] sample_system_init start\n");

	ret = IMP_ISP_Open();
	if(ret < 0){
		printf("[sample_system_init] failed to open ISP\n");
		return -1;
	}

	ret = IMP_ISP_AddSensor(&sensor_info);
	if(ret < 0){
		printf("[sample_system_init] failed to AddSensor\n");
		return -1;
	}

	ret = IMP_ISP_EnableSensor();
	if(ret < 0){
		printf("[sample_system_init] failed to EnableSensor\n");
		return -1;
	}

	ret = IMP_System_Init();
	if(ret < 0){
		printf("[sample_system_init] IMP_System_Init failed\n");
		return -1;
	}

	/* enable turning, to debug graphics */
	ret = IMP_ISP_EnableTuning();
	if(ret < 0){
		printf("[sample_system_init] IMP_ISP_EnableTuning failed\n");
		return -1;
	}

    ret = IMP_ISP_Tuning_SetSensorFPS(SENSOR_FRAME_RATE_NUM, SENSOR_FRAME_RATE_DEN);
    if (ret < 0){
		printf("[sample_system_init] failed to set sensor fps\n");
        return -1;
    }

	//printf("[sample_system_init] ImpSystemInit success\n");
	return 0;
}





int sample_system_exit()
{
	int ret = 0;
	//printf("[sample_system_exit] sample_system_exit start\n");

	IMP_System_Exit();

	ret = IMP_ISP_DisableSensor();
	if(ret < 0){
		printf("[sample_system_exit] failed to EnableSensor\n");
		return -1;
	}

	ret = IMP_ISP_DelSensor(&sensor_info);
	if(ret < 0){
		printf("[sample_system_exit] failed to AddSensor\n");
		return -1;
	}

	ret = IMP_ISP_DisableTuning();
	if(ret < 0){
		printf("[sample_system_exit] IMP_ISP_DisableTuning failed\n");
		return -1;
	}

	if(IMP_ISP_Close()){
		printf("[sample_system_exit] failed to open ISP\n");
		return -1;
	}

	//printf("[sample_system_exit] sample_system_exit success\n");

	return 0;
}


//视频数据源设置
int sample_framesource_init()
{
	int i, ret;

	for (i = 0; i <  FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			ret = IMP_FrameSource_CreateChn(chn[i].index, &chn[i].fs_chn_attr);
			if(ret < 0){
				printf("IMP_FrameSource_CreateChn(chn%d) error !\n", chn[i].index);
				return -1;
			}
			ret = IMP_FrameSource_SetChnAttr(chn[i].index, &chn[i].fs_chn_attr);
			if (ret < 0) {
				printf("IMP_FrameSource_SetChnAttr(chn%d) error !\n",  chn[i].index);
				return -1;
	}	}	}
	return 0;
}

int sample_framesource_exit()
{
	int ret,i;

	for (i = 0; i <  FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			/*Destroy channel i*/
			ret = IMP_FrameSource_DestroyChn(i);
			if (ret < 0) {
				printf("IMP_FrameSource_DestroyChn() error: %d\n", ret);
				return -1;
			}
		}
	}
	return 0;
}






//编码设置
int sample_encoder_init()
{
	int i, ret;
	IMPEncoderAttr *enc_attr;
	IMPEncoderRcAttr *rc_attr;
	IMPFSChnAttr *imp_chn_attr_tmp;
	IMPEncoderCHNAttr channel_attr;

	for (i = 0; i <  FS_CHN_NUM; i++) {
		if (chn[i].enable) {
			imp_chn_attr_tmp = &chn[i].fs_chn_attr;
			memset(&channel_attr, 0, sizeof(IMPEncoderCHNAttr));
			enc_attr = &channel_attr.encAttr;
			enc_attr->enType = PT_H264;
			enc_attr->bufSize = 0;
			enc_attr->profile = 1;
			enc_attr->picWidth = imp_chn_attr_tmp->picWidth;
			enc_attr->picHeight = imp_chn_attr_tmp->picHeight;
			rc_attr = &channel_attr.rcAttr;
            if (S_RC_METHOD == ENC_RC_MODE_CBR) {
                rc_attr->attrRcMode.rcMode = ENC_RC_MODE_CBR;
                rc_attr->attrRcMode.attrH264Cbr.outFrmRate.frmRateNum = imp_chn_attr_tmp->outFrmRateNum;
                rc_attr->attrRcMode.attrH264Cbr.outFrmRate.frmRateDen = imp_chn_attr_tmp->outFrmRateDen;
                rc_attr->attrRcMode.attrH264Cbr.maxGop = 2 * rc_attr->attrRcMode.attrH264Cbr.outFrmRate.frmRateNum / rc_attr->attrRcMode.attrH264Cbr.outFrmRate.frmRateDen;
                rc_attr->attrRcMode.attrH264Cbr.outBitRate = 2000 * (imp_chn_attr_tmp->picWidth * imp_chn_attr_tmp->picHeight) / (1280 * 720);
                rc_attr->attrRcMode.attrH264Cbr.maxQp = 45;
                rc_attr->attrRcMode.attrH264Cbr.minQp = 15;
                rc_attr->attrRcMode.attrH264Cbr.iBiasLvl = 0;
                rc_attr->attrRcMode.attrH264Cbr.frmQPStep = 3;
                rc_attr->attrRcMode.attrH264Cbr.gopQPStep = 15;
                rc_attr->attrRcMode.attrH264Cbr.adaptiveMode = false;
                rc_attr->attrRcMode.attrH264Cbr.gopRelation = false;

                rc_attr->attrHSkip.hSkipAttr.skipType = IMP_Encoder_STYPE_N1X;
                rc_attr->attrHSkip.hSkipAttr.m = 0;
                rc_attr->attrHSkip.hSkipAttr.n = 0;
                rc_attr->attrHSkip.hSkipAttr.maxSameSceneCnt = 0;
                rc_attr->attrHSkip.hSkipAttr.bEnableScenecut = 0;
                rc_attr->attrHSkip.hSkipAttr.bBlackEnhance = 0;
                rc_attr->attrHSkip.maxHSkipType = IMP_Encoder_STYPE_N1X;
            } else if (S_RC_METHOD == ENC_RC_MODE_VBR) {
                rc_attr->attrRcMode.rcMode = ENC_RC_MODE_VBR;
                rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateNum = imp_chn_attr_tmp->outFrmRateNum;
                rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateDen = imp_chn_attr_tmp->outFrmRateDen;
                rc_attr->attrRcMode.attrH264Vbr.maxGop = 2 * rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateNum / rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateDen;
                rc_attr->attrRcMode.attrH264Vbr.maxQp = 45;
                rc_attr->attrRcMode.attrH264Vbr.minQp = 15;
                rc_attr->attrRcMode.attrH264Vbr.staticTime = 2;
                rc_attr->attrRcMode.attrH264Vbr.maxBitRate = 2000 * (imp_chn_attr_tmp->picWidth * imp_chn_attr_tmp->picHeight) / (1280 * 720);
                rc_attr->attrRcMode.attrH264Vbr.iBiasLvl = 0;
                rc_attr->attrRcMode.attrH264Vbr.changePos = 80;
                rc_attr->attrRcMode.attrH264Vbr.qualityLvl = 2;
                rc_attr->attrRcMode.attrH264Vbr.frmQPStep = 3;
                rc_attr->attrRcMode.attrH264Vbr.gopQPStep = 5;
                rc_attr->attrRcMode.attrH264Vbr.gopRelation = false;

                rc_attr->attrHSkip.hSkipAttr.skipType = IMP_Encoder_STYPE_N1X;
                rc_attr->attrHSkip.hSkipAttr.m = 0;
                rc_attr->attrHSkip.hSkipAttr.n = 0;
                rc_attr->attrHSkip.hSkipAttr.maxSameSceneCnt = 0;
                rc_attr->attrHSkip.hSkipAttr.bEnableScenecut = 0;
                rc_attr->attrHSkip.hSkipAttr.bBlackEnhance = 0;
                rc_attr->attrHSkip.maxHSkipType = IMP_Encoder_STYPE_N1X;
            } else if (S_RC_METHOD == ENC_RC_MODE_SMART) {
                rc_attr->attrRcMode.rcMode = ENC_RC_MODE_SMART;
                rc_attr->attrRcMode.attrH264Smart.outFrmRate.frmRateNum = imp_chn_attr_tmp->outFrmRateNum;
                rc_attr->attrRcMode.attrH264Smart.outFrmRate.frmRateDen = imp_chn_attr_tmp->outFrmRateDen;
                rc_attr->attrRcMode.attrH264Smart.maxGop = 2 * rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateNum / rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateDen;
                rc_attr->attrRcMode.attrH264Smart.maxQp = 50;
                rc_attr->attrRcMode.attrH264Smart.minQp = 15;
                rc_attr->attrRcMode.attrH264Smart.staticTime = 2;
                rc_attr->attrRcMode.attrH264Smart.maxBitRate = 3000 * (imp_chn_attr_tmp->picWidth * imp_chn_attr_tmp->picHeight) / (1280 * 720);
                rc_attr->attrRcMode.attrH264Smart.iBiasLvl = 0;
                rc_attr->attrRcMode.attrH264Smart.changePos = 80;
                rc_attr->attrRcMode.attrH264Smart.qualityLvl = 2;
                rc_attr->attrRcMode.attrH264Smart.frmQPStep = 3;
                rc_attr->attrRcMode.attrH264Smart.gopQPStep = 15;
                rc_attr->attrRcMode.attrH264Smart.gopRelation = false;

                rc_attr->attrHSkip.hSkipAttr.skipType = IMP_Encoder_STYPE_N1X;
                rc_attr->attrHSkip.hSkipAttr.m = rc_attr->attrRcMode.attrH264Smart.maxGop - 1;
                rc_attr->attrHSkip.hSkipAttr.n = 1;
                rc_attr->attrHSkip.hSkipAttr.maxSameSceneCnt = 6;
                rc_attr->attrHSkip.hSkipAttr.bEnableScenecut = 0;
                rc_attr->attrHSkip.hSkipAttr.bBlackEnhance = 0;
                rc_attr->attrHSkip.maxHSkipType = IMP_Encoder_STYPE_N1X;
            } else { /* fixQp */
                rc_attr->attrRcMode.rcMode = ENC_RC_MODE_FIXQP;
                rc_attr->attrRcMode.attrH264FixQp.outFrmRate.frmRateNum = imp_chn_attr_tmp->outFrmRateNum;
                rc_attr->attrRcMode.attrH264FixQp.outFrmRate.frmRateDen = imp_chn_attr_tmp->outFrmRateDen;
                rc_attr->attrRcMode.attrH264FixQp.maxGop = 2 * rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateNum / rc_attr->attrRcMode.attrH264Vbr.outFrmRate.frmRateDen;
                rc_attr->attrRcMode.attrH264FixQp.qp = 42;

                rc_attr->attrHSkip.hSkipAttr.skipType = IMP_Encoder_STYPE_N1X;
                rc_attr->attrHSkip.hSkipAttr.m = 0;
                rc_attr->attrHSkip.hSkipAttr.n = 0;
                rc_attr->attrHSkip.hSkipAttr.maxSameSceneCnt = 0;
                rc_attr->attrHSkip.hSkipAttr.bEnableScenecut = 0;
                rc_attr->attrHSkip.hSkipAttr.bBlackEnhance = 0;
                rc_attr->attrHSkip.maxHSkipType = IMP_Encoder_STYPE_N1X;
            }

			ret = IMP_Encoder_CreateChn(chn[i].index, &channel_attr);
			if (ret < 0) {
				printf("IMP_Encoder_CreateChn(%d) error !\n", i);
				return -1;
			}

			ret = IMP_Encoder_RegisterChn(chn[i].index, chn[i].index);
			if (ret < 0) {
				printf("IMP_Encoder_RegisterChn(%d, %d) error: %d\n",
						chn[i].index, chn[i].index, ret);
				return -1;
			}
		}
	}
	return 0;
}

static int encoder_chn_exit(int encChn)
{
	int ret;
	IMPEncoderCHNStat chn_stat;
	ret = IMP_Encoder_Query(encChn, &chn_stat);
	if (ret < 0) {
		printf("IMP_Encoder_Query(%d) error: %d\n",
					encChn, ret);
		return -1;
	}

	if (chn_stat.registered) {
		ret = IMP_Encoder_UnRegisterChn(encChn);
		if (ret < 0) {
			printf("IMP_Encoder_UnRegisterChn(%d) error: %d\n",
						encChn, ret);
			return -1;
		}

		ret = IMP_Encoder_DestroyChn(encChn);
		if (ret < 0) {
			printf("IMP_Encoder_DestroyChn(%d) error: %d\n",
						encChn, ret);
			return -1;
		}
	}

	return 0;
}

int sample_encoder_exit()
{
	int ret;

	ret = encoder_chn_exit(ENC_H264_CHANNEL);
	if (ret < 0) {
		printf("Encoder Channel %d exit  error: %d\n",
					ENC_H264_CHANNEL, ret);
		return -1;
	}

	ret = encoder_chn_exit(ENC_JPEG_CHANNEL);
	if (ret < 0) {
		printf("Encoder Channel %d exit  error: %d\n",
					ENC_JPEG_CHANNEL, ret);
		return -1;
	}

	ret = IMP_Encoder_DestroyGroup(0);
	if (ret < 0) {
		printf("IMP_Encoder_DestroyGroup(0) error: %d\n", ret);
		return -1;
	}
	return 0;
}


//开启码流
int sample_framesource_streamon()
{
	int ret = 0, i = 0;
	/* Enable channels */
	for (i = 0; i < FS_CHN_NUM; i++) {
		if (chn[i].enable){
			ret = IMP_FrameSource_EnableChn(chn[i].index);
			if (ret < 0) {
				printf("IMP_FrameSource_EnableChn(%d) error: %d\n", ret, chn[i].index);
				return -1;
			}
		}
	}
	return 0;
}

int sample_framesource_streamoff()
{
	int ret = 0, i = 0;
	/* Enable channels */
	for (i = 0; i < FS_CHN_NUM; i++) {
		if (chn[i].enable){
			ret = IMP_FrameSource_DisableChn(chn[i].index);
			if (ret < 0) {
				printf("IMP_FrameSource_DisableChn(%d) error: %d\n", ret, chn[i].index);
				return -1;
			}
		}
	}
	return 0;
}

#ifdef __cplusplus
}
#endif
