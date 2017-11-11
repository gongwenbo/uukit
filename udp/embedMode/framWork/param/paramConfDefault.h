#ifndef __SYSCONFDEFAULT_H__
#define __SYSCONFDEFAULT_H__

#include "const.h"
#define DEV_VERSION          "v2.0.6.00"  


#define PARAM_CONFIG_SIGNATURE  "LqJcon1"   				//lqj config 1 ,该宏固定不变
#define MAX_CLIENT_USER_NUM     5       					//最多支持创建5个用户
#define MAX_CHANNEL_NUM         16      					//最多支持16个通道
#if defined MCU_HI3515
#elif defined MCU_HI3518
#define DEV_MODEL               "BHIPC_HI3518ev100"         //产品型号 
#define DEV_SERIAL_NUM          "HHIPC-720P"        		//产品序列号
#define DEV_HARDWARE_VERSION    DEV_VERSION             	//硬件版本  
#define DEV_SOFTWARE_VERSION    DEV_VERSION            		//软件版本
#define DEV_CONFIG_VERSION      DEV_VERSION            		//配置版本
#define DEV_CHIP_NUM                    1
#define DEV_VIDEO_IN_NUM                1
#define DEV_VIDEO_OUT_NUM               1
#define DEV_ALARM_IN_NUM                1
#define DEV_ALARM_OUT_NUM               1
#define MAX_OVERLAY_NUM_ECHE_CHANNEL    4   
#elif defined MCU_HI3518ev200
#define DEV_MODEL               "BHIPC_HI3518ev200"   

#if defined SENSOR_H42_MIPI_720P_30FPS || defined SENSOR_H62_MIPI_720P_30FPS
#define DEV_SERIAL_NUM          "HHIPC-720P"        
#define DEV_HARDWARE_VERSION    DEV_VERSION             
#define DEV_SOFTWARE_VERSION    DEV_VERSION            
#define DEV_CONFIG_VERSION      DEV_VERSION             

#elif defined SENSOR_F22_MIPI_1080P_30FPS

// 防水机F22
#if defined WATERPROOF_SENSOR_F22_MIPI_1080P_30FPS
#define DEV_SERIAL_NUM          "HHIPC-1080P"        
#define DEV_HARDWARE_VERSION    DEV_VERSION             
#define DEV_SOFTWARE_VERSION    DEV_VERSION             
#define DEV_CONFIG_VERSION      DEV_VERSION             
#else // #if defined WATERPROOF_SENSOR_F22_MIPI_

// 芒果机F22
#define DEV_SERIAL_NUM          "HHIPC-1080P"        
#define DEV_HARDWARE_VERSION    DEV_VERSION            
#define DEV_SOFTWARE_VERSION    DEV_VERSION            
#define DEV_CONFIG_VERSION      DEV_VERSION             
#endif // #if defined WATERPROOF_SENSOR_F22_MIPI_
#endif // #elif defined SENSOR_F22_MIPI_1080P_3
#define DEV_CHIP_NUM                    2
#define DEV_VIDEO_IN_NUM                1
#define DEV_VIDEO_OUT_NUM               2
#define DEV_ALARM_IN_NUM                1
#define DEV_ALARM_OUT_NUM               1
#define MAX_OVERLAY_NUM_ECHE_CHANNEL    4   

#elif defined MCU_T10
#define DEV_MODEL               "BHIPC_T10"         
#define DEV_SERIAL_NUM          "HHIPC-720P"        
#define DEV_HARDWARE_VERSION    DEV_VERSION           
#define DEV_SOFTWARE_VERSION    DEV_VERSION            
#define DEV_CONFIG_VERSION      DEV_VERSION            
#define DEV_CHIP_NUM                    2
#define DEV_VIDEO_IN_NUM                1
#define DEV_VIDEO_OUT_NUM               2
#define DEV_ALARM_IN_NUM                1
#define DEV_ALARM_OUT_NUM               1
#define MAX_OVERLAY_NUM_ECHE_CHANNEL    4  

#elif defined MCU_AK3918E
#define DEV_MODEL               "HWIPC_AK3918E"         
#define DEV_SERIAL_NUM          "HHIPC-720P"        
#define DEV_HARDWARE_VERSION    "v2.0.6.02"              
#define DEV_SOFTWARE_VERSION    "v2.0.6.02"            
#define DEV_CONFIG_VERSION      "v2.0.6.02"           
#define DEV_CHIP_NUM                    2
#define DEV_VIDEO_IN_NUM                1
#define DEV_VIDEO_OUT_NUM               2
#define DEV_ALARM_IN_NUM                1
#define DEV_ALARM_OUT_NUM               1
#define MAX_OVERLAY_NUM_ECHE_CHANNEL    4   

