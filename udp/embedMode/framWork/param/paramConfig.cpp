#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "rand.h"
#include "malloc.h"
#include "md5.h"
#include "timer.h"
#include "flash.h"
#include "message.h"
#include "public.h"
#include "paramConfig.h"
#include "vencParamEasy.h"
#include "dcpInsLocal.h"

static CMutexLock g_MutexConfig;
static SYS_CONFIG g_sysConfig;//系统全局变量配置初始化
static int SyncParamConfigOnlyConfig();
static int SyncParamConfigOnlyConfigBack();

static void SysConfigInitHead( PARAM_CONFIG_HEAD *pHead )
{
    if( NULL !=  pHead )
    {
        memset( pHead, 0x00, sizeof( *pHead ) );
        memcpy( pHead->signature, PARAM_CONFIG_SIGNATURE, sizeof( pHead->signature ) );
    }
}

static void SysConfigInitBaseInfo( PARAM_CONFIG_BASE_INFO *pBaseInfo )
{
    if( NULL != pBaseInfo )
    {
        memset( pBaseInfo, 0x00, sizeof( *pBaseInfo ) );
        strncpy( pBaseInfo->devModel, DEV_MODEL, sizeof( pBaseInfo->devModel ) - 1 );
        strncpy( pBaseInfo->serialNo, DEV_SERIAL_NUM, sizeof( pBaseInfo->serialNo ) - 1 );
        strncpy( pBaseInfo->hardwareVersion, DEV_HARDWARE_VERSION, sizeof( pBaseInfo->serialNo ) - 1 );
        strncpy( pBaseInfo->softwareVersion, DEV_SOFTWARE_VERSION, sizeof( pBaseInfo->serialNo ) - 1 );
        strncpy( pBaseInfo->configureVersion, DEV_CONFIG_VERSION, sizeof( pBaseInfo->serialNo ) - 1 );
        pBaseInfo->chipNum          = DEV_CHIP_NUM;
        pBaseInfo->channelNum       = REAL_CHANNEL_NUM;
        pBaseInfo->videoInputNum    = DEV_VIDEO_IN_NUM;
        pBaseInfo->videoOutputNum   = DEV_VIDEO_OUT_NUM;
        pBaseInfo->alarmInputNum    = DEV_ALARM_IN_NUM;
        pBaseInfo->alarmOutputNum   = DEV_ALARM_OUT_NUM;
    }
}

static void SysConfigInitNetWork( PARAM_CONFIG_NETWORK *pNework )
{
    PARAM_CONFIG_NETWORK tmpNetWork;
    tmpNetWork = g_sysConfig.network;
    if( NULL != pNework )
    {
		
        memset( pNework, 0x00, sizeof( *pNework ) );
        pNework->wired.enableFlag = FI_FALSE;
		strcpy( pNework->wired.mac, PARAM_CONFIG_DEFAULT_MAC );
#if defined WATERPROOF_SENSOR_F22_MIPI_1080P_30FPS
		unsigned char mac[2];
        mac[0] = ( unsigned char )RandAb( 0x01, 0xFE );
        mac[1] = ( unsigned char )RandAb( 0x01, 0xFE );
        snprintf( pNework->wired.mac + 12, 3, "%02X", mac[0] );
        *(pNework->wired.mac + 12 + 2) = ':';
        snprintf( pNework->wired.mac + 15, 3, "%02X", mac[1] );
#endif
        strcpy( pNework->wired.ip, DEV_DEFAULT_IP );
        strcpy( pNework->wired.netmask, DEV_DEFAULT_NETMASK );
        strcpy( pNework->wired.gateway, DEV_DEFAULT_GATEWAY );
        strcpy( pNework->wired.broadAddr, DEV_DEFAULT_BROADADDR );
        pNework->wifi.dhcpEnable = FI_TRUE;// 第二次启动直接dhcp
        pNework->wifi.enableFlag = FI_FALSE;// 默认wifi是没开的,所以第一次smartlink
        strcpy( pNework->wifi.ip, DEV_DEFAULT_IP );
        strcpy( pNework->wifi.netmask, DEV_DEFAULT_NETMASK );
        strcpy( pNework->wifi.gateway, DEV_DEFAULT_GATEWAY );
        strcpy( pNework->wifi.broadAddr, DEV_DEFAULT_BROADADDR );
        strcpy( pNework->dns.dns1, DEV_DEFAULT_DNS1 );
        strcpy( pNework->dns.dns2, DEV_DEFAULT_DNS2 );
        pNework->port.webPort       = DEV_DEFAULT_WEBPORT;
        pNework->port.msgPort       = DEV_DEFAULT_MSG_PORT;
        pNework->port.searchPort    = DEV_DEFAULT_SEARCH_PORT;
        // Mac 赋值随机内存
        strcpy( pNework->wired.mac, tmpNetWork.wired.mac );
        strcpy( pNework->wifi.mac, tmpNetWork.wifi.mac );
    }
}

static void SysConfigInitUser( PARAM_CONFIG_CLIENT_USER *pUser )
{
    int i;
    if( NULL != pUser )
    {
        memset( pUser, 0x00, sizeof( PARAM_CONFIG_CLIENT_USER ) * MAX_CLIENT_USER_NUM );
        for( i = 0; i < MAX_CLIENT_USER_NUM; i++ )
        {
            if( 0 == i )
            {
                strcpy( pUser->name, DEV_DEFAULT_USER_NAME );
                strcpy( pUser->pwd, DEV_DEFAULT_USER_PWD );
                pUser->permission   = DEV_DEFAULT_USER_PERMISSION;
                pUser->level        = DEV_DEFAULT_USER_LEVEL;
                pUser->enable       = FI_TRUE;
                break; //默认只有admin用户
            }
        }
    }
}

