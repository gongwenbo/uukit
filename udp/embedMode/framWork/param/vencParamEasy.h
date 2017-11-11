#ifndef __VENCPARAMEASY_H__
#define __VENCPARAMEASY_H__

#include "const.h"

typedef struct _VideoHeadLocal_
{
	uchar videoStandard;// 视频制式: 0:PAL制、1:NTSC制   2:AUTO
	uchar resolution[REAL_CHANNEL_NUM];//分辨率: 0,qcif; 1,cif; 3,hd1; 4,d1; 6,qvga; 7,vga; 16,720p(1280x720); 100,(1280x960)参考PIC_SIZE_E
	uchar frameRate[REAL_CHANNEL_NUM];//帧率,低6位标识具体帧率。bit7 和 bit8 标识帧率最大值,00:最大值为25,01:最大值为30,其它保留
} VIDEO_HEAD_LOCAL_T;

typedef struct _AudioHeadLocal_
{
	uchar	sampleRate;			// 2é?ù?ê, 0:8k, 1:16k
	uchar	bitWidth;			// ???í,0:8bits, 1:16bits
	uchar	encodeType;			// ±à??·?ê?,0:adpcm, 1:g711, 2:g726
	uchar	chMode;				// í¨μà?￡ê?, 0:μ￥í¨μà, 1:á￠ì?éù
} AUDIO_HEAD_LOCAL_T;

uchar VencParamEasyGetVideoStandard();
uchar VencParamEasyGetResolution( int channel );
uchar VencParamEasyGetFramerate( int channel );

void VencParamEasySetVideoStandard( uchar val );
void VencParamEasySetResolution( int channel, uchar val );
void VencParamEasySetFramerate( int channel, uchar val );

uchar VencParamEasyGetAudioSampleRate();
uchar VencParamEasyGetAudioBitWidth();
uchar VencParamEasyGetAudioEncodeType();
uchar VencParamEasyGetAudioChMode();
void VencParamEasySetAudioSampleRate( uchar val );
void VencParamEasySetAudioBitWidth( uchar val );
void VencParamEasySetAudioEncodeType( uchar val );
void VencParamEasySetAudioChMode( uchar val );

int ParamEasyInit();

#endif // __VENCPARAMEASY_H__

