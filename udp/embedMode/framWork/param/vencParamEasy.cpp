/*
*******************************************************************************
**  Copyright (c) 2012, ÉîÛÚÊĞÓĞÏŞ¹«Ë¾, All rights reserved.
**  ×÷Õß£ºÁºÇÅ½­
**  µ±Ç°°æ±¾£ºv1.0
**  ´´½¨ÈÕÆÚ: 2012.08.06
**  ÎÄ¼şËµÃ÷: ÕâÀïµÄ½Ó¿ÚÖ÷Òª¸ømpi ÊÓÆµ±àÂëÈ¡ÊÓÆµÖ¡µÄÊ±ºòÌî³äÖ¡Í·Ê¹ÓÃµÄ
			ÕâĞ©½Ó¿ÚÆäÊµ¿ÉÒÔÓÃ paramManage.h ÀïÃæµÄ½Ó¿ÚÊµÏÖ,µ«ÊÇÓÉÓÚÊ¹ÓÃ
			ÆµÂÊ·Ç³£¸ß,Ã¿¸öÍ¨µÀµÄÃ¿Ò»Ö¡¶¼ÓÃµ½,paramManage.h ÀïÃæµÄ½Ó¿Ú¶¼
			Éæ¼°µ½¼ÓËø½âËø¶¯×÷,Ğ§ÂÊÓĞµãµÍ,ËùÒÔ×¨ÃÅÊ¹ÓÃ±»ÎÄµµµÄ½Ó¿Ú
*******************************************************************************
*/

#include "paramManage.h"
#include "vencParamEasy.h"
#include "debug.h"

/* ===== video ===== */
static VIDEO_HEAD_LOCAL_T g_videoHeadLocal;

uchar VencParamEasyGetVideoStandard()
{
	return g_videoHeadLocal.videoStandard;
}

uchar VencParamEasyGetResolution( int channel )
{
	return g_videoHeadLocal.resolution[channel];
}

uchar VencParamEasyGetFramerate( int channel )
{
	return g_videoHeadLocal.frameRate[channel];
}

void VencParamEasySetVideoStandard( uchar val )
{
	g_videoHeadLocal.videoStandard = val;
}

void VencParamEasySetResolution( int channel, uchar val )
{
	g_videoHeadLocal.resolution[channel] = val;
}

void VencParamEasySetFramerate( int channel, uchar val )
{
	g_videoHeadLocal.frameRate[channel] = val;
}

static int VencParamEasyInit()
{
	int ret, i;
	PARAM_CONFIG_VIDEO_ENCODE_PUBLIC vepp;
	PARAM_CONFIG_VIDEO_ENCODE vep;
	
	ret = ParamGetVideoEncodePublic( &vepp );
	if( 0 == ret )
	{
		g_videoHeadLocal.videoStandard = vepp.videoStandard;
	}
	for( i = 0; i < REAL_CHANNEL_NUM; ++i )
	{
		ret = ParamGetVideoEncode( i, &vep );
		if( 0 == ret )
		{
			g_videoHeadLocal.resolution[i]	= vep.resolution;		
			g_videoHeadLocal.frameRate[i] 	= vep.frameRate;
		}
	}
	return ret;
}

/* ===== audio ===== */

static AUDIO_HEAD_LOCAL_T g_audioHeadLocal;

uchar VencParamEasyGetAudioSampleRate()
{
	return g_audioHeadLocal.sampleRate;
}

uchar VencParamEasyGetAudioBitWidth()
{
	return g_audioHeadLocal.bitWidth;
}

uchar VencParamEasyGetAudioEncodeType()
{
	return g_audioHeadLocal.encodeType;             //MARK: 20171101 ä¿®æ”¹å€¼ï¼Œå›æ”¾éŸ³é¢‘è¿˜æ˜¯æœ‰é”™è¯¯
 }

uchar VencParamEasyGetAudioChMode()
{
	return g_audioHeadLocal.chMode;
}

void VencParamEasySetAudioSampleRate( uchar val )
{
	g_audioHeadLocal.sampleRate = val;
}

void VencParamEasySetAudioBitWidth( uchar val )
{
	g_audioHeadLocal.bitWidth = val;
}

void VencParamEasySetAudioEncodeType( uchar val )
{
	g_audioHeadLocal.encodeType = val;
}

void VencParamEasySetAudioChMode( uchar val )
{
	g_audioHeadLocal.chMode = val;
}

static int AudioParamEasyInit()
{
	int ret;
	PARAM_CONFIG_AUDIO_ENCODE param;
	ret = ParamGetAudio( &param );
	if( 0 == ret )
	{
		VencParamEasySetAudioSampleRate( param.sampleRate );
		VencParamEasySetAudioBitWidth( param.bitWidth );
		VencParamEasySetAudioEncodeType( param.encodeType );
		VencParamEasySetAudioChMode( param.chMode );
	}
	return ret;
}

int ParamEasyInit()
{
	int ret = -1;
	ret = VencParamEasyInit();
	ret = AudioParamEasyInit();

	
    RtPrint( ret, "[03] %s [%s:%d]\n", __FUNCTION__, __FILE__, __LINE__ );
	return ret;
}