static void SysConfigInitVideoBaseParam( PARAM_CONFIG_VIDEO_BASE_PARAM *pVideoBaseParam )
{
    int i;
    if( NULL != pVideoBaseParam )
    {
        memset( pVideoBaseParam, 0x00, sizeof( *pVideoBaseParam ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; ++i )
        {
            pVideoBaseParam->brightness = DEV_DEFAULT_VIDEO_BRIGHTNESS;
            pVideoBaseParam->contrast   = DEV_DEFAULT_VIDEO_CONTRAST;
            pVideoBaseParam->saturation = DEV_DEFAULT_VIDEO_SATURATION;
            pVideoBaseParam->exposure   = DEV_DEFAULT_VIDEO_EXPOSURE;
            pVideoBaseParam->hue        = DEV_DEFAULT_VIDEO_HUE;
#if defined WATERPROOF_SENSOR_F22_MIPI_1080P_30FPS														
			//pVideoBaseParam->rotate     = 1;
			pVideoBaseParam->flip     = 7; // 设置画面翻转应该使用flip。
#else
			pVideoBaseParam->flip     = 4; // 初始不翻转。
#endif
			pVideoBaseParam->enbale_LDC = 0; //初始不打开LDC
            pVideoBaseParam++;
        }
    }
}

static void SysConfigInitOsdLogo( PARAM_CONFIG_OSD_LOGO *pOsdLogo )
{
    int i;
    if( NULL != pOsdLogo )
    {
        memset( pOsdLogo, 0x00, sizeof( *pOsdLogo ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; i++ )
        {
            pOsdLogo->enable = 1;
            pOsdLogo->colorRed = 0;
            pOsdLogo->colorGreen = 0;
            pOsdLogo->colorBlue = 0;
            pOsdLogo->xPos = 0;
            pOsdLogo->yPos = 0;
            pOsdLogo->bgTransparence = 100;
            pOsdLogo->fontSize = FONT_SIZE_H32;//FONT_SIZE_H16;
            //sprintf( pOsdLogo->logo, "通道%d", i );
            //sprintf( pOsdLogo->logo, " ", i );
            pOsdLogo->rotate = 0;
            pOsdLogo->enable = 0;	
            pOsdLogo++;
        }
    }
}

static void SysConfigInitOsdTime( PARAM_CONFIG_OSD_TIME *pOsdTime )
{
    int i;
    if( NULL != pOsdTime )
    {
        memset( pOsdTime, 0x00, sizeof( *pOsdTime ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; i++ )
        {
            pOsdTime->enable = 1;
            pOsdTime->colorRed = 0;
            pOsdTime->colorGreen = 0;
            pOsdTime->colorBlue = 0;
            pOsdTime->xPos = 50;// 100
            //pOsdTime->xPos = 100;// 100
            pOsdTime->yPos = 0;
            pOsdTime->bgTransparence = 100;//透明度
            if(i == 0)
            	pOsdTime->fontSize = FONT_SIZE_H32;
            else
				pOsdTime->fontSize = FONT_SIZE_H16;//FONT_SIZE_H32;
            pOsdTime->rotate = 0;
            pOsdTime->enable = 1;
            pOsdTime++;
        }
    }
}

static void SysConfigInitVideoEncodePublic( PARAM_CONFIG_VIDEO_ENCODE_PUBLIC *pVideoEncodePublic )
{
    if( NULL != pVideoEncodePublic )
    {
        memset( pVideoEncodePublic, 0x00, sizeof( *pVideoEncodePublic ) );
        pVideoEncodePublic->videoStandard = DEV_DEFAULT_VIDEO_ENCODE_STANDARD;
    }
}
static void SysConfigInitVideoEncode( PARAM_CONFIG_VIDEO_ENCODE *pVideoEncode )
{
    int i;
    if( NULL != pVideoEncode )
    {
        memset( pVideoEncode, 0x00, sizeof( *pVideoEncode ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; ++i )
        {
#if 1
            switch( i )
            {
                case 0:
#if defined SENSOR_H42_MIPI_720P_30FPS || defined SENSOR_H62_MIPI_720P_30FPS
                   pVideoEncode->resolution    = VIDEO_ENCODE_RESOLUTION_HD720;
#elif defined SENSOR_F22_MIPI_1080P_30FPS
                   pVideoEncode->resolution    = VIDEO_ENCODE_RESOLUTION_HD1080;
#endif
                    pVideoEncode->bitrate       = DEV_DEFAULT_VIDEO_ENCODE_BITRATE;//比特率
                    pVideoEncode->encodeType    = DEV_DEFAULT_VIDEO_ENCODE_TYPE;// 音视频
                    break;
                case 1:
                    pVideoEncode->resolution    = VIDEO_ENCODE_RESOLUTION_VGA;
                    pVideoEncode->bitrate       = DEV_DEFAULT_VIDEO_ENCODE_BITRATE >> 1;
                    pVideoEncode->encodeType    = DEV_DEFAULT_VIDEO_ENCODE_TYPE;
                    break;
                case 2:
                    pVideoEncode->resolution    = VIDEO_ENCODE_RESOLUTION_QVGA;
                    pVideoEncode->bitrate       = DEV_DEFAULT_VIDEO_ENCODE_BITRATE;
                    pVideoEncode->encodeType    = VIDEO_ENCODE_TYPE_V;
                    break;
                case 3:
                default: 
#if defined SENSOR_H42_MIPI_720P_30FPS || defined SENSOR_H62_MIPI_720P_30FPS
					pVideoEncode->resolution    = VIDEO_ENCODE_RESOLUTION_HD720;
#elif defined SENSOR_F22_MIPI_1080P_30FPS
                    pVideoEncode->resolution    = VIDEO_ENCODE_RESOLUTION_HD1080;
#endif
                    pVideoEncode->bitrate       = DEV_DEFAULT_VIDEO_ENCODE_BITRATE;
                    pVideoEncode->encodeType    = VIDEO_ENCODE_TYPE_V;
                    break;
            }
#else
            pVideoEncode->resolution        = DEV_DEFAULT_VIDEO_ENCODE_RESOLUTION;
#endif
            pVideoEncode->bitrateType       = DEV_DEFAULT_VIDEO_ENCODE_BITRATETYPE;// 码率类型
            pVideoEncode->frameRate         = DEV_DEFAULT_VIDEO_ENCODE_FRAMERATE;// 帧率
            pVideoEncode->iFrameInterval    = DEV_DEFAULT_VIDEO_ENCODE_IFRAMEINTERVAL;// I帧间隔
            pVideoEncode->preferFrame       = DEV_DEFAULT_VIDEO_ENCODE_PREFERFRAME;
            pVideoEncode++;
        }
    }
}
static void SysConfigInitVideoEncodeSlave( PARAM_CONFIG_VIDEO_ENCODE *pVideoEncodeSlave )
{
    int i;
    if( NULL != pVideoEncodeSlave )
    {
        memset( pVideoEncodeSlave, 0x00, sizeof( *pVideoEncodeSlave ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; ++i )
        {
            pVideoEncodeSlave->resolution       = VIDEO_ENCODE_RESOLUTION_CIF;
            pVideoEncodeSlave->bitrateType      = DEV_DEFAULT_VIDEO_ENCODE_BITRATETYPE;
            pVideoEncodeSlave->bitrate          = DEV_DEFAULT_VIDEO_ENCODE_BITRATE;
            pVideoEncodeSlave->frameRate        = DEV_DEFAULT_VIDEO_ENCODE_FRAMERATE;
            pVideoEncodeSlave->iFrameInterval   = DEV_DEFAULT_VIDEO_ENCODE_IFRAMEINTERVAL;
            pVideoEncodeSlave->preferFrame      = DEV_DEFAULT_VIDEO_ENCODE_PREFERFRAME;
            pVideoEncodeSlave->encodeType       = DEV_DEFAULT_VIDEO_ENCODE_TYPE;
            pVideoEncodeSlave++;
        }
    }
}

static void SysConfigInitAudioEncode( PARAM_CONFIG_AUDIO_ENCODE *pAudioEncode )
{
    if( NULL != pAudioEncode )
    {
        memset( pAudioEncode, 0x00, sizeof( *pAudioEncode ) );
        pAudioEncode->sampleRate    = DEV_DEFAULT_AUDIO_ENCODE_SAMPLE_RATE;
        pAudioEncode->bitWidth      = DEV_DEFAULT_AUDIO_ENCODE_SAMPLE_WIDTH;
        pAudioEncode->encodeType    = DEV_DEFAULT_AUDIO_ENCODE_TYPE;
        pAudioEncode->chMode        = DEV_DEFAULT_AUDIO_ENCODE_CHANNEL_MODE;
        pAudioEncode->amrMode       = DEV_DEFAULT_AUDIO_ENCODE_AMR_MODE;
        pAudioEncode->amrFormat     = DEV_DEFAULT_AUDIO_ENCODE_AMR_FORMAT;

#if defined WATERPROOF_SENSOR_F22_MIPI_1080P_30FPS	
	    pAudioEncode->inputVol      = 0x20;/*0x00~0x7e, 0x7F:mute*/
        pAudioEncode->inputMute     = DEV_DEFAULT_AUDIO_ENCODE_UNMUTE;
        pAudioEncode->outputVol     = 0x02;/*0x00~0x7e, 0x7F:mute*/
        pAudioEncode->outputMute    = DEV_DEFAULT_AUDIO_ENCODE_UNMUTE;
#else
	    pAudioEncode->inputVol      = 0x20;/*0x00~0x7e, 0x7F:mute*/
        pAudioEncode->inputMute     = DEV_DEFAULT_AUDIO_ENCODE_UNMUTE;
        pAudioEncode->outputVol     = 0x08;/*0x00~0x7e, 0x7F:mute*/
        pAudioEncode->outputMute    = DEV_DEFAULT_AUDIO_ENCODE_UNMUTE;
#endif		
    }
}

static void SysConfigInitAutoMaintain( PARAM_CONFIG_AUTO_MAINTAIN *pAutoMaintion )
{
    if( NULL != pAutoMaintion )
    {
        memset( pAutoMaintion, 0x00, sizeof( *pAutoMaintion ) );
    }
}

static void SysConfigInitRecordPublic( PARAM_CONFIG_RECORD_PUBLIC *pRecordPublic )
{
    if( NULL != pRecordPublic )
    {
        memset( pRecordPublic, 0x00, sizeof( *pRecordPublic ) );
#if 1
        pRecordPublic->loopRecord   = FI_TRUE;
        pRecordPublic->preRecord    = FI_TRUE;
#endif
        pRecordPublic->delSize         = DEV_DEFAULT_RECORD_PUBLIC_DEL_SIZE;
        pRecordPublic->delSpace     = DEV_DEFAULT_RECORD_PUBLIC_DEL_SPACE;
        pRecordPublic->switchFileTime   = DEV_DEFAULT_RECORD_PUBLIC_SWITCH_FILE_TIME;
       pRecordPublic->audFlag                 = DEV_DEFAULT_RECORD_PUBLIC_AUDIO_FLAG;
    }
}

static void SysConfigInitRecordParam( PARAM_CONFIG_RECORD_PARAM *pRecordParam )
{
    int i = 0;
    if( NULL != pRecordParam )
    {
        memset( pRecordParam, 0x00, sizeof( *pRecordParam ) * MAX_CHANNEL_NUM );
        for(i = 0; i < MAX_CHANNEL_NUM; i++)
        {
            pRecordParam->recHand.recFlag = DEV_DEFAULT_RECORD_PUBLIC_HANDRECORD_FLAG;
            pRecordParam = pRecordParam + 1 ;
        }
#if 0
        for( k = 0; k < MAX_CHANNEL_NUM; ++k )
        {
            for( i = 0; i < MAX_WEEK_DAY; ++i )
            {
                pRecordParam->recTimer.day[i].enableFlag = FI_TRUE;
                for( j = 0; j < MAX_DAY_TIME_SEG; ++j )
                {
                    pRecordParam->recTimer.day[i].timeSeg[j].timeStart.hour     = 0;
                    pRecordParam->recTimer.day[i].timeSeg[j].timeStart.minute   = 0;
                    pRecordParam->recTimer.day[i].timeSeg[j].timeStart.second   = 0;
                    pRecordParam->recTimer.day[i].timeSeg[j].timeEnd.hour       = 23;
                    pRecordParam->recTimer.day[i].timeSeg[j].timeEnd.minute     = 59;
                    pRecordParam->recTimer.day[i].timeSeg[j].timeEnd.second     = 59;
                }
            }
            pRecordParam++;
        }
#endif
    }
}

static void SysConfigInitAlarmIo( PARAM_CONFIG_ALARM_IO *pAlarmIo )
{
    if( NULL != pAlarmIo )
    {
        memset( pAlarmIo, 0x00, sizeof( *pAlarmIo ) );
        pAlarmIo->scoutInterval = 100;
        pAlarmIo->armFlag = 1;
    }
}

static void SysConfigInitSerial( PARAM_CONFIG_SERIAL *pSerial )
{
    if( NULL != pSerial )
    {
        memset( pSerial, 0x00, sizeof( *pSerial ) );
        pSerial->ptz.comNum     = 1;
        pSerial->ptz.baudRate   =  DEV_DEFAULT_SERIAL_BAUDRATE;
        pSerial->ptz.dataBits   = DEV_DEFAULT_SERIAL_DATABITS;
        pSerial->ptz.stopBits   = DEV_DEFAULT_SERIAL_STOPBITS;
        pSerial->ptz.parity     = DEV_DEFAULT_SERIAL_PARITY;
    }
}

static void SysConfigInitNtp( PARAM_CONFIG_NTP *pNtp )
{
    if( NULL != pNtp )
    {
        memset( pNtp, 0x00, sizeof( *pNtp ) );
        pNtp->enable    = PARAM_CONFIG_DEFAULT_NTP_ENABLE_FLAG;
        pNtp->interval  = PARAM_CONFIG_DEFAULT_NTP_INTERVAL;
        pNtp->zone      = PARAM_CONFIG_DEFAULT_NTP_ZONE;
        strncpy( pNtp->host, PARAM_CONFIG_DEFAULT_NTP_ADDR, sizeof( pNtp->host ) );
    }
}

static void SysConfigInitEmail( PARAM_CONFIG_EMAIL *pEmail )
{
    if( NULL != pEmail )
    {
        memset( pEmail, 0x00, sizeof( *pEmail ) );
        pEmail->port = 25;
    }
}

static void SysConfigInitAlarmMoveDetect( PARAM_CONFIG_ALARM_MOVE_DETECT *pAlarmMoveDetect )
{
    int i, j;
    if( NULL != pAlarmMoveDetect )
    {
        memset( pAlarmMoveDetect, 0x00, sizeof( *pAlarmMoveDetect ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; i++ )
        {
            pAlarmMoveDetect->armFlag           = FI_FALSE;	//FI_TRUE;
            pAlarmMoveDetect->sensitiveLevel    = PARAM_CONFIG_DEFAULT_MOVE_DETECT_SENSITIVITY;
            pAlarmMoveDetect->scoutInterval     = PARAM_CONFIG_DEFAULT_MOVE_DETECT_INTERVAL;
            pAlarmMoveDetect->linkage.linkageAlarmOut   = PARAM_CONFIG_DEFAULT_MOVE_DETECT_LINKALARMOUT;
            pAlarmMoveDetect->linkage.alarmOutDuration  = PARAM_CONFIG_DEFAULT_MOVE_DETECT_ALARMOUTDURATION;
            pAlarmMoveDetect->linkage.linkageCapture    = PARAM_CONFIG_DEFAULT_MOVE_DETECT_LINKCAPTURE;
            pAlarmMoveDetect->linkage.captureNum        = PARAM_CONFIG_DEFAULT_MOVE_DETECT_CAPTURENUM;
            pAlarmMoveDetect->linkage.linkageRecord     = PARAM_CONFIG_DEFAULT_MOVE_DETECT_LINKRECORD;
            pAlarmMoveDetect->linkage.recordDuration    = PARAM_CONFIG_DEFAULT_MOVE_DETECT_RECORDDURATION;
            //for( j = 0; j < 12; ++j )
            //{
            //    pAlarmMoveDetect->detectArea.area[j] = 0xFFFF;
            //}
            for(i= 0;i <36; i ++)
			{
				for(j = 0; j < 45; j++)
				{
					pAlarmMoveDetect->detectArea.area[i][j] = 1;
				}
			}
            pAlarmMoveDetect++;
        }
    }
}

static void SysConfigInitVideoOverlay( PARAM_CONFIG_VIDEO_OVERLAY *pVideoOverlay )
{
    int i, j;
    if( NULL != pVideoOverlay )
    {
        memset( pVideoOverlay, 0x00, sizeof( *pVideoOverlay ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; i++ )
        {
            pVideoOverlay->enable   = FI_TRUE;
            pVideoOverlay->num      = MAX_OVERLAY_NUM_ECHE_CHANNEL;
            for( j = 0; j < MAX_OVERLAY_NUM_ECHE_CHANNEL; j++ )
            {
                pVideoOverlay->overlay[j].color     = j % 2;
                pVideoOverlay->overlay[j].x_start   = j * 16 + 8;
                pVideoOverlay->overlay[j].y_start   = j * 16 + 8;
                pVideoOverlay->overlay[j].width     = 32;
                pVideoOverlay->overlay[j].height    = 32;
            }
            pVideoOverlay++;
        }
    }
}

static void SysConfigInitAlarmVideoLose( PARAM_CONFIG_ALARM_VIDEO_LOSE *pAlarmVideoLose )
{
    int i;
    if( NULL != pAlarmVideoLose )
    {
        memset( pAlarmVideoLose, 0x00, sizeof( *pAlarmVideoLose ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; ++i )
        {
            pAlarmVideoLose[i].armFlag = FI_TRUE;
            pAlarmVideoLose[i].scoutInterval = 1;
        }
    }
}

static void SysConfigInitFtp( PARAM_CONFIG_FTP *pFtp )
{
    uint i;
    if( NULL != pFtp )
    {
        memset( pFtp, 0x00, sizeof( *pFtp ) );
        pFtp->enable = PARAM_CONFIG_DEFAULT_FTP_ENABLE;
        pFtp->port = PARAM_CONFIG_DEFAULT_FTP_PORT;
        strncpy( pFtp->ip, PARAM_CONFIG_DEFAULT_FTP_IP, sizeof( pFtp->ip ) );
        strncpy( pFtp->user, PARAM_CONFIG_DEFAULT_FTP_USER, sizeof( pFtp->user ) );
        strncpy( pFtp->passwd, PARAM_CONFIG_DEFAULT_FTP_PASSWD, sizeof( pFtp->passwd ) );
        for( i = 0; i < sizeof( pFtp->jpgUpChannel ); ++i )
        {
            pFtp->jpgUpChannel[i] = PARAM_CONFIG_DEFAULT_FTP_UP;
        }
    }
}

static void SysConfigInitSnapTimer( PARAM_CONFIG_SNAP_TIMER *pSnapTimer )
{
    int i;
    if( NULL != pSnapTimer )
    {
        memset( pSnapTimer, 0x00, sizeof( *pSnapTimer ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; ++i )
        {
            pSnapTimer[i].enable    = 1;
            pSnapTimer[i].interval  = 10;
            strcpy( pSnapTimer[i].startTime, "00:00:00" );
            strcpy( pSnapTimer[i].stopTime, "23:59:59" );
        }
    }
}


static void SysConfigInitIcmp( PARAM_CONFIG_ICMP *pIcmp )
{
    if( NULL != pIcmp )
    {
        memset( pIcmp, 0x00, sizeof( *pIcmp ) );
        pIcmp->enable       = FI_TRUE;
        strcpy( pIcmp->ipAddr,  PARAM_CONFIG_DEFAULT_ICMP_IPADDR );
        pIcmp->interval     = PARAM_CONFIG_DEFAULT_ICMP_INTERVAL;
        pIcmp->timeOut      = PARAM_CONFIG_DEFAULT_ICMP_TIMEOUT;
        pIcmp->fcount       = PARAM_CONFIG_DEFAULT_ICMP_FCOUNT;
        pIcmp->finterval    = PARAM_CONFIG_DEFAULT_ICMP_FINTERVAL;
    }
}

static void SysConfigInitDdns( PARAM_CONFIG_DDNS *pDdns )
{
    if( NULL != pDdns )
    {
        memset( pDdns, 0x00, sizeof( *pDdns ) );
        pDdns->enable   = FI_TRUE;
        pDdns->vender   = PARAM_CONFIG_DEFAULT_DNS_VENDER;
        pDdns->port     = PARAM_CONFIG_DEFAULT_DNS_PORT;
        pDdns->interval = PARAM_CONFIG_DEFAULT_DNS_INTERVAL;
        strcpy( pDdns->userName,    PARAM_CONFIG_DEFAULT_DNS_USERNAME );
        strcpy( pDdns->passwd,  PARAM_CONFIG_DEFAULT_DNS_PASSWD );
        strcpy( pDdns->url, PARAM_CONFIG_DEFAULT_DNS_URL );
        strcpy( pDdns->ifName, PARAM_CONFIG_DEFAULT_DNS_IFNAME );
    }
}

static void SysConfigInitDtu( PARAM_CONFIG_DTU *pDtu )
{
    if( NULL != pDtu )
    {
        memset( pDtu, 0x00, sizeof( *pDtu ) );
        pDtu->enable        = FI_TRUE;
        pDtu->transProtocol = PARAM_CONFIG_DEFAULT_DTU_PROTOCOL;
        pDtu->serverPort    = PARAM_CONFIG_DEFAULT_DTU_SERVERPORT;
        pDtu->interval      = PARAM_CONFIG_DEFAULT_DTU_HEARTBEAT;
        strcpy( pDtu->severIp, PARAM_CONFIG_DEFAULT_DTU_SERVERIP );
        strcpy( pDtu->heartbeatContent, PARAM_CONFIG_DEFAULT_DTU_CONTENT );
    }
}

static void SysConfigInitWifiConnect( PARAM_CONFIG_WIFI_CONNECT_T *pWifiConnect )
{
    if( NULL != pWifiConnect )
    {
        memset( pWifiConnect, 0x00, sizeof( *pWifiConnect ) );
        pWifiConnect->connectFlag = 0;
		pWifiConnect->encryptionkey = 0;
		pWifiConnect->wifiConnect = 0;
    }
}

static void SysConfigInitThreeg( PARAM_CONFIG_THREEG_T *pThreeg )
{
    if( NULL != pThreeg )
    {
        memset( pThreeg, 0x00, sizeof( *pThreeg ) );
    }
}

static void SysConfigInitVideoShelter( PARAM_CONFIG_ALARM_VIDEO_SHELTER *pVideoShelter )
{
    int i;
    if( NULL != pVideoShelter )
    {
        memset( pVideoShelter, 0x00, sizeof( *pVideoShelter ) * MAX_CHANNEL_NUM );
        for( i = 0; i < MAX_CHANNEL_NUM; ++i )
        {
            pVideoShelter[i].armFlag = FI_TRUE;
            pVideoShelter[i].scoutInterval = 1;
            pVideoShelter[i].sensitivity = VIDEO_SHELTER_SENSITIVITY_2;
            pVideoShelter[i].linkage.linkageBuzzer = 1;
            pVideoShelter[i].linkage.buzzerDuration = 2;
            pVideoShelter[i].linkage.linkageRecord = 0xf;
            pVideoShelter[i].linkage.recordDuration = 6;
        }
    }
}

static void SysConfigInitDiskInit( PARAM_CONFIG_DISK_INIT *pDiskInit )
{
    if( NULL != pDiskInit )
    {
        memset( pDiskInit, 0x00, sizeof( *pDiskInit ) );
    }
}

static void SysConfigInitSendRtp( PARAM_CONFIG_SEND_RTP_T *pSendRtp )
{
    if( NULL != pSendRtp )
    {
        memset( pSendRtp, 0x00, sizeof( *pSendRtp ) );
    }
}

static void SysConfigInitPtz( PARAM_PTZ_INFO_T *pptzInfo )
{
    if( NULL != pptzInfo )
    {
        memset( pptzInfo, 0x00, sizeof( *pptzInfo ) );
		pptzInfo->pose[0].x = 0;
		pptzInfo->pose[0].y = MAX_VL/2;
    }
}


#if 0
static void SysConfigInitWifiList( CONFIG_WIFI_LIST_T *pWifiList )
{
    if( NULL != pWifiList )
    {
        memset( pWifiList, 0x00, sizeof( *pWifiList ) );
    }
}
#endif
/*
* SYS_CONFIG每添加一个成员都要修改下面两个函数
*/
PARAM_CONFIG_STORE_HEAD g_storeHead;// 512字节
static void SysConfigInitStoreHead( PARAM_CONFIG_STORE_HEAD *pStoreHead )
{
    if( NULL != pStoreHead )
    {
        memcpy( pStoreHead->mark, PARAM_CONFIG_MARK, 16 );
        pStoreHead->size            = sizeof( g_sysConfig );
        pStoreHead->totalMembers    = INDEX_PARAM_CONFIG_TOTAL;
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_HEAD] = sizeof( g_sysConfig.head );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_BASE_INFO] = sizeof( g_sysConfig.baseInfo );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_NETWORK] = sizeof( g_sysConfig.network );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_CLIENT_USER] = sizeof( g_sysConfig.user );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_VIDEO_ENCODE_PUBLIC] = sizeof( g_sysConfig.videoEncodePublic );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_VIDEO_ENCODE] = sizeof( g_sysConfig.videoEncode );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_VIDEO_ENCODE_SLAVE] = sizeof( g_sysConfig.videoEncodeSlave );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_VIDEO_BASE_PARAM] = sizeof( g_sysConfig.videoBaseParam );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_OSD_LOGO] = sizeof( g_sysConfig.osdLogo );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_OSD_TIME] = sizeof( g_sysConfig.osdTime );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_AUDIO] = sizeof( g_sysConfig.audioEncode );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_AUTO_MAINTAIN] = sizeof( g_sysConfig.autoMaintion );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_RECORD_PUBLIC] = sizeof( g_sysConfig.recordPublic );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_RECORD_PARAM] = sizeof( g_sysConfig.recordParam );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_ALARM_IO] = sizeof( g_sysConfig.alarmIo );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_SERIAL] = sizeof( g_sysConfig.serial );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_NTP] = sizeof( g_sysConfig.ntp );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_EMAIL] = sizeof( g_sysConfig.email );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_ALARM_MOVE_DETECT] = sizeof( g_sysConfig.alarmMoveDetect );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_VIDEO_OVERLAY] = sizeof( g_sysConfig.videoOverlay );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_ALARM_VIDEO_LOSE] = sizeof( g_sysConfig.alarmVideoLose );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_FTP]  = sizeof( g_sysConfig.ftpParam );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_SNAP_TIMER]  = sizeof( g_sysConfig.snapTimer );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_ICMP] = sizeof( g_sysConfig.icmp );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_DDNS] = sizeof( g_sysConfig.ddns );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_DTU] = sizeof( g_sysConfig.dtu );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_WIFI_CONNECT] = sizeof( g_sysConfig.wifiConnect );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_THREEG] = sizeof( g_sysConfig.threeg );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_VIDEO_SHELTER] = sizeof( g_sysConfig.videoShelter );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_DISK_INIT] = sizeof( g_sysConfig.diskInit );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_SEND_RTP] = sizeof( g_sysConfig.sendRtp );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_ERRORFILE_PATH] = sizeof( g_sysConfig.errorFilePath );
        pStoreHead->memberSize[INDEX_PARAM_CONFIG_PTZ] = sizeof( g_sysConfig.ptzInfo );
        //pStoreHead->memberSize[INDEX_PARAM_CONFIG_WIFI_LIST] = sizeof( g_sysConfig.wifiList );
    }
}

//恢复默认配置
void SysConfigpRestoreDefaultParam()
{
    g_MutexConfig.Lock();
    // 视频
    SysConfigInitVideoBaseParam( g_sysConfig.videoBaseParam );
    SysConfigInitVideoEncodePublic( &g_sysConfig.videoEncodePublic );
    SysConfigInitVideoEncode( g_sysConfig.videoEncode );
    SysConfigInitVideoEncodeSlave( g_sysConfig.videoEncodeSlave );
    // 音频
    SysConfigInitAudioEncode( &g_sysConfig.audioEncode );
    // 录像
    SysConfigInitRecordPublic( &g_sysConfig.recordPublic );
    SysConfigInitRecordParam( g_sysConfig.recordParam );
    SysConfigInitDiskInit( &g_sysConfig.diskInit );
    // OSD
    SysConfigInitOsdLogo( g_sysConfig.osdLogo );
    SysConfigInitOsdTime( g_sysConfig.osdTime );
    // 移动侦测
    SysConfigInitAlarmIo( &g_sysConfig.alarmIo );
    SysConfigInitAlarmMoveDetect( g_sysConfig.alarmMoveDetect );
    // 遮挡(视频丢失)报警
    SysConfigInitVideoOverlay( g_sysConfig.videoOverlay );
    SysConfigInitAlarmVideoLose( g_sysConfig.alarmVideoLose );
    SysConfigInitVideoShelter( g_sysConfig.videoShelter );
    // 定时抓拍
    SysConfigInitSnapTimer( g_sysConfig.snapTimer );
    // Wifi

	
    SysConfigInitAutoMaintain( &g_sysConfig.autoMaintion );
    SysConfigInitSerial( &g_sysConfig.serial );
    SysConfigInitNtp( &g_sysConfig.ntp );
    SysConfigInitEmail( &g_sysConfig.email );
    SysConfigInitFtp( &g_sysConfig.ftpParam );
    SysConfigInitIcmp( &g_sysConfig.icmp );
    SysConfigInitDdns( &g_sysConfig.ddns );
    SysConfigInitDtu( &g_sysConfig.dtu );
    SysConfigInitThreeg( &g_sysConfig.threeg );
    SysConfigInitSendRtp( &g_sysConfig.sendRtp );
	//PTZ
	SysConfigInitPtz(&g_sysConfig.ptzInfo);
    g_MutexConfig.Unlock();
}

static void SysConfigRestoreFactoryConfNeed()
{
    g_MutexConfig.Lock();
    SysConfigInitStoreHead( &g_storeHead );
    SysConfigInitHead( &g_sysConfig.head );
    SysConfigInitBaseInfo( &g_sysConfig.baseInfo );
    SysConfigInitNetWork( &g_sysConfig.network );
    SysConfigInitUser( g_sysConfig.user );
	SysConfigInitWifiConnect( &g_sysConfig.wifiConnect );
    g_MutexConfig.Unlock();
}

// 恢复出网络以外的基本参数
static void SysConfigRestoreFactoryConfNeedNoNet()
{
    g_MutexConfig.Lock();
    SysConfigInitStoreHead( &g_storeHead );
    SysConfigInitHead( &g_sysConfig.head );
    SysConfigInitBaseInfo( &g_sysConfig.baseInfo );
    SysConfigInitUser( g_sysConfig.user );
    g_MutexConfig.Unlock();
}



//恢复出厂配置
void SysConfigRestoreFactoryConf()
{
    // 基本参数全局变量初始化
    SysConfigRestoreFactoryConfNeed();
    // 音视频等其他全局变量初始化
    SysConfigpRestoreDefaultParam();
}

//恢复除网络参数以外的参数为默认值
void SysConfigSetDefaultParam()
{
    // 基本参数全局变量初始化(除了网络)
    SysConfigRestoreFactoryConfNeedNoNet();
    // 音视频等其他全局变量初始化
    SysConfigpRestoreDefaultParam();
}

static char *g_pMemberAddr[PARAM_CONFIG_MAX_MEMBERS];//指针数组，每一个元素存放一个结构体变量的地址
void SysConfigInitMemberAddr()
{
    g_pMemberAddr[INDEX_PARAM_CONFIG_HEAD]                  = ( char * )&g_sysConfig.head;
    g_pMemberAddr[INDEX_PARAM_CONFIG_BASE_INFO]             = ( char * )&g_sysConfig.baseInfo;
    g_pMemberAddr[INDEX_PARAM_CONFIG_NETWORK]               = ( char * )&g_sysConfig.network;
    g_pMemberAddr[INDEX_PARAM_CONFIG_CLIENT_USER]           = ( char * )g_sysConfig.user;
    g_pMemberAddr[INDEX_PARAM_CONFIG_VIDEO_ENCODE_PUBLIC]   = ( char * )&g_sysConfig.videoEncodePublic;
    g_pMemberAddr[INDEX_PARAM_CONFIG_VIDEO_ENCODE]          = ( char * )g_sysConfig.videoEncode;
    g_pMemberAddr[INDEX_PARAM_CONFIG_VIDEO_ENCODE_SLAVE]    = ( char * )g_sysConfig.videoEncodeSlave;
    g_pMemberAddr[INDEX_PARAM_CONFIG_VIDEO_BASE_PARAM]      = ( char * )g_sysConfig.videoBaseParam;
    g_pMemberAddr[INDEX_PARAM_CONFIG_OSD_LOGO]              = ( char * )g_sysConfig.osdLogo;
    g_pMemberAddr[INDEX_PARAM_CONFIG_OSD_TIME]              = ( char * )g_sysConfig.osdTime;
    g_pMemberAddr[INDEX_PARAM_CONFIG_AUDIO]                 = ( char * )&g_sysConfig.audioEncode;
    g_pMemberAddr[INDEX_PARAM_CONFIG_AUTO_MAINTAIN]         = ( char * )&g_sysConfig.autoMaintion;
    g_pMemberAddr[INDEX_PARAM_CONFIG_RECORD_PUBLIC]         = ( char * )&g_sysConfig.recordPublic;
    g_pMemberAddr[INDEX_PARAM_CONFIG_RECORD_PARAM]          = ( char * )g_sysConfig.recordParam;
    g_pMemberAddr[INDEX_PARAM_CONFIG_ALARM_IO]              = ( char * )&g_sysConfig.alarmIo;
    g_pMemberAddr[INDEX_PARAM_CONFIG_SERIAL]                = ( char * )&g_sysConfig.serial;
    g_pMemberAddr[INDEX_PARAM_CONFIG_NTP]                   = ( char * )&g_sysConfig.ntp;
    g_pMemberAddr[INDEX_PARAM_CONFIG_EMAIL]                 = ( char * )&g_sysConfig.email;
    g_pMemberAddr[INDEX_PARAM_CONFIG_ALARM_MOVE_DETECT]     = ( char * )g_sysConfig.alarmMoveDetect;
    g_pMemberAddr[INDEX_PARAM_CONFIG_VIDEO_OVERLAY]         = ( char * )g_sysConfig.videoOverlay;
    g_pMemberAddr[INDEX_PARAM_CONFIG_ALARM_VIDEO_LOSE]      = ( char * )g_sysConfig.alarmVideoLose;
    g_pMemberAddr[INDEX_PARAM_CONFIG_FTP]                   = ( char * )&g_sysConfig.ftpParam;
    g_pMemberAddr[INDEX_PARAM_CONFIG_SNAP_TIMER]            = ( char * )g_sysConfig.snapTimer;
    g_pMemberAddr[INDEX_PARAM_CONFIG_ICMP]                  = ( char * )&g_sysConfig.icmp;
    g_pMemberAddr[INDEX_PARAM_CONFIG_DDNS]                  = ( char * )&g_sysConfig.ddns;
    g_pMemberAddr[INDEX_PARAM_CONFIG_DTU]                   = ( char * )&g_sysConfig.dtu;
    g_pMemberAddr[INDEX_PARAM_CONFIG_WIFI_CONNECT]          = ( char * )&g_sysConfig.wifiConnect;
    g_pMemberAddr[INDEX_PARAM_CONFIG_THREEG]                = ( char * )&g_sysConfig.threeg;
    g_pMemberAddr[INDEX_PARAM_CONFIG_VIDEO_SHELTER]         = ( char * )g_sysConfig.videoShelter;
    g_pMemberAddr[INDEX_PARAM_CONFIG_DISK_INIT]             = ( char * )&g_sysConfig.diskInit;
    g_pMemberAddr[INDEX_PARAM_CONFIG_SEND_RTP]              = ( char * )&g_sysConfig.sendRtp;
    g_pMemberAddr[INDEX_PARAM_CONFIG_ERRORFILE_PATH]        = ( char * )&g_sysConfig.errorFilePath;
    g_pMemberAddr[INDEX_PARAM_CONFIG_PTZ]              		= ( char * )&g_sysConfig.ptzInfo;
    //g_pMemberAddr[INDEX_PARAM_CONFIG_WIFI_LIST]               = ( char * )&g_sysConfig.wifiList;
}

static int CheckFlashConfigMd5( PARAM_CONFIG_STORE_HEAD storeHead, char *pBuf, int bufLen )
{
    int ret = FI_FAIL;
    char key[16];
    int configLen = sizeof( storeHead ) + storeHead.size;
    if( configLen + MD5_KEY_SIZE <= bufLen )
    {
        ret = Md5GenerateKey( ( unsigned char * )pBuf, ( unsigned int )configLen, ( unsigned char * )key );
        if( FI_SUCCESS == ret )
        {
            if( 0 != memcmp( pBuf + configLen, key, MD5_KEY_SIZE ) )
            {
                FiPrint( "check MD5 failed!\r\n" );
                PrintHex( "flash MD5 :", ( unsigned char * )( pBuf + configLen ), MD5_KEY_SIZE, "\r\n" );
                PrintHex( "gen MD5	:", ( unsigned char * )key, MD5_KEY_SIZE, "\r\n" );
                ret = FI_FAIL;
            }
        }
    }
    return ret;
}

static int GetSysConfigStruct( char *pBuf, int bufLen )
{
    uint    i;
    int ret = FI_FAIL;
    int offset, copySize;
    PARAM_CONFIG_STORE_HEAD storeHead = {0};
    memcpy( &storeHead, pBuf, sizeof( storeHead ) );
    if( 0 != memcmp( PARAM_CONFIG_MARK, storeHead.mark, strlen( PARAM_CONFIG_MARK ) ) ) // 没有这个可能导致CheckFlashConfigMd5()段错误
    {
        FiPrint( "error:Param Mark wrong!\r\n" );
        return FI_FAILED;
    }
    ret = CheckFlashConfigMd5( storeHead, pBuf, bufLen );
    if( FI_SUCCESS == ret && storeHead.totalMembers <= PARAM_CONFIG_MAX_MEMBERS )
    {
        offset = sizeof( storeHead );
        for( i = 0; i < storeHead.totalMembers; i++ )
        {
            if( offset + storeHead.memberSize[i] < bufLen )
            {
                copySize = g_storeHead.memberSize[i] < storeHead.memberSize[i] ? g_storeHead.memberSize[i] : storeHead.memberSize[i];
                memcpy( g_pMemberAddr[i], pBuf + offset, copySize );
                offset += storeHead.memberSize[i];
            }
        }
        ret = FI_SUCCESS;
    }
    return ret;
}

static int SysConfigFromFlash()
{
    int ret = -1;
    char *pBuf = NULL;
    int flagConfig = 0, flagConfigBack = 0;
    pBuf = ( char * )Malloc( MAX_PARAM_CONFIG_SIZE );
    if( NULL != pBuf )
    {
        // 从flash中读取128k到pBuf
        ret = ReadConfig( pBuf, MAX_PARAM_CONFIG_SIZE );
        if( FI_SUCCESS == ret )
        {
            // 校验配置的值，以及全局变量赋值
            ret = GetSysConfigStruct( pBuf, MAX_PARAM_CONFIG_SIZE );
            if( FI_SUCCESS != ret )
            {
                FiPrint( "Get sys config from normal partition failed!\r\n" );
                SyncParamConfigOnlyConfig();
            }
            else
            {
                flagConfig = 1;
            }
        }
        // 从flash偏移128k后中读取128k到pBuf
        ret = ReadConfigBackup( pBuf, MAX_PARAM_CONFIG_SIZE );
        if( FI_SUCCESS == ret )
        {
            ret = GetSysConfigStruct( pBuf, MAX_PARAM_CONFIG_SIZE );
            if( FI_SUCCESS != ret )
            {
                FiPrint( "Get sys config from config backup partition failed!\r\n" );
                // 备份都读不到就立刻写配置初始值
                 SyncParamConfigOnlyConfigBack();
            }
            else
            {
                flagConfigBack = 1;
            }
        }
        if( 1 == flagConfig )
        {
            FiPrint("use config normal!\r\n");
            ReadConfig( pBuf, MAX_PARAM_CONFIG_SIZE );
            GetSysConfigStruct( pBuf, MAX_PARAM_CONFIG_SIZE );
            FiPrint("3333333!\r\n");
            if( 1 != flagConfigBack )
            {
                SyncParamConfigOnlyConfigBack();
            }
            FiPrint("22222222!\r\n");
        }
        else if( 1 == flagConfigBack )
        {
            FiPrint( "use config backup!\r\n" );
            ReadConfigBackup( pBuf, MAX_PARAM_CONFIG_SIZE );
            GetSysConfigStruct( pBuf, MAX_PARAM_CONFIG_SIZE );
            if( 1 != flagConfig )
            {
                SyncParamConfigOnlyConfig();
            }
        }
    }
    Free( pBuf );
	
    return ret;
}


// 初始化系统配置
void InitParamConfig()
{
    // 指针数组地址分别指向对应全局变量g_sysConfig
    SysConfigInitMemberAddr();
    // 全局变量g_sysConfig初始化
    SysConfigRestoreFactoryConf();
    // 当没有flash调试的时候把这部分屏蔽掉
    int ret = SysConfigFromFlash();
    // 某些参数刚开机的时候总是需要恢复默认值
    SysConfigInitSendRtp( &g_sysConfig.sendRtp );
	//SysConfigInitWifiList( &g_sysConfig.wifiList );
	
	
    RtPrint( ret, "[02] %s [%s:%d]\n", __FUNCTION__, __FILE__, __LINE__ );
}


//告诉定时器,要保存配置到flash
int SaveParamConfig()
{
    return MessageSend( MSG_ID_TIMER_WRITE_SYS_CONFIG );
}

//马上把配置写进flash
int SyncParamConfig()
{
    int ret = -1;
    int configLen = sizeof( g_storeHead ) + sizeof( g_sysConfig ); // 512 + 27252 = 27268 = 26k
    int bufLen =  configLen + MD5_KEY_SIZE;
    char *pBuf = ( char * )Malloc( bufLen );
    if( NULL == pBuf )
        return ret;
    g_MutexConfig.Lock();
    memcpy( pBuf, &g_storeHead, sizeof( g_storeHead ) );
    memcpy( pBuf + sizeof( g_storeHead ), &g_sysConfig, sizeof( g_sysConfig ) );
    ret = Md5GenerateKey( ( unsigned char * )pBuf, ( unsigned int )configLen, ( unsigned char * )pBuf + configLen );
    if( FI_SUCCESS == ret )
        ret = WriteConfig( pBuf, bufLen );
#if 1
    if( FI_SUCCESS == ret )
        ret = WriteConfigBackup( pBuf, bufLen );
#endif
    g_MutexConfig.Unlock();
    Free( pBuf );
    return ret;
}
static int SyncParamConfigOnlyConfig()
{
    int ret = -1;
    int configLen = sizeof( g_storeHead ) + sizeof( g_sysConfig );
    int bufLen =  configLen + MD5_KEY_SIZE;
    char *pBuf = ( char * )Malloc( bufLen );
    if( NULL == pBuf ) return ret;
    g_MutexConfig.Lock();
    memcpy( pBuf, &g_storeHead, sizeof( g_storeHead ) );
    memcpy( pBuf + sizeof( g_storeHead ), &g_sysConfig, sizeof( g_sysConfig ) );
    ret = Md5GenerateKey( ( unsigned char * )pBuf, ( unsigned int )configLen,
                          ( unsigned char * )pBuf + configLen );
    if( FI_SUCCESS == ret ) ret = WriteConfig( pBuf, bufLen );
    g_MutexConfig.Unlock();
    Free( pBuf );
    return ret;
}

#if 1
//马上把配置写进flash
static int SyncParamConfigOnlyConfigBack()
{
    int ret = -1;
    int configLen = sizeof( g_storeHead ) + sizeof( g_sysConfig );
    int bufLen =  configLen + MD5_KEY_SIZE;
    char *pBuf = ( char * )Malloc( bufLen );
    if( NULL == pBuf ) return ret;
    g_MutexConfig.Lock();
    memcpy( pBuf, &g_storeHead, sizeof( g_storeHead ) );
    memcpy( pBuf + sizeof( g_storeHead ), &g_sysConfig, sizeof( g_sysConfig ) );
    ret = Md5GenerateKey( ( unsigned char * )pBuf, ( unsigned int )configLen,
                          ( unsigned char * )pBuf + configLen );
    if( FI_SUCCESS == ret ) ret = WriteConfigBackup( pBuf, bufLen );
    g_MutexConfig.Unlock();
    Free( pBuf );
    return ret;
}
#endif

static void *WriteSysConfig( void *args )
{
    if( MessageFind( MSG_ID_TIMER_WRITE_SYS_CONFIG ) )
    {
        while( MessageRecv( MSG_ID_TIMER_WRITE_SYS_CONFIG ) >= 0 )
        {
            ;
        }
        SyncParamConfig();
    }
    return NULL;
}

//写flash 定时器
void SysConfigAddTimer()
{
    unsigned int writeSysConfigTimerInterval    = 2000;
    AddRTimer( WriteSysConfig, NULL, writeSysConfigTimerInterval );
}

/*
* 获取系统配置
* index : 参见SYS_CONFIG里面的INDEX_ 宏
  pBuf  : buf,out
  len   : 获取的长度
  n     : 如果SYS_CONFIG的某个成员是个数组, n表示数组的第几个成员
*/
int GetParamConfig( int index, void *pBuf, int len, int n )
{
    int ret;
    char *pGetBuf;
    if( NULL == pBuf || len <= 0 || len > ( int )sizeof( g_sysConfig ) )
    {
        FiPrint( "NULL == pBuf || len <= 0 || len > sizeof(g_sysConfig)\r\n" );
        return FI_FAIL;
    }
    g_MutexConfig.Lock();
    ret = FI_SUCCESS;
    pGetBuf = NULL;
    switch( index )
    {
        case INDEX_PARAM_CONFIG_HEAD:
            pGetBuf = ( char * )&g_sysConfig.head;
            break;
        case INDEX_PARAM_CONFIG_BASE_INFO:
            pGetBuf = ( char * )&g_sysConfig.baseInfo;
            break;
        case INDEX_PARAM_CONFIG_NETWORK:
            pGetBuf = ( char * )&g_sysConfig.network;
            break;
        case INDEX_PARAM_CONFIG_CLIENT_USER:
            if( n >= 0 && n < MAX_CLIENT_USER_NUM )
                pGetBuf = ( char * )&g_sysConfig.user[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_ENCODE_PUBLIC:
            pGetBuf = ( char * )&g_sysConfig.videoEncodePublic;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_ENCODE:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.videoEncode[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_ENCODE_SLAVE:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.videoEncodeSlave[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_BASE_PARAM:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.videoBaseParam[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_OSD_LOGO:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.osdLogo[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_OSD_TIME:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.osdTime[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_AUDIO:
            pGetBuf = ( char * )&g_sysConfig.audioEncode;
            break;
        case INDEX_PARAM_CONFIG_AUTO_MAINTAIN:
            pGetBuf = ( char * )&g_sysConfig.autoMaintion;
            break;
        case INDEX_PARAM_CONFIG_RECORD_PUBLIC:
            pGetBuf = ( char * )&g_sysConfig.recordPublic;
            break;
        case INDEX_PARAM_CONFIG_RECORD_PARAM:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.recordParam[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_ALARM_IO:
            pGetBuf = ( char * )&g_sysConfig.alarmIo;
            break;
        case INDEX_PARAM_CONFIG_SERIAL:
            pGetBuf = ( char * )&g_sysConfig.serial;
            break;
        case INDEX_PARAM_CONFIG_NTP:
            pGetBuf = ( char * )&g_sysConfig.ntp;
            break;
        case INDEX_PARAM_CONFIG_EMAIL:
            pGetBuf = ( char * )&g_sysConfig.email;
            break;
        case INDEX_PARAM_CONFIG_ALARM_MOVE_DETECT:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.alarmMoveDetect[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_OVERLAY:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.videoOverlay[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_ALARM_VIDEO_LOSE:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.alarmVideoLose[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_FTP:
            pGetBuf = ( char * )&g_sysConfig.ftpParam;
            break;
        case INDEX_PARAM_CONFIG_SNAP_TIMER:
            pGetBuf = ( char * )&g_sysConfig.snapTimer[n];
            break;
        case INDEX_PARAM_CONFIG_ICMP:
            pGetBuf = ( char * )&g_sysConfig.icmp;
            break;
        case INDEX_PARAM_CONFIG_DDNS:
            pGetBuf = ( char * )&g_sysConfig.ddns;
            break;
        case INDEX_PARAM_CONFIG_DTU:
            pGetBuf = ( char * )&g_sysConfig.dtu;
            break;
        case INDEX_PARAM_CONFIG_WIFI_CONNECT:
            pGetBuf = ( char * )&g_sysConfig.wifiConnect;
            break;
        case INDEX_PARAM_CONFIG_THREEG:
            pGetBuf = ( char * )&g_sysConfig.threeg;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_SHELTER:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pGetBuf = ( char * )&g_sysConfig.videoShelter[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_TOTAL:
            pGetBuf = ( char * )&g_sysConfig.head;
            break;
        case INDEX_PARAM_CONFIG_DISK_INIT:
            pGetBuf = ( char * )&g_sysConfig.diskInit;
            break;
        case INDEX_PARAM_CONFIG_SEND_RTP:
            pGetBuf = ( char * )&g_sysConfig.sendRtp;
            break;

		case INDEX_PARAM_CONFIG_ERRORFILE_PATH:
			pGetBuf = ( char * )g_sysConfig.errorFilePath.errorFilePath;
			break;		
		case INDEX_PARAM_CONFIG_PTZ:
			pGetBuf = ( char * )&g_sysConfig.ptzInfo;				
			break;
        //case INDEX_PARAM_CONFIG_WIFI_LIST:
        //pGetBuf = ( char * )&g_sysConfig.wifiList;
        //break;
        default:
            FiPrint( "GetParamConfig failed:index(%d)!\r\n", index );
            ret = FI_FAIL;
            break;
    } // end switch
    if( NULL != pGetBuf && FI_SUCCESS == ret )
    {
        memcpy( pBuf, pGetBuf, len );
    }
    g_MutexConfig.Unlock();
    return ret;
}

/*
* 设置系统配置
* index : 参见SYS_CONFIG里面的INDEX_ 宏
  pBuf  : buf,out
  len   : 获取的长度
  n     : 如果SYS_CONFIG的某个成员是个数组, n表示数组的第几个成员
*/
int SetParamConfig( int index, void *pBuf, int len, int n )
{
    int ret;
    char *pSetAddr;
    if( NULL == pBuf || len <= 0 || len > ( int )sizeof( g_sysConfig ) )
    {
        FiPrint( "NULL == pBuf || len <= 0 || len > sizeof(g_sysConfig)\r\n" );
        return FI_FAIL;
    }
    g_MutexConfig.Lock();
    ret = FI_SUCCESS;
    pSetAddr = NULL;
    switch( index )
    {
        case INDEX_PARAM_CONFIG_HEAD:
            pSetAddr = ( char * )&g_sysConfig.head;
            break;
        case INDEX_PARAM_CONFIG_BASE_INFO:
            pSetAddr = ( char * )&g_sysConfig.baseInfo;
            break;
        case INDEX_PARAM_CONFIG_NETWORK:
            pSetAddr = ( char * )&g_sysConfig.network;
            break;
        case INDEX_PARAM_CONFIG_CLIENT_USER:
            if( n >= 0 && n < MAX_CLIENT_USER_NUM )
                pSetAddr = ( char * )&g_sysConfig.user[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_ENCODE_PUBLIC:
            pSetAddr = ( char * )&g_sysConfig.videoEncodePublic;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_ENCODE:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.videoEncode[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_ENCODE_SLAVE:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.videoEncodeSlave[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_BASE_PARAM:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.videoBaseParam[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_OSD_LOGO:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.osdLogo[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_OSD_TIME:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.osdTime[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_AUDIO:
            pSetAddr = ( char * )&g_sysConfig.audioEncode;
            break;
        case INDEX_PARAM_CONFIG_AUTO_MAINTAIN:
            pSetAddr = ( char * )&g_sysConfig.autoMaintion;
            break;
        case INDEX_PARAM_CONFIG_RECORD_PUBLIC:
            pSetAddr = ( char * )&g_sysConfig.recordPublic;
            break;
        case INDEX_PARAM_CONFIG_RECORD_PARAM:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.recordParam[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_ALARM_IO:
            pSetAddr = ( char * )&g_sysConfig.alarmIo;
            break;
        case INDEX_PARAM_CONFIG_SERIAL:
            pSetAddr = ( char * )&g_sysConfig.serial;
            break;
        case INDEX_PARAM_CONFIG_NTP:
            pSetAddr = ( char * )&g_sysConfig.ntp;
            break;
        case INDEX_PARAM_CONFIG_EMAIL:
            pSetAddr = ( char * )&g_sysConfig.email;
            break;
        case INDEX_PARAM_CONFIG_ALARM_MOVE_DETECT:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.alarmMoveDetect[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_OVERLAY:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.videoOverlay[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_ALARM_VIDEO_LOSE:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.alarmVideoLose[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_FTP:
            pSetAddr = ( char * )&g_sysConfig.ftpParam;
            break;
        case INDEX_PARAM_CONFIG_SNAP_TIMER:
            pSetAddr = ( char * )&g_sysConfig.snapTimer[n];
            break;
        case INDEX_PARAM_CONFIG_ICMP:
            pSetAddr = ( char * )&g_sysConfig.icmp;
            break;
        case INDEX_PARAM_CONFIG_DDNS:
            pSetAddr = ( char * )&g_sysConfig.ddns;
            break;
        case INDEX_PARAM_CONFIG_DTU:
            pSetAddr = ( char * )&g_sysConfig.dtu;
            break;
        case INDEX_PARAM_CONFIG_WIFI_CONNECT:
            pSetAddr = ( char * )&g_sysConfig.wifiConnect;
            break;
        case INDEX_PARAM_CONFIG_THREEG:
            pSetAddr = ( char * )&g_sysConfig.threeg;
            break;
        case INDEX_PARAM_CONFIG_VIDEO_SHELTER:
            if( n >= 0 && n < MAX_CHANNEL_NUM )
                pSetAddr = ( char * )&g_sysConfig.videoShelter[n];
            else    ret = FI_FAIL;
            break;
        case INDEX_PARAM_CONFIG_TOTAL:
            pSetAddr = ( char * )&g_sysConfig.head;
            break;
        case INDEX_PARAM_CONFIG_DISK_INIT:
            pSetAddr = ( char * )&g_sysConfig.diskInit;
            break;
        case INDEX_PARAM_CONFIG_SEND_RTP:
            pSetAddr = ( char * )&g_sysConfig.sendRtp;
            break;
        case INDEX_PARAM_CONFIG_ERRORFILE_PATH:
            pSetAddr = ( char * )g_sysConfig.errorFilePath.errorFilePath;
            break;		
		case INDEX_PARAM_CONFIG_PTZ:
            pSetAddr = ( char * )&g_sysConfig.ptzInfo;
            break;	
        //case INDEX_PARAM_CONFIG_WIFI_LIST:
        //pSetAddr = ( char * )&g_sysConfig.wifiList;
        //break;
        default:
            FiPrint( "GetParamConfig failed:index(%d)!\r\n", index );
            ret = FI_FAIL;
            break;
    } // end switch
    if( NULL != pSetAddr && FI_SUCCESS == ret )
    {
        memcpy( pSetAddr, pBuf, len );
        ParamChangedReport();
    }
    g_MutexConfig.Unlock();
    return ret;
}

void ParamChangedReport( void )
{
    //MSG_CMD_T msgCmd;
    //发送到客户端
    //msgCmd.cmd = DIL_PARAM_CHANGED_REPORT;
    //MessageSend( MSG_ID_DCP_SIGNAL, (char *)&msgCmd, sizeof(msgCmd) );
}


int InitThttpdConfig()
{
    unsigned short port = 0;
    //g_MutexConfig.Lock();
    port = g_sysConfig.network.port.webPort;
    //FiPrint("Port---------------------------------------%d\r\n", port);
    //g_MutexConfig.Unlock();
    FILE *fp = fopen( "/tmp/thttpd.conf", "wb+" );
    if( fp == NULL )
    {
        int errNo = errno;
        FiPrint( "Open thttpd config file error: %s !\r\n", strerror( errNo ) );
        return -1;
    }
    fprintf( fp, "port=%d\r\n", port ); // 向配置文件中写入网页端口号
    fflush( fp );
    fclose( fp );
    return 0;
}