#else // 板级无关
#define DEV_MODEL               "DEV_NORMAL"     // 通用产品型号 
#define DEV_SERIAL_NUM          "DEV-007"        // 产品序列号
#define DEV_HARDWARE_VERSION    "v1.0.0.00"             //硬件版本  
#define DEV_SOFTWARE_VERSION    "v1.0.0.00"             //软件版本
#define DEV_CONFIG_VERSION      "v1.0.0.00"            //配置版本
#define DEV_CHIP_NUM                    2
#define DEV_VIDEO_IN_NUM                1
#define DEV_VIDEO_OUT_NUM               0
#define DEV_ALARM_IN_NUM                0
#define DEV_ALARM_OUT_NUM               0
#define MAX_OVERLAY_NUM_ECHE_CHANNEL    0   // 每个通道最多支持4个遮挡区域

#endif
#define PARAM_CONFIG_DEFAULT_MAC    "00:00:00:00:00:08"
#define DEV_DEFAULT_IP              "192.168.1.22"
#define DEV_DEFAULT_NETMASK         "255.255.255.0"
#define DEV_DEFAULT_GATEWAY         "192.168.1.1"
#define DEV_DEFAULT_DNS1            "202.96.134.133"
#define DEV_DEFAULT_DNS2            "202.96.128.68"
#define DEV_DEFAULT_BROADADDR       "255.255.255.255"
#define DEV_DEFAULT_WEBPORT         80
#define DEV_DEFAULT_MSG_PORT        20000
#define DEV_DEFAULT_STREAM_PORT     ( DEV_DEFAULT_MSG_PORT + 1 )
#define DEV_DEFAULT_SEARCH_PORT     ( DEV_DEFAULT_MSG_PORT + 2 )


#define DEV_DEFAULT_USER_NAME   "admin"
#define DEV_DEFAULT_USER_PWD    "admin"
#define USER_PERMISSION_VIDEO           (0x01 << 0)     // 浏览视频权限
#define USER_PERMISSION_RECORD          (0x01 << 1)     // 录像操作权限
#define USER_PERMISSION_PARAM_SET       (0x01 << 2)     // 参数设置权限
#define USER_PERMISSION_LOG             (0x01 << 3)     // 日志查看权限
#define USER_PERMISSION_PTZ             (0x01 << 4)     // 云台控制权限

#define USER_PERMISSION_ALL (   USER_PERMISSION_VIDEO       | \
                                USER_PERMISSION_RECORD      | \
                                USER_PERMISSION_PARAM_SET   | \
                                USER_PERMISSION_LOG         | \
                                USER_PERMISSION_PTZ )
typedef enum _UserLevel_
{
    USER_LEVEL_NONE = 0,
    USER_LEVEL_ADMIN,
    USER_LEVEL_BROWSE
} USER_LEVEL;

#define DEV_DEFAULT_USER_PERMISSION USER_PERMISSION_ALL
#define DEV_DEFAULT_USER_LEVEL      USER_LEVEL_ADMIN

#define DEV_DEFAULT_VIDEO_BRIGHTNESS    128
#define DEV_DEFAULT_VIDEO_CONTRAST      138
#define DEV_DEFAULT_VIDEO_SATURATION    135
#define DEV_DEFAULT_VIDEO_EXPOSURE      128
#define DEV_DEFAULT_VIDEO_HUE           8

typedef enum _VideoEncodeStandard_
{
    VIDEO_ENCODE_STANDARD_PAL = 0,
    VIDEO_ENCODE_STANDARD_NTSC,
    VIDEO_ENCODE_STANDARD_AUTO
} VIDEO_ENCODE_STANDARD;

typedef enum _VideoEncodeResolution_
{
    VIDEO_ENCODE_RESOLUTION_QCIF = 0,
    VIDEO_ENCODE_RESOLUTION_CIF,
    VIDEO_ENCODE_RESOLUTION_2CIF,
    VIDEO_ENCODE_RESOLUTION_HD1,
    VIDEO_ENCODE_RESOLUTION_D1,
    VIDEO_ENCODE_RESOLUTION_960H,

    VIDEO_ENCODE_RESOLUTION_QVGA,    /* 320 * 240 */
    VIDEO_ENCODE_RESOLUTION_VGA,     /* 640 * 480 */
    VIDEO_ENCODE_RESOLUTION_XGA,     /* 1024 * 768 */
    VIDEO_ENCODE_RESOLUTION_SXGA,    /* 1400 * 1050 */
    VIDEO_ENCODE_RESOLUTION_UXGA,    /* 1600 * 1200 */
    VIDEO_ENCODE_RESOLUTION_QXGA,    /* 2048 * 1536 */

    VIDEO_ENCODE_RESOLUTION_WVGA,    /* 854 * 480 */
    VIDEO_ENCODE_RESOLUTION_WSXGA,   /* 1680 * 1050 */
    VIDEO_ENCODE_RESOLUTION_WUXGA,   /* 1920 * 1200 */
    VIDEO_ENCODE_RESOLUTION_WQXGA,   /* 2560 * 1600 */

    VIDEO_ENCODE_RESOLUTION_HD720 = 16,   /* 1280 * 720 */
    VIDEO_ENCODE_RESOLUTION_HD1080,  /* 1920 * 1080 */
    VIDEO_ENCODE_RESOLUTION_HD960 = 100,    // 1280 x 960
} VIDEO_ENCODE_RESOLUTION;

typedef enum _VideoEncodeBitrateType_
{
    VIDEO_ENCODE_BITRATE_TYPE_CBR = 0,  // 固定位率
    VIDEO_ENCODE_BITRATE_TYPE_VBR,      // 可变位率
} VIDEO_ENCODE_BITRATE_TYPE;

typedef enum _VideoEncodeStreamType_
{
    VIDEO_ENCODE_TYPE_AV = 0,   //音视频
    VIDEO_ENCODE_TYPE_V,        //视频
    VIDEO_ENCODE_TYPE_A,        //音频
} VIDEO_ENCODE_STREAM_TYPE;

#define DEV_DEFAULT_VIDEO_ENCODE_STANDARD           VIDEO_ENCODE_STANDARD_PAL

#if defined MCU_HI3515
#define DEV_DEFAULT_VIDEO_ENCODE_RESOLUTION         VIDEO_ENCODE_RESOLUTION_D1
#elif defined MCU_HI3518
#define DEV_DEFAULT_VIDEO_ENCODE_RESOLUTION         VIDEO_ENCODE_RESOLUTION_HD720
#elif defined MCU_HI3518ev200
#define DEV_DEFAULT_VIDEO_ENCODE_RESOLUTION         VIDEO_ENCODE_RESOLUTION_HD720

#endif
#define DEV_DEFAULT_VIDEO_ENCODE_BITRATETYPE        VIDEO_ENCODE_BITRATE_TYPE_CBR
#define DEV_DEFAULT_VIDEO_ENCODE_FRAMERATE          15//25
#define DEV_DEFAULT_VIDEO_ENCODE_IFRAMEINTERVAL     15//50
#define DEV_DEFAULT_VIDEO_ENCODE_PREFERFRAME        FI_FALSE
#define DEV_DEFAULT_VIDEO_ENCODE_TYPE               VIDEO_ENCODE_TYPE_AV
#define DEV_DEFAULT_VIDEO_ENCODE_BITRATE            512//2048

/******音频参数******/
typedef enum _FiAudioBitWidth_
{
    FI_AUDIO_BIT_WIDTH_8   = 0,   /* 8bit width */
    FI_AUDIO_BIT_WIDTH_16  = 1,   /* 16bit width*/
    FI_AUDIO_BIT_WIDTH_32  = 2,   /* 32bit width*/
    FI_AUDIO_BIT_WIDTH_BUTT,
} FI_AUDIO_BIT_WIDTH_E;


/******音频采样率******/
typedef enum _FiAudioSampleRate_
{
    FI_AUDIO_SAMPLE_R8     = 0,   /* 8K Sample rate     */
    FI_AUDIO_SAMPLE_R16    = 1,   /* 16K Sample rate    */
} FI_AUDIO_SAMPLE_RATE_E;

/******音频编码格式******/
typedef enum FiAudioCodecFormat_
{
    FI_AUDIO_FORMAT_ADPCM   = 0,    /* ADPCM     */
    FI_AUDIO_FORMAT_G711A,          /* G.711A    */
    FI_AUDIO_FORMAT_G726,           /* G.7126    */
    FI_AUDIO_FORMAT_G711U,          /* G.711U    */
} FI_AUDIO_CODEC_FORMAT_E;

/******音频通道模式******/
typedef enum _FiAudioChannelMode_
{
    FI_AUDIO_CHANNEL_MODE_MOMO = 0,
    FI_AUDIO_CHANNEL_MODE_STEREO,
} FI_AUDIO_CHANNEL_MODE_E;

/******AMR包类型******/
typedef enum stAMR_PACKAGE_TYPE_E
{
    FI_AMR_PACKAGE_MIME = 0,  /* Using for file saving        */
    FI_AMR_PACKAGE_IF_1 = 1,  /* Using for wireless translate */
    FI_AMR_PACKAGE_IF_2 = 2,  /* Using for wireless translate */
} AMR_PACKAGE_TYPE;

/******AMR比特率类型******/
typedef enum stAUDIO_AMR_MODE_E
{
    FI_AMR_MODE_R475 = 0,     /* AMR bit rate as  4.75k */
    FI_AMR_MODE_R515,         /* AMR bit rate as  5.15k */
    FI_AMR_MODE_R59,          /* AMR bit rate as  5.90k */
    FI_AMR_MODE_R67,          /* AMR bit rate as  6.70k */
    FI_AMR_MODE_R74,          /* AMR bit rate as  7.40k */
    FI_AMR_MODE_R795,         /* AMR bit rate as  7.95k */
    FI_AMR_MODE_R102,         /* AMR bit rate as 10.20k */
    FI_AMR_MODE_R122,         /* AMR bit rate as 12.20k */
} AUDIO_AMR_MODE;

#define DEV_DEFAULT_AUDIO_ENCODE_SAMPLE_RATE    FI_AUDIO_SAMPLE_R8
#define DEV_DEFAULT_AUDIO_ENCODE_SAMPLE_WIDTH   FI_AUDIO_BIT_WIDTH_16
#define DEV_DEFAULT_AUDIO_ENCODE_TYPE           FI_AUDIO_FORMAT_G711A
#define DEV_DEFAULT_AUDIO_ENCODE_CHANNEL_MODE   FI_AUDIO_CHANNEL_MODE_MOMO
#define DEV_DEFAULT_AUDIO_ENCODE_AMR_MODE       FI_AMR_PACKAGE_MIME
#define DEV_DEFAULT_AUDIO_ENCODE_AMR_FORMAT     FI_AMR_MODE_R475

#define DEV_DEFAULT_AUDIO_ENCODE_MUTE   1
#define DEV_DEFAULT_AUDIO_ENCODE_UNMUTE 0


#define DEV_DEFAULT_RECORD_PUBLIC_DEL_SPACE     (50)   //剩余50M开始删盘  
#define DEV_DEFAULT_RECORD_PUBLIC_DEL_SIZE      (300)       //删除300M
#define DEV_DEFAULT_RECORD_PUBLIC_SWITCH_FILE_TIME      1      //1分钟切换一个文件
#define DEV_DEFAULT_RECORD_PUBLIC_HANDRECORD_FLAG       1      //1:打开，0:关闭
#define DEV_DEFAULT_RECORD_PUBLIC_AUDIO_FLAG            1      // 录音频标志,0:不录,1:录. 

typedef enum _Baudrate_
{
    BAUDRATE_110 = 0,
    BAUDRATE_300,
    BAUDRATE_600,
    BAUDRATE_1200,
    BAUDRATE_2400,
    BAUDRATE_4800,
    BAUDRATE_9600,
    BAUDRATE_19200,
    BAUDRATE_38400,
    BAUDRATE_57600,
    BAUDRATE_115200
} BAUDRATE_EN;

typedef enum _Databits_
{
    DATABITS_5 = 0,
    DATABITS_6,
    DATABITS_7,
    DATABITS_8
} DATABITS_EN;

typedef enum _Stopbits_
{
    STOPBITS_1 = 0,
    STOPBITS_2
} ENOPBITS_EN;

typedef enum _Parity_
{
    PARITY_NONE = 0,
    PARITY_ODD,
    PARITY_EVEN
} PARITY_EN;

typedef enum _OsdFontSize_
{
    FONT_SIZE_H16 = 0,
    FONT_SIZE_H32,
} OSDFONTSIZE_EN;


#define DEV_DEFAULT_SERIAL_BAUDRATE     BAUDRATE_9600
#define DEV_DEFAULT_SERIAL_DATABITS     DATABITS_8
#define DEV_DEFAULT_SERIAL_STOPBITS     STOPBITS_1
#define DEV_DEFAULT_SERIAL_PARITY       PARITY_NONE

// for ntp
#define PARAM_CONFIG_DEFAULT_NTP_ENABLE_FLAG    1   // 使能
#define PARAM_CONFIG_DEFAULT_NTP_INTERVAL       120     // 120 秒尝试一次
#define PARAM_CONFIG_DEFAULT_NTP_ZONE           8   // 时区
#define PARAM_CONFIG_DEFAULT_NTP_ADDR           "192.168.1.125"

// for move detect
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_SENSITIVITY        1
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_INTERVAL           1
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_LINKALARMOUT       0x1F // 5个报警输出
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_ALARMOUTDURATION   3
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_LINKCAPTURE        0x1F // 5个抓拍通道
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_CAPTURENUM         1
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_LINKRECORD         0x0F
#define PARAM_CONFIG_DEFAULT_MOVE_DETECT_RECORDDURATION     20

// for ftp
#define PARAM_CONFIG_DEFAULT_FTP_ENABLE     1
#define PARAM_CONFIG_DEFAULT_FTP_PORT       21
#define PARAM_CONFIG_DEFAULT_FTP_IP         "192.168.16.195"
#define PARAM_CONFIG_DEFAULT_FTP_USER       "oscar"
#define PARAM_CONFIG_DEFAULT_FTP_PASSWD     "123456789"
#define PARAM_CONFIG_DEFAULT_FTP_UP         1

// for icmp
#define PARAM_CONFIG_DEFAULT_ICMP_IPADDR    "58.63.236.49" // www.sina.com
#define PARAM_CONFIG_DEFAULT_ICMP_INTERVAL  32
#define PARAM_CONFIG_DEFAULT_ICMP_TIMEOUT   10
#define PARAM_CONFIG_DEFAULT_ICMP_FCOUNT    5
#define PARAM_CONFIG_DEFAULT_ICMP_FINTERVAL 32

// for ddns
typedef enum _DdnsVender_
{
    DDNS_VENDER_QDNS = 0,       // members.3322.org 希网,中国
    DDNS_VENDER_DYNDNS,         // www.dyns.cx 英国
    DDNS_VENDER_ORAY,           // 花生壳
} DDNS_VENDER_EN;

#define PARAM_CONFIG_DEFAULT_DNS_VENDER     DDNS_VENDER_ORAY // DDNS_VENDER_QDNS// 
#define PARAM_CONFIG_DEFAULT_DNS_PORT       6060
#define PARAM_CONFIG_DEFAULT_DNS_INTERVAL   120
#define PARAM_CONFIG_DEFAULT_DNS_USERNAME   "qiaoliang328"
#define PARAM_CONFIG_DEFAULT_DNS_PASSWD     "oscar328"
#define PARAM_CONFIG_DEFAULT_DNS_URL        "qiaoliang328.3322.org" //"qiaoliang328.gicp.net"
#define PARAM_CONFIG_DEFAULT_DNS_IFNAME     "ppp0"

// for dtu
#define PARAM_CONFIG_DEFAULT_DTU_SERVERIP   "192.168.16.218"
#define PARAM_CONFIG_DEFAULT_DTU_SERVERPORT 22222
#define PARAM_CONFIG_DEFAULT_DTU_HEARTBEAT  10
#define PARAM_CONFIG_DEFAULT_DTU_PROTOCOL   0   // 0,tcp; 1, udp
#define PARAM_CONFIG_DEFAULT_DTU_CONTENT    "app"

// for video shelter
typedef enum _VideoShelterSensitivity_
{
    VIDEO_SHELTER_SENSITIVITY_0 = 0,   // 灵敏度低，需要完全遮挡才会感应
    VIDEO_SHELTER_SENSITIVITY_1,
    VIDEO_SHELTER_SENSITIVITY_2,
    VIDEO_SHELTER_SENSITIVITY_3,
    VIDEO_SHELTER_SENSITIVITY_4,       //灵敏度最高，背景差别不大就会认为被遮挡
} VIDEO_SHELTER_SENSITIVITY_EN;

#endif //__SYSCONFDEFAULT_H__

