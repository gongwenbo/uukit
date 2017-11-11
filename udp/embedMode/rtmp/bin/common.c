#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <imp/imp_common.h>
#include <imp/imp_system.h>
#include <imp/imp_encoder.h>
#include <imp/imp_isp.h>
#include "common.h"

static const int S_RC_METHOD = ENC_RC_MODE_SMART;

struct chn_conf chn[FS_CHN_NUM] = {
	{
		.index = CH0_INDEX,
		.enable = CHN0_EN,
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


//数据源设置
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
                rc_attr->attrRcMode.attrH264Vbr.gopQPStep = 15;
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
                rc_attr->attrRcMode.attrH264Smart.maxQp = 45;
                rc_attr->attrRcMode.attrH264Smart.minQp = 15;
                rc_attr->attrRcMode.attrH264Smart.staticTime = 2;
                rc_attr->attrRcMode.attrH264Smart.maxBitRate = 2000 * (imp_chn_attr_tmp->picWidth * imp_chn_attr_tmp->picHeight) / (1280 * 720);
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