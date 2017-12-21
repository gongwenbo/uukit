/*
*******************************************************************************
**  Copyright (c) 2012, 深圳市有限公司, All rights reserved.
**  作者：梁桥江
**  当前版本：v1.0
**  创建日期: 2015.10.26
**  文件说明: nvr 客户端sdk 类型
*******************************************************************************
*/

#ifndef __HWSDKTYPE_H__ 
#define __HWSDKTYPE_H__

#ifdef WIN32
// #include <windows.h>
#pragma pack(push)
#pragma pack(1)
#define PACK_ALIGN
#else
#define PACK_ALIGN	__attribute__((packed))
#endif

#define HWSDKC_VERSION    "v3.04"

#define NORMAL_FILENAME_LEN		80	// 包含绝对路径的文件名字, 常用的不超过80 个字节
#define DATETIME_LEN			20		// "2012-11-18 10:20:28" 的长度

//
// 存储空间相关
#define MAX_DISK_NUM 12
#define MAX_PART_NUM 4

#define HWSDK_RECORD_VERSION        0xAB01      // 录像包过滤版本控制相关
#define HWSDK_RECORD_SEARCH_VERSION 0xAB01      // 录像搜索版本号

// sdk 本地全局错误类型;
typedef enum 
{
    CERROR_TYPE_GET_PARAM_FAILED        = 29,   // 获取参数失败 
    CERROR_TYPE_SET_PARAM_FAILED        = 30,   // 设置参数失败

	CERROR_TYPE_CONNECT 		        = 511, 	// 连接失败(网络故障)
	CERROR_TYPE_SEND 			        = 512, 	// 发送失败(网络故障)	
	CERROR_TYPE_RECV 			        = 513, 	// 接收失败(网络故障)
	CERROR_TYPE_GET_MNG_HOST	        = 514,	// 获取管理服务器失败(网络故障)	
	CERROR_TYPE_TIMEOUT 		        = 515, 	// 超时(等待服务器返回出错)
	
	CERROR_TYPE_ISNOT_LOGIN 	        = 516, 	// 用户没登陆(操作流程出错)
	CERROR_TYPE_NOT_PERMISSION 	        = 517,	// 权限不够(操作流程出错) 	
    CERROR_TYPE_STREAM_NOT_OPEN         = 518,  // 请求音频时，视频流还没有打开(操作流程出错)
    CERROR_TYPE_PARSE_XML_RES	        = 519,	// 解析服务器返回的结果出错(数据格式出错)
	CERROR_TYPE_BUFFER_SIZE		        = 520,	// 缓冲不足(缓冲区不够空间存放图片或文件)
	
	CERROR_TYPE_PARAM			        = 521,	// 参数错误
    CERROR_TYPE_REPLAY_TOO_MANY_USER    = 522,	// 回放录像的用户太多了
	CERROR_TYPE_REPLAY_LAST_FILE        = 523,	// 播放完最后一个录像

    CERROR_TYPE_CB_NO_THIS_DEV          = 601,  // 上下线回调,设备列表没有相对应设备id。
    CERROR_TYPE_CB_NOT_OPEN_STREAM      = 602,  // 实视流回调,没有打开实时流
    CERROR_TYPE_CB_NOT_IN_REPLAY        = 603,  // 录像回放回调,回放没有打开,或者已停止
    CERROR_TYPE_BUTT			        = 10000 // 非服务器错误号取值范围[511,10000) 
} HW_CERROR_TYPE_EN;

typedef enum 
{
	CE_CLIENT_INDEX 		= 1,	    // 服务器返回客户端的index, APP 需要保存;
	CE_WIFI_CONNECT_PROGESS = 2, 	    // 链接wifi的进度;
	CE_WIFI_IP				= 3, 	    // 某个设备连接上wifi 的IP 地址;
	CE_DEV_ONLINE			= 4,	    // 设备上线;
	CE_DEV_OFFLINE			= 5,	    // 设备下线;
	
	CE_DEV_SVR				= 6,	    // 设备的IP 地址或者它所连的P2P 服务器的IP 地址或者转发服务器地址格式有误;
    CE_PLAYBACK_RES         = 7,        // 回放控制错误时返回错误码;
    CE_CHANNEL_STATE_LOW    = 8,        // NVR 0-31通道状态;
    CE_CHANNEL_STATE_HIGH   = 9,        // NVR 32-63通道状态;
	CE_MNG_IP				= 10,	    // 管理服务器的IP 地址和端口, APP 需要保存;
    CE_CHANNEL_SWITCH       = 11,       // 实时流数据通道状态,包括P2P和转发;
    CE_DEV_SLEEP            = 12,       // 设备休眠;
    CE_DEV_ELECTRICITY      = 13,       // 门铃设备电量;
	CE__BUTT
} COM_EVENT_EN;

typedef enum 
{
	CD_UNVARNISHED_TRANSMISSION 		= 1,	    // 透传设备传输过来的数据;
	CD_DEBUG_DATA,			// 调试数据, 字符串类型, 当APP 屏幕打印开关(视频走P2P还是转发)打开时, 把该指令回调的信息打印到屏幕上(类似于视频走P2P还是转发);
	CD__BUTT
} COM_DATA_EN;


typedef enum 
{
	PIC_TYPE_REALTIME 	= 1,	// 实时图片, 用于获取一张图片;
	PIC_TYPE_ALARM 		= 2,	// 报警图片;
	PIC_TYPE_PRESET		= 3,	// 预置位, 该类型只有在回调时会用到;
} PIC_TYPE_EN;

typedef enum _PlaybackControlQt_
{
	RC_STOP 	    = 0,		// 停止
	RC_PLAY		    = 1, 		// 播放	
	RC_PAUSE	    = 2, 		// 暂停
	RC_FILE		    = 3,		// 拖动
	RC_SPEED	    = 4,		// 按某个速度播放 
    RC_CONTINUNE    = 5,		// 继续播放，对应 RC_PAUSE 
    RC_SWITCH_CHN   = 6,        // 切换码流
	RC_UNKNOW       = 100,	    // 未知状态,例如从RC_STOP 进入 RC_PLAY, 但播放列表为0, 这进入未知状态
} REPLAY_CMD_EN;

typedef enum _PlaybackSpeedQt_
{
	PSQ_2   = 0,	    // 快进 2倍速度
	PSQ_4   = 1, 		// 快进 4倍速度
	PSQ_8   = 2, 		// 快进 8倍速度
	PSQ_16  = 3,		// 快进 16倍速度
	PSQ_1_2 = 4,	    // 快进 1/2 倍速度
	
	PSQ_1_4 = 5,	// 快进 1/4 倍速度
	PSQ_1_8 = 6,	// 快进 1/8 倍速度
	PSQ_1_16 = 7,	// 快进 1/16 倍速度
/* 暂时不支持快退
	PSQ_FB_2,	// 快退 2倍速度
	PSQ_FB_4, 	// 快退 4倍速度
	
	PSQ_FB_8, 	// 快退 8倍速度
	PSQ_FB_16,	// 快退 16倍速度
	PSQ_FB_1_2,	// 快退 1/2 倍速度
	PSQ_FB_1_4,	// 快退 1/4 倍速度
	PSQ_FB_1_8,	// 快退 1/8 倍速度
	
	PSQ_FB_1_16,// 快退 1/16 倍速度
*/
} PLAYBACK_SPEED_QT_EN;

//
// 编码类型
typedef enum 
{
	ET_H264 	= 0,
	ET_H265 	= 1,
	ET_MPEG4	= 2,
	ET_JPEG		= 3, 	// jpg 图片
	ET_G711A	= 100,	// 音频数据为 >= 100; 视频类型 <100
	ET_G711U	= 101,
	ET_AAC		= 102,
} HW_ENC_TYPE;

// 
// 消息推送时间段(Push Notification time quantum)
typedef enum 
{
	PNTQ_ALL 	= 0,	// 全天推送
	PNTQ_DAY 	= 1,	// 白天推送
	PNTQ_NIGHT 	= 2,	// 晚上推送
	PNTQ_OFF 	= 3,	// 不推送
} HW_PNTQ_EN;

// 
// 定义用户的操作;
typedef enum
{
	AA_ENTER 	= 1, // 废弃, 进入某个界面;
	AA_UP		= 2, // 向上拉;
	AA_DOWN		= 3, // 向下拉;		
	AA_TIME		= 4, // 按时间段来查询;	
} APP_ACTION_EN;

// 
// 定义客户端类型;
typedef enum
{
	CLI_ANDROID_PHONE	= 1, // android 手机;
	CLI_ISO_PHONE		= 2, // 苹果手机;
	CLI_WIN_PC			= 3, // win电脑;	
} CLI_TYPE_EN;

// 
// 定义客户端类型;
// VRL_[1,4]  对应15帧/s, 码率: 2048kbps、1536kbps、1024kbps、768kbps;
// VRL_[5,7]  对应12帧/s, 码率: 512kbps、384kbps、256kbps;
// VRL_[8,10] 对应 8帧/s, 码率: 200kbps, 168kbps、128kbps;
typedef enum
{
	VRL_UNKONW	= 0,	// 未知
	VRL_1		= 1, 			
	VRL_2		= 2, 	
	VRL_3		= 3, 
	VRL_4		= 4, 	
	VRL_5		= 5, 	
	VRL_6		= 6, 
	VRL_7		= 7, 	
	VRL_8		= 8, 	
	VRL_9		= 9, 	
	VRL_10		= 10, 
} HW_VRL_EN; // video rate level

// 通道类型
typedef enum 
{
	CHN_TYPE_CAMERA  = 0, // 摄像机类型通道, 对应设备列表WEBS_DEV_INFO_T 里面的 "CAMERA_ATTR_T *cameraAttr[64]" 相机;
	CHN_TYPE_KSENSOR = 1, // 开关量类型通道, 在设备列表中未定义;
	CHN_TYPE_DSENSOR = 2, // 数字开关量类型通道, 在设备列表中未定义;
	CHN_TYPE_SYSTEM  = 3, // 系统通道, 每个设备都有一个唯一的设备通道, 而且永远存在;

	CHN_TYPE_BUTT
} HW_CHN_TYPE_EN;

//
// 报警输入类型
typedef enum 
{
	HW_ALM_INPUT_VIDEO 		= 1, // 视频报警(移动侦测、视频分析、视频丢失等所有由视频通道产生的报警);
	HW_ALM_INPUT_KSENSOR 	= 2, // 开关量探头报警(常开转为常闭，或者常闭转为常开);
	HW_ALM_INPUT_DSENSOR	= 3, // 数字传感器报警(比如通过RS433, wifi 链接的子设备);
	HW_ALM_INPUT_SYSTEM		= 4, // 系统故障报警(比如硬盘等)
} HW_ALM_INPUT_TYPE_EN;

//
// 视频报警(HW_ALM_INPUT_VIDEO)子类型
typedef enum 
{
	HW_ALM_VIDEO_MOTION_DETECT 		= 101, // 移动侦测;
	HW_ALM_VIDEO_LOSS 				= 102, // 视频丢失, 非设备失联;
	HW_ALM_VIDEO_COVER				= 103, // 视频遮挡;
	HW_ALM_INPUT_BEHAVIOR			= 104, // 视频分析报警, 根据实际情况增加具体的行为定义;	
	HW_ALM_SWIPING_CARD				= 105, // 刷卡联动视频动作;
} HW_ALM_VIDEO_TYPE_EN;

//
// 开关量探头报警(HW_ALM_INPUT_KSENSOR)子类型
typedef enum 
{
	HW_ALM_KSENSOR_KSWITCH_ON 		= 201, // 开关打开;
	HW_ALM_KSENSOR_KSWITCH_OFF		= 202, // 开关关闭;
	HW_ALM_KSENSOR_KSWITCH_DOORBELLBTN	= 203, // 门铃按扭触发;

} HW_ALM_KSENSOR_TYPE_EN;

//
// 数字传感器报警(HW_ALM_INPUT_DSENSOR)子类型
typedef enum 
{
	HW_ALM_DSENSOR_DSWITCH_UP 		= 301, // 数字传感器超出限制(高);
	HW_ALM_DSENSOR_DSWITCH_DOWN		= 302, // 数字传感器超出限制(低);

} HW_ALM_DSENSOR_TYPE_EN;

//
// 系统故障报警(HW_ALM_INPUT_SYSTEM)子类型
typedef enum 
{
	HW_ALM_SYSTEM_EXTDEV_DISCONNECT	= 401, // 外部设备失联(除了video、ksensor、dsensor以外的外部设备，预留);
	HW_ALM_SYSTEM_DISK_FULL			= 402, // 磁盘满，不能继续录像(system);
	HW_ALM_SYSTEM_DISK_ERROR		= 403, // 磁盘错误，不能继续写入(system);	
	HW_ALM_SYSTEM_DISK_NOSDCARD		= 404, // 开机时未检测到SD卡(system);
	HW_ALM_SYSTEM_DISK_MOUNTFAIL	= 405, // 检测到SD卡但加载失败(system);
	
	HW_ALM_SYSTEM_DISK_ERRORFILE    = 406, // SD卡上太多error文件，建议格式化(system);
	HW_ALM_SYSTEM_DISK_REMOVE   	= 407, // SD卡被拔掉(system);	
	HW_ALM_SYSTEM_DISK_MULTIERROR	= 408, // 文件读写错误太频繁,建议断电后插拔SD卡,然后重新上电,如果问题依旧存在,请格式化SD卡(system);
	HW_ALM_SYSTEM_LOW_BATTERY	= 409, // 电量低于20%;

	HW_ALM_SYSTEM_BUTT

} HW_ALM_SYSTEM_TYPE_EN;

//
// 输出开关量动作
typedef enum 
{
	HW_ALM_KOUT_ACT_SWITCH_ON 		= 501, // 开关量输出打开;
	HW_ALM_KOUT_ACT_SWITCH_OFF 		= 502, // 开关量输出关闭;
} HW_ALM_KOUT_ACT_EN;

//
// 数字输出开关量动作
typedef enum 
{
	HW_ALM_DOUT_ACT_CMD_1 		= 601, // 数字输出开关量动作命令1;
	HW_ALM_DOUT_ACT_CMD_2 		= 602, // 数字输出开关量动作命令2;	
	HW_ALM_DOUT_ACT_CMD_3 		= 603, // 数字输出开关量动作命令3;
	HW_ALM_DOUT_ACT_CMD_4		= 604, // 数字输出开关量动作命令4;
	HW_ALM_DOUT_ACT_CMD_5		= 605, // 数字输出开关量动作命令5;
	HW_ALM_DOUT_ACT_CMD_6		= 606, // 数字输出开关量动作命令6;
	HW_ALM_DOUT_ACT_CMD_7		= 607, // 数字输出开关量动作命令7;
	HW_ALM_DOUT_ACT_CMD_8		= 608, // 数字输出开关量动作命令8;
	HW_ALM_DOUT_ACT_CMD_9		= 609, // 数字输出开关量动作命令9;
	HW_ALM_DOUT_ACT_CMD_10		= 610, // 数字输出开关量动作命令10;

	HW_ALM_DOUT_ACT_CMD_BUTT
} HW_ALM_DOUT_ACT_EN;

//
// 摄像机动作
typedef enum 
{
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_1 		= 701, // 调用热点区域1;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_2 		= 702, // 调用热点区域2;	
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_3 		= 703, // 调用热点区域3;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_4		= 704, // 调用热点区域4;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_5		= 705, // 调用热点区域5;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_6		= 706, // 调用热点区域6;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_7		= 707, // 调用热点区域7;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_8		= 708, // 调用热点区域8;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_9		= 709, // 调用热点区域9;
	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_10		= 710, // 调用热点区域10;

	HW_ALM_CAMERA_ACT_CALL_HOTPOINT_BUTT
} HW_ALM_CAMERA_ACT_EN;

// 
// 位置方向
typedef enum
{
	CD_NORTHERN_LATITUDE = 'N',	// 北纬
	CD_SOUTH_LATITUDE	 = 'S',	// 南纬
	CD_WEST_LONGITUDE	 = 'W', // 西经
	CD_EAST_LONGITUDE	 = 'E',	// 东经
} COORDINATE_DIRECTION_EN;

//
// 回放请求返回的回调参数,目的是告知客户端回放控制失败的原因;
typedef enum _ReplayResEn_
{
    REPLAY_RES_SUCCESS = 1,        // 请求成功;
    REPLAY_RES_TOO_MANY_CLIENTS,   // 太多有户播放;
    REPLAY_RES_NOMORE_FILE,        // 播放到了最后一个文件,ipc停止了回放;
} HWSDK_REPLAY_RES_EN;

//  
//  画面翻转
typedef enum 
{
    //  0-3 对应旋转
    HW_ROTATE_NONE = 0,  //  不翻转
    HW_ROTATE_180 = 1,  //  180度翻译
    HW_ROTATE_90 =  2,   //  90度
    HW_ROTATE_270 = 3,  //  270度
    //  4-5 对应镜像翻转
    HW_ROTATE_FLIP_NONE = 4,  //  没有镜像
    HW_ROTATE_FLIP_HORI = 5, //  水平镜像翻转
    HW_ROTATE_FLIP_VERT = 6, //  垂直镜像翻转
    HW_ROTATE_FLIP_HOVE = 7, //  水平+垂直镜像翻转
} HW_ROTATE_EN;

//  
// 获取设备更多参数
typedef enum
{
    HW_MULTI_CONF_ARM_FLAG_RESBIT   = (0x01),   // 侦测布防
    HW_MULTI_CONF_SEN_LEVEL_RESBIT  = (0x02),   // 灵敏度
    HW_MULTI_CONF_ONL_ALARM_RESBIT  = (0x04),   // 是否只录制报警录像
    HW_MULTI_CONF_AUD_RECORD_RESBIT = (0x08),   // 录像时是否录制音频
    HW_MULTI_CONF_DIS_NUM_RESBIT    = (0x10),   // 磁盘数量
    HW_MULTI_CONF_DIS_ATTR_RESBIT   = (0x20),   // 每个硬盘的信息数组
    HW_MULTI_CONF_PWRFREQ_RESBIT    = (0x40),   // 设备电源频率
    HW_MULTI_CONF_ROTATE_RESBIT     = (0x80),   // 旋转属性
    HW_MULTI_CONF_FLIP_RESBIT       = (0x0100), // 翻转属性 
    HW_MULTI_CONF_VOLUME_RESBIT     = (0X0200), // 音量属性,表示volume,slaveVolume,micVol,slaveMicVol这四个音量属性
    HW_MULTI_CONF_PICSNAP_RESBIT    = (0X0400), // PIR属性
}  HW_MULTI_CONF_RESBIT_EN;

// 
// 报警记录类型
typedef enum
{
	HW_REC_TYPE_NORMAL = 0,		// 通用, 原来获取报警数量和详细报警消息使用这个即可;
	HW_REC_TYPE_VISITOR,		// 门铃访客, 门铃专用;
	HW_REC_TYPE_BUTT,
} HW_REC_TYPE_EN;

typedef struct _FrameHeadAttr_  // attribute
{
	unsigned char 	dataType:3;		// 数据类型, 0:视频; 1:音频; 2:智能数据(如osd或者其它描述)
	unsigned char	frameHeadLen:5;	// 帧头长度,该长度根据FRAME_HEAD_T 的大小变化	
    unsigned char   sizeOfSps;
    unsigned char   sizeOfPps;
	char			reserved[1];
} PACK_ALIGN FRAME_HEAD_ATTR_T;

// 音视频帧头描述
typedef struct _FrameHead_
{                                // <视频定义>              |   <音频定义>	   	
	unsigned int  	frameLen;   // 帧裸流长度               |	帧裸流长度
	unsigned int  	frameNo;    // 帧号,单调递增            |	帧号,单调递增
	unsigned int 	tsSec;      // 时间戳, 单位:秒          |	保留	
	unsigned int 	tsUsec;     // 时间戳, 单位:微秒        |	保留
	unsigned short 	width;      // 视频宽度                 |	保留
	unsigned short 	height;     // 视频高度                 |	采样率: 0, 8000; 1, 16000
	unsigned char 	frameRate;  // 视频:帧率                |	通道模式: 0, 单通道(Mone); 1, 立体声
	unsigned char 	frameType;  // 视频:1,关键帧;0,非关键帧 |	位宽: 0, 8bit; 1, 16bit
	unsigned char	encType;    // 编码类型,见HW_ENC_TYPE   |	编码类型,见HW_ENC_TYPE
	char			level;		// 码率级别,见HW_VRL_EN		|	保留 
} PACK_ALIGN FRAME_HEAD_T;

typedef struct _StreamHead_
{
	FRAME_HEAD_ATTR_T 	fha;			// frame head attribute
	FRAME_HEAD_T		frameHead;
} PACK_ALIGN STREAM_HEAD_T;

typedef struct _ProconHead_
{
	int type;	// 数据类型,DATA_TYPE_EN 中的其中一种
	int len;	// 节点数据的大小
} PACK_ALIGN PROCON_HEAD_T;

typedef struct _ProConNode_
{
	PROCON_HEAD_T 	proconHead;
	char 			data[1]; // 存放一帧音视频数据, 帧头 + 裸流, 帧头参考 STREAM_HEAD_T;
} PACK_ALIGN PROCON_NODE_T;

typedef struct
{
    unsigned int totalSize;	// 该硬盘的总容量, 单位: 兆
    unsigned int freeSize;	// 该硬盘的剩余容量, 单位: 兆
} PACK_ALIGN HWSDK_DISK_ATTR_T;
#if 0
typedef struct
{
    char model[16];		// 设备型号
    char devId[52];		// 最长支持48 个字节的的ID
    char devType[16];	// 设备类型 "nvr/ipc/dvr"
    char version[16];	// 如"v1.23"
    unsigned char vch;	// 视频通道数
    unsigned char ach;	// 音频通道数
    unsigned char kin;	// 输入开关量数量
    unsigned char kout; // 输出开关量数量
    char vencStandard[16]; 		// 当前视频编码标准, 如"jpeg/fmpeg4/h.264/h.265" 
    char aencStardard[16]; 		// 当前音频编码标准, 如"AAC/g711a/g711u/g726/mp3"
    char allResolution[84]; 	// 设备所支持的所有分辨率, 用半角分号区分开来: "1920X1080;1080X720;640X360;704X576" 
    unsigned char diskNum;		// 总共有多少个磁盘, 最多支持8 个
    char unsued[3];				// 对齐
    HWSDK_DISK_ATTR_T diskAttr[8]; 	// 每个硬盘的信息
} PACK_ALIGN HWSDK_DEV_STATUS_T;
#endif

typedef struct
{	
    char	mac[24];			// 只读, 物理地址, 例如"00:25:63:63:25:ba"
    char	ip[16];				// ip地址例如:"192.168.111.254"	
    char	gateway[16];		// 网关, 例如:"192.168.111.1"
    char	netmask[16];		// 子网掩码, 例如:"255.255.255.0"
    unsigned char	dhcpEnable;	// 1: DHCP, 0: STATIC
    unsigned char 	enableFlag;			// 1: 启用, 0: 停用,有线网卡总是启用
    unsigned char   inUse;      //  是否在使用, 1 使用 , 0 没用
    char	reserved[9];
} PACK_ALIGN HWSDK_NET_WIRED_INFO_T;

typedef struct
{	
    char	mac[24];			// 只读, 物理地址, 例如"00:25:63:63:25:ba"
    char	ip[16];				// ip地址例如:"192.168.111.254"	
    char	gateway[16];		// 网关, 例如:"192.168.111.1"
    char	netmask[16];		// 子网掩码, 例如:"255.255.255.0"

    char    appName[32];				// 已经链接上的app 的名字, 如"free-wifi"
    char 	passwd[32];					// wifi 的密码
    unsigned char 	appStrength;		// 当前链接APP 的信号强度 [0,5]	
    unsigned char	dhcpEnable;			// 1: DHCP, 0: STATIC
    unsigned char 	enableFlag;			// 1: 启用, 0: 停用	
    unsigned char	status;				// 只读, 0,在线; 1, 断线
    unsigned char   inUse;      //  是否在使用, 1 使用 , 0 没用
    char	reserved[8];
} PACK_ALIGN HWSDK_NET_WIFI_INFO_T;

typedef struct
{	
    char	dns1[16];	// dns 1例如:"202.96.134.133"
    char	dns2[16];	// dns 2例如:"202.96.128.86"
} PACK_ALIGN HWSDK_NET_COM_INFO_T;

typedef struct
{
    HWSDK_NET_WIRED_INFO_T 	    wiredInfo; 	// 有线网信息
    HWSDK_NET_WIFI_INFO_T		wifiInfo;	// wifi网信息
    HWSDK_NET_COM_INFO_T		comInfo;	// 网络公共信息
} PACK_ALIGN HWSDK_NET_INFO_T;

typedef struct
{
    unsigned char   isCanUse;			// 0, 不能使用; 1, 能使用
    unsigned char 	partIndex;			// 分区索引, 格式化的时候需要用到
    char 			unused[2];
    unsigned int    totalSize;			// 总大小,单位M
    unsigned int    freeSize;			// 剩余空间
} PACK_ALIGN HWSDK_DISK_PART_INFO_T;

typedef struct
{
    unsigned int 	size;				// 大小,单位M
    unsigned char 	partNum;			// 多少个分区
    unsigned char	type;				// 0,SD 卡/TF卡; 1,硬盘; 2, USB 设备	
    unsigned char	diskIndex;			// 硬盘索引, 格式化的时候需要用到
    char  	unused[1];			// 	
    HWSDK_DISK_PART_INFO_T partInfo[MAX_PART_NUM];
} PACK_ALIGN HWSDK_DISK_INFO_T;

typedef struct _SearchRecordRes_
{
	char yearMark[12];		/* 12 X 8 = 96 bits, 可以表示从1970 年开始以后的96 年的录像情况, 
								如果为1 表示该年有录像, 如果为0 表示该年没录像; */
	char dateMark[46];		/* 46 X 8 = 368 bits, 1bit 表示1天, 最多表示366 天, 从每年的1月1日开始算; 
								如果为1 表示该天有录像, 如果为0 表示该天没录像; */
	char date[12];			// 格式"2016-03-30", 本次搜索结果的日期, 考虑到使用回调的方式通知APP;							
	char minuteMark[180]; 	/* 普通录像: 一天 60 X 24=1440 分钟, 每bit 表示1 分钟; 如果为1 
							   表示该分钟有录像, 如果为0 表示该分钟没录像; 需要 1440 / 8 = 180 字节 */
	char minuteMarkAlm[180]; /* 报警录像: 一天 60 X 24 = 1440 bits, 每bit 表示1 分钟; 如果为1 表示该分钟
							   有报警录像, 如果为0 表示该分钟没报警录像; 需要 1440 / 8 = 180 字节 */
    unsigned short recordVer; //  录像版本号, 由sdk填充
	char reserved[62];
	struct _SearchRecordRes_ *next;	// 预留, 暂时为NULL;
} PACK_ALIGN HWSDK_SEARCH_RECORD_RES_T;

typedef struct 
{
    char apAddr[20];  //  物理地址
    int channel;      //  通道号
    char apEssid[33]; //  ap 名称
    char encryptionkey;  //  加密方式 0不加密 1 wep加密 2 wpa2加密
    char matchCnt;       //  
    char quality;        //  信号强度 0-100。
    unsigned char isUtf8;//  编码格式是否是utf8,1:是 0:否;
    char reserve[3];
} PACK_ALIGN HWSDK_WIFI_INFO_T;

typedef struct
{	
	unsigned int 	groupIndex;		// 该相机所在组的index, 同一个设备的几个摄像头可以分到不同的组;
	unsigned int 	devIndex;		// 该相机所在设备的index, 全局唯一的索引;
	unsigned char 	chNum;			// 通道号, 从0 开始;	
	unsigned char  	addFrom;		// 相机来源, 0, 用户自己添加; 1, 别的用户分享;
	unsigned char	ptz;			// 1, 支持云台; 0, 不支持云台;
	unsigned char	isDisplay;		// 1, 需要在APP 上显示; 0, 不需要在APP 上显示;
	char 	chName[128];			// 通道名字;
	char	sharedFrom[128];			// 当addFrom 为1 的时候, 该变量表示分享者账号;
} PACK_ALIGN CAMERA_ATTR_T;

typedef struct
{	
	unsigned int 	groupIndex;		// 该相机所在组的index, 同一个设备的几个摄像头可以分到不同的组;
	unsigned int 	devIndex;		// 该相机所在设备的index, 全局唯一的索引;
	unsigned char 	chNum;			// 通道号, 从0 开始;	
	unsigned char  	addFrom;		// 相机来源, 0, 用户自己添加; 1, 别的用户分享;
	unsigned char	unused;			// 无用;
	unsigned char	isDisplay;		// 1, 需要在APP 上显示; 0, 不需要在APP 上显示;
	char 	chName[128];			// 通道名字;
	char	sharedFrom[128];		// 当addFrom 为1 的时候, 该变量表示分享者账号;
} PACK_ALIGN KSENSOR_ATTR_T;

typedef struct
{	
	unsigned int 	groupIndex;		// 该相机所在组的index, 同一个设备的几个摄像头可以分到不同的组;
	unsigned int 	devIndex;		// 该相机所在设备的index, 全局唯一的索引;
	unsigned char 	chNum;			// 通道号, 从0 开始;	
	unsigned char  	addFrom;		// 相机来源, 0, 用户自己添加; 1, 别的用户分享;
	unsigned char	unused;			// 无用;
	unsigned char	isDisplay;		// 1, 需要在APP 上显示; 0, 不需要在APP 上显示;
	char 	chName[128];			// 通道名字;
	char	sharedFrom[128];		// 当addFrom 为1 的时候, 该变量表示分享者账号;
} PACK_ALIGN KOUT_ATTR_T;



// 客户端向服务器查询到的某个设备的信息
typedef struct _WebsDevInfo_
{
	unsigned int nodeIndex;	// 该设备所在节点的index, 如果是为0 表示在根节点;注意: 如果以相机分组, 则APP 不用理会该变量;
	unsigned int index;		// 设备自己的index, 全局唯一的索引;
	char devId[128];		// 设备ID,例如: AAAABBBB-ABCD-1234-ABCD-123456789001;
	char type[16];			// 设备类型, 例如: ipc,nvr,dvr;
	char name[128];			// 设备名字, UTF-8;
	char authorizedFlag[32]; 	// 认证标识, 比如"normal";
	unsigned char videoCh;		// 视频通道数;
	char ip[20];				// 局域网IP;
	unsigned short port; 		// 局域网登陆的端口;
	char wip[20];				// 公网网IP;
	unsigned short wport; 		// 公网端口;
	char user[32];				// 登陆设备的用户名;
	char pwd[32];				// 登陆设备的密码;
	char natType[8];			// nat 类型, 'A',完全圆锥型; 'B',IP 限制性, 'C',端口限制性, 'D',Symmetric NAT 对称型;
	char p2pIp[20];				// P2P 服务器的IP 地址1	;
	unsigned short p2pPort; 	// P2P 服务器的IP 端口1;
	char tssIp[20];				// 转发服务器IP 地址;	
	unsigned short tssPort; 	// 转发服务器端口;
	char almsIp[20];			// 报警服务器IP 地址;
	unsigned short almsPort; 	// 报警服务器端口;
	char devCode[32];			// 设备编码, 作为查询设备升级信息接口的入参之一;
	char devSoftVersion[20];	// 设备软件版本, 和从设备获取到的版本对比, 决定是否对设备升级;
	char devHardware[32];		// 设备硬件信息, 暂时没用到;
	unsigned char cameraNum;	// 有多少个摄像头;
	CAMERA_ATTR_T *cameraAttr[64];	// 摄像头属性,最多支持64 个通道, 有效个数为[0,cameraNum) ;
	unsigned char ksensorNum;		// 有多少个模拟开关;
	KSENSOR_ATTR_T *ksensorAttr[64];// 模拟开关属性,最多支持64 个通道, 有效个数为[0,cameraNum) ;
	unsigned char koutNum;			// 有多少个模拟输出开关(控制类);
	KOUT_ATTR_T *koutAttr[64];		// 模拟输出开关属性,最多支持64 个通道, 有效个数为[0,cameraNum) ;
	struct _WebsDevInfo_ *next;	
} PACK_ALIGN WEBS_DEV_INFO_T;

// 节点信息 
typedef struct _WebsNodeInfo_
{
	unsigned int parentIndex;		// 父节点索引, 如果为0, 表示他的父节点就是根节点
	unsigned int nodeIndex;			// 本节点索引
	char parentNodeName[128];		// 父节点名字, UTF-8
	char nodeName[128];				// 本节点名字, UTF-8
	
	struct _WebsNodeInfo_ *next;
} PACK_ALIGN WEBS_NODE_INFO_T;

// 组信息 
typedef struct _GroupInfo_
{
	unsigned int index;			// 本节点索引
	unsigned int number;		// 组号码, 排序用
	char groupName[128];		// 组名字
	
	struct _GroupInfo_ *next;
} PACK_ALIGN WEBS_GROUP_INFO_T;

// 从webs 获取到的设备列表信息
typedef struct 
{
	WEBS_DEV_INFO_T 	*pDevInfo;		// 设备链表;
	WEBS_DEV_INFO_T 	*pDevTail;		// APP 在遍历的时候可以不用关注这个变量;
	WEBS_NODE_INFO_T 	*pNodeInfo; 	// 节点链表;
	WEBS_NODE_INFO_T 	*pNodeTail; 	// APP 在遍历的时候可以不用关注这个变量;
	WEBS_GROUP_INFO_T	*pGroupInfo; 	// 组链表 	
	WEBS_GROUP_INFO_T 	*pGroupTail; 	// APP 在遍历的时候可以不用关注这个变量;
} PACK_ALIGN WEBS_DEV_LIST_T;

// 客户端向服务器查询到的某个OEM厂家的信息
typedef struct
{
	char brand[32]; 	// 品牌, 同一个OEM 下可能有很多个brand;
	char oemInc[128]; 	// oem 厂家的名字: 华伍智能技术(深圳)有限公司;
	char oemLogo[128]; 	// logo 的下载地址: http://www.5-smart.com/logo.jpg;
	char address[512]; 	// 公司地址;
	char url[128]; 		// 公司主页;
	char call[32];		// 联系电话;
	char fax[32];		// 传真;
	char post[8];		// 邮编;
	char lang[16];		// 语言, "zh-cn", "us_en";
	char oemEshopurl[128]; 		// 网店的url, 举例: 5-smart.tmall.com;
	char email[128];			// 邮件地址;
	char status[32];			// 状态信息;
	char oemAppname[32];		// App名称;
	char oemNewversion[16];		// App版本;
	char oemdownloadurl[128];	// App下载地址;
	char oemHelpUrl[128];		// 帮助信息地址;	
	char oemAboutUrl[128];		// 关于信息地址;
	char updateInfo[128*1024];	// 新版本信息, 最多支持128KBytes 个字节;
} PACK_ALIGN WEBS_CLIENT_INFO_T;

typedef struct _EventMsg_
{
	unsigned int 	msgIndex; 	// 消息索引, 表示当前第几条消息;
	unsigned int 	devIndex; 	// 设备的唯一索引;	
	unsigned int	almInputType;	// 报警输入类型, 见HW_ALM_INPUT_TYPE_EN
	unsigned int	AlmType; 		// 报警子类型:
								  	// 1) 当 HW_ALM_INPUT_VIDEO == almInputType; 取值范围见HW_ALM_VIDEO_TYPE_EN;	
								  	// 2) 当 HW_ALM_INPUT_KSENSOR == almInputType; 取值范围见HW_ALM_KSENSOR_TYPE_EN;
									// 3) 当 HW_ALM_INPUT_DSENSOR == almInputType; 取值范围见HW_ALM_DSENSOR_TYPE_EN;
									// 4) 当 HW_ALM_INPUT_SYSTEM == almInputType; 取值范围见HW_ALM_SYSTEM_TYPE_EN;
	unsigned char 	chn;		// 通道号:
								// 1) 当 HW_ALM_INPUT_VIDEO == almInputType; 取值范围(0, 设备所支持的视频通道数];	
							  	// 2) 当 HW_ALM_INPUT_KSENSOR == almInputType; 取值范围(0, 设备所支持的视频通道数];
								// 3) 当 HW_ALM_INPUT_DSENSOR == almInputType; 取值范围(0, 设备所支持的视频通道数];
								// 4) 当 HW_ALM_INPUT_SYSTEM == almInputType; 无意义;
	char	unused[3];
	char	*koutAct; 	// 遗弃, 由变量linkage 替换;
						// 报警所联动的模拟开关量动作, 如果没有, 则NULL == koutAct; 如果存在, 取值范围见
						// HW_ALM_KOUT_ACT_EN, 如果一个通道联动多个, 使用'^'链接, 如: 0:501^1:502 
						// 表示该报警联动了开关输出0 的打开动作(501), 同时联动了开关输出1 的关闭动作(502);
						// 该指针存放的全是ascii 字符, 并且以'\0' 为结束符号;
	char	*doutAct; 	// 遗弃, 由变量linkage 替换;
						// 报警所联动的数字开关量动作, 如果没有, 则NULL == doutAct; 如果存在, 取值范围见
					 	// HW_ALM_DOUT_ACT_EN, 如果一个通道联动多个, 使用'^'链接, 如: 0:601^1:602 
					 	// 表示该报警联动了数字开关通道0 执行动作命令1(601), 同时联动数字开关通道1 执行动作命令2(602);
					 	// 该指针存放的全是ascii 字符, 并且以'\0' 为结束符号;
	char	*cameraAct; // 遗弃, 由变量linkage 替换;
						// 报警所联动的摄像机动作, 如果没有, 则NULL == doutAct; 如果存在, 取值范围见
						// HW_ALM_CAMERA_ACT_EN, 如果一个通道联动多个, 使用'^'链接, 如: 0:701^1:702 
						// 表示该报警联动摄像机0调用热点区域1(701), 摄像机1调用热点区域2(702);
						// 该指针存放的全是ascii 字符, 并且以'\0' 为结束符号;
	char 	*linkage;	// 报警发生后的联动动作, 由服务器提供多国语言的字符串, APP 直接显示;
						// +++ 增加该变量是否了替换koutAct, doutAct, cameraAct 这几个变量;
	char 	*picture;	// 报警联动所抓拍的图片, 如果没有, 则NULL == picture; 如果联动了多个视频通道抓拍,使用'^'链接,
						// 如:"168_2_2016_03_28_11_25_23.jpg^168_1_2016_03_28_11_25_23.jpg", 每张图片的格式为
						// 设备index_视频通道号_年_月_日_时_分_秒.jpg.
						// 该指针存放的全是ascii 字符, 并且以'\0' 为结束符号;
	char 	tsUtc[20];	// APP展示给客户看的报警时间, 格式"2016-01-30 20:20:09", 注意, 在展示的时候加上UTC 时间;
	char	srvTime[20];// 报警上报时, 服务器的当前时间, 给APP 使用本地搜索时使用;
	char 	*detail;	// 报警的详细信息, 由服务器提供多国语言的字符串, APP 直接显示;
	float	value;		// 值,它的意义取决于 almType 和 almSubType 的值的组合:
						/*	almType 				|	almSubType					|	values
							HW_ALM_INPUT_SYSTEM		|	HW_ALM_SYSTEM_LOW_BATTERY	|	表示设备剩余电量的百分比[0,100]	
						*/
	struct _EventMsg_ *next;
} PACK_ALIGN ALARM_MSG_T , DOOR_BELL_T;

//
// 某个设备通道1天的报警数量, 如果遍历整个链表都找不到对应的设备, 说明该设备,
// 在所请求的那天没有报警消息产生;
typedef struct _OneDayNewMsgSize_
{
	unsigned int 	devIndex;	// 通道所在设备的索引, 当 CHN_TYPE_SYSTEM == chnType, 该变量没意义;
	unsigned char	chnType;	// 通道类型, 见HW_CHN_TYPE_EN;
	unsigned char	chn;		// 某个设备的通道, 当 CHN_TYPE_SYSTEM == chnType, 该变量没意义;
	unsigned int  	size;		// 有多少条报警信息, +++ 大于100 条的时候, APP 显示"99+"即可;
	ALARM_MSG_T		lastMsg;	// 最新的报警消息, 当 CHN_TYPE_SYSTEM == chnType, 该变量没意义;
								// +++ 该变量暂时只使用到它所属类型里面的picture 变量;
	struct _OneDayNewMsgSize_ *next;	
} ONE_DAY_NEW_MSG_SIZE_T;

//
//批量获取图片的请求参数结构
typedef struct _GetPicParam_
{
    unsigned int picType;       // 要获取的图片类型, 取值范围参见:PIC_TYPE_EN;
    unsigned int eventType;     // 当PIC_TYPE_REALTIME == picType, 表示表示获取设备当前截取的一张图片, eventType 无效;
                                // 当PIC_TYPE_ALARM = picType, 为报警类型, 对应ALARM_MSG_T 里面的AlmType 参数;
                                // 当PIC_TYPE_PRESET == picType, 表示表示获取获取某个预置位的图片, eventType 无效;
    int chn;                    // 当PIC_TYPE_REALTIME == picType, 表示视频的通道号;
                                // 当PIC_TYPE_ALARM = picType, 对应ALARM_MSG_T 里面的chn 参数;
                                // 当PIC_TYPE_PRESET == picType, 表示预置位所在的视频通道号;
    char context[64];           // 当PIC_TYPE_REALTIME == picType, 该参数没意义;
                                // 当PIC_TYPE_ALARM = picType,对应ALARM_MSG_T 里面的picture 参数;
                                // 当PIC_TYPE_PRESET == picType, 表示预置位号[1,8], 用字符串表示, 例如:"1"、"2"、"3";
} HWSDK_GET_PIC_PARAM_T;

//
// 用户登录时返回一些简单的信息, 提高用户体验, 例如昵称, 不用专门用一条指令去获取昵称
typedef struct
{
	char nickname[128];		// 昵称;
	int userValue;			// 用户经验值;
	int userDiamons;		// 用户砖石数;
	int userSuns;			// 用户太阳数;
	int userMoons;			// 用户月亮数;
	int userStars;			// 用户星星数;
	char reserved[1004];	// 
} LOGIN_RES_T;

//
// 所有的新消息
typedef struct _AllNewMsgSize_
{
	ONE_DAY_NEW_MSG_SIZE_T *today;		// 今天
	ONE_DAY_NEW_MSG_SIZE_T *yesterday;	// 昨天
	ONE_DAY_NEW_MSG_SIZE_T *beforeYesterday; // 前天
	ONE_DAY_NEW_MSG_SIZE_T *moreDay;	// 三天前
} ALL_NEW_MSG_SIZE_T;

//
// 所有的新消息
typedef struct
{
	ONE_DAY_NEW_MSG_SIZE_T *anyDay;	// 所有日期的消息
} ANYDAY_NEW_MSG_SIZE_T;

//
// 设备版本参数
typedef struct _DevVersionParam_
{
	char version[16];		// 最新的版本号, 格式举例:"1.0.0.11";
	char reserved[1024];	//
} HWSDK_DEV_VERSION_PARAM;

//
// 设备更多参数;
typedef struct
{
    unsigned char   	armFlag;			// 0: 撤防(设备不启动移动侦测); 1: 布防(设备启动移动侦测);
    unsigned char 		sensitiveLevel;		// 灵敏度, [1,5], 值越大灵敏度越高;
    unsigned char       isOnlyAlarmRec;	    // 0, 全天录像, 包括报警录像; 1, 只有报警时才录像;
    unsigned char       isAudioRec;		    // 0, 录像时只录制视频; 1, 录制时同时录制音视频;
    
    unsigned char       rotate;	            // 旋转;
    unsigned char       flip;			    // 翻转;
    unsigned char       volume;		        // 音量[0-100],ipc,nvr,门铃主机扬声器音量;
    unsigned char       diskNum;		    // 总共有多少个磁盘, 最多支持8 个;
    
    HWSDK_DISK_ATTR_T   diskAttr[8]; 	    // 每个硬盘的信息;
    
    unsigned short      pwrFreq;            // 电源频率;
    unsigned char       slaveVolume;        // [0-100],门铃从机扬声器音量;
    unsigned char       micVol;             // [0-100],ipc,nvr,门铃主机mic音量;
    
    unsigned int        resBits;            // 每位对应一个参数的返回结果, 0表示失败，1成功;
    unsigned char       slaveMicVol;        // [0-100],门铃从机mic音量;
    unsigned char       pirSnap;            // 感应拍照 0,关闭 1，打开;

    unsigned char       reserved[510];
} PACK_ALIGN HWSDK_GET_MULTI_CONF_T;

typedef enum _UpdateState_
{
    UPDATE_SEND_CMD = 0,             //  已发送升级命令
    UPDATE_GET_CMD = 1,              //  收到升级命令
    UPDATE_GET_FILEURL,              //  获取升级文件url
    UPDATE_DOWNLOAD_FILE,            //  下载文件
    UPDATE_DOWNLOAD_FILE_END,        //  下载文件完成
    UPDATE_WRITE_FLASH,              //  开始升级
    UPDATE_WRITE_FLASH_END,          //  完成升级
    UPDATE_REBOOT,                   //  准备重启
    UPDATE_IS_NEWEST,                //  已经是最新不需要升级
    UPDATE_OTHER_UPDATE,             //  其它客户在升级
    UPDATE_FAIL,                     //  升级失败
} UPDATE_STATE_EN;

//  磁盘格式化
typedef enum 
{
    FORMAT_ING = 1,             //  正在格式化 1
    FORMAT_END,             //  格式化完成 2
    FORMAT_FAIL,            //  格式失败 3 
} FORMAT_STATE_EN;

//
// 迅美安装模式参数;
typedef enum
{
    HWSDK_XM_INS_MODE_SUCTIONTOP    = 1,    // 吸顶模式;
    HWSDK_XM_INS_MODE_DESKTOP       = 2,    // 桌面模式;
    HWSDK_XM_INS_MODE_WALLLOAD      = 3,    // 壁装模式;
} HWSDK_XM_INS_MODE_E;

//
// 迅美鱼眼模式参数;
typedef enum
{
    HWSDK_XM_FISHEYE_MODE_FISHEYE   = 1,    // 鱼眼模;
    HWSDK_XM_FISHEYE_MODE_PTZ       = 2,    // PTZ;
    HWSDK_XM_FISHEYE_MODE_DEG180    = 3,    // 水平180;
    HWSDK_XM_FISHEYE_MODE_DEG360    = 4,    // 360;
    HWSDK_XM_FISHEYE_MODE_FOURSEG   = 5,    // 四分割;
} HWSDK_XM_FISHEYE_MODE_E;

typedef enum {
    PTZ_CTRL_STOP = 100, 
    PTZ_CTRL_MOVE_UP,           // 向上移动;
    PTZ_CTRL_MOVE_DOWN,         // 向下移动;
    PTZ_CTRL_MOVE_LEFT,         // 向左移动;
    PTZ_CTRL_MOVE_RIGHT,        // 向右移动;
    PTZ_CTRL_MOVE_UPLEFT,       // 向左上移动;
    PTZ_CTRL_MOVE_DOWNLEFT,     // 向左下移动;
    PTZ_CTRL_MOVE_UPRIGHT,      // 向右上移动;
    PTZ_CTRL_MOVE_DOWNRIGHT,    // 向右下移动;

    PTZ_CTRL_SET_PSP,           // 设置预制位;
    PTZ_CTRL_CALL_PSP,          // 获取预制位;
    PTZ_CTRL_DELETE_PSP,        // 删除预制位;

    PTZ_CTRL_BEGIN_CRUISE_SET,  // 
    PTZ_CTRL_SET_CRUISE,        // 
    PTZ_CTRL_END_CRUISE_SET,    // 
    PTZ_CTRL_CALL_CRUISE,       // 
    PTZ_CTRL_DELETE_CRUISE,     // 
    PTZ_CTRL_STOP_CRUISE,       // 

    PTZ_CTRL_AUTO_SCAN,         // 

    PTZ_CTRL_RAINBRUSH_START,   // 
    PTZ_CTRL_RAINBRUSH_STOP,    // 
    PTZ_CTRL_LIGHT_ON,          // 
    PTZ_CTRL_LIGHT_OFF,         // 

    PTZ_CTRL_MAX
} PTZ_CTRL_E;

//
// 接收音视频流回调;
// context: 上下文, HwsdkRealTimeStreamStart() 第三个参数的返回值;
// pnt: 流数据及其描述;
typedef int (*HW_STREAM_RECV_CB)( unsigned long context, PROCON_NODE_T *pnt );
// typedef HW_STREAM_RECV_CB HW_PLAYBACK_RECV_CB;

// 接收回放数据包回调;
// context: 上下文, HwsdkDevSearchRecord() 第五个参数的返回值, 绑定回放的设备端和通道号;
// pnt: 流数据及其描述;
// playbackSessID: 回放的sessionID,用于防止切换回放文件时收到上次回放的数据,范围[1,127];
typedef int (*HW_PLAYBACK_RECV_CB)( unsigned long context, PROCON_NODE_T *pnt, unsigned char playbackSessID );

//
// 接收录像搜索结果的回调;
// context: 上下文, HwsdkSearchRecord() 最后一个参数的返回值;
// hsrr: out, 某天的录像搜索结果;
typedef int (*HW_SEARCH_RECORD_RES_CB)( unsigned long context, HWSDK_SEARCH_RECORD_RES_T *hsrr );

//
// 接收报警消息;
// alarmMsg: 消息描述;
typedef int (*HW_DEV_REPORT_MSG_CB)( ALARM_MSG_T alarmMsg );

//
// 设备上下线;
// devIndex: 设备的唯一索引;
// onOFF: 0, 离线; 1, 上线;
// 注意:设备上线: APP获取设备列表(离线)->sdk 尝试连接所有设备->使用本回调函数把连接上的设备通知app;
//      设备下线: sdk 维护所有已经在线的设备->检测到设备掉线->使用本回调函数把连接上的设备通知app;
//		设备重新上线: sdk 对设备进行重连->设备重新上线->使用本回调函数把连接上的设备通知app;
typedef int (*HW_DEV_ONOFF_CB)( unsigned int devIndex, int onOFF );

//
// 接收到图片回调, 对应HwsdkDevGetPic() 的请求;
// devIndex: 设备的唯一索引, 对应HwsdkDevGetPic() 的 devIndex参数;
// picType: 图片类型, 对应HwsdkDevGetPic() 的 picType参数;
// eventType, 事件类型, 对应HwsdkDevGetPic() 的 eventType参数;
// chn: 通道号, 对应HwsdkDevGetPic() 的 chn参数;
// context: 上下文, 对应HwsdkDevGetPic() 的 context参数;
// pic: 图片数据, 暂时支持jpg 格式;
// picSize: 图片数据的长度, 为0 表示图片文件不存在;
typedef int (*HW_DEV_RECV_PIC_CB)( unsigned int devIndex, unsigned int picType, 
									unsigned int eventType, int chn, char context[64], 
									char *pic, unsigned int picSize );

//
// 事件回调, 主要用于一些比较通用的回调交互;
// event: 参见 COM_EVENT_EN;
// param1: 根据event 的不同具有不同的意义;
// param2: 根据event 的不同具有不同的意义;
/* event、param1、param2 组合如下:
*   event  						| param1                            |  param2
    1(CE_CLIENT_INDEX)    		| 服务器返回给客户端的index          |  无意义  
    2(CE_WIFI_CONNECT_PROGESS)	| 链接wifi的进度,百分比[0,100]		|  无意义
    3(CE_WIFI_IP)				| 某个设备连接上wifi 的IP 地址       |  无意义
    4(CE_DEV_ONLINE)			| 设备index							|  登陆码
    5(CE_DEV_OFFLINE)			| 设备index							|  无意义
    6(CE_DEV_SVR)				| 设备index							|  无意义
    7(CE_PLAYBACK_RES)          | 请求回放的channel                  |  错误码，见HW_CERROR_TYPE_EN
    8(CE_CHANNEL_STATE_LOW)     | 设备index                         |  NVR设备的通道状态信息,取后32位（unsigned long可能有64位或32位）,1 bit对应一个通道,低位算起;
                                                                        表示通道 0-31的通道状态,bit置1表示有视频,0没有视频;
                                                                        例如: 0001 0000 0000 0000 0000 0000 0000 0000 表示channel=28 通道视频可用;
    9(CE_CHANNEL_STATE_HIGH)    | 设备index                         | 表示32-63的通道状态;
                                                                        例如: 0000 0000 0000 00000 0000 0000 00000 0001 表示channel=32 通道视频可用;
	10(CE_MNG_IP)				| 管理服务器的IP 地址, APP 需要保存   |  端口
    11(CE_CHANNEL_SWITCH)       | 设备index                         |  实时流数据通道状态,0:表示P2P,1:表示转发,2:表示局域网;
    12(CE_DEV_SLEEP)			| 设备index							|  无意义
    13(CE_DEV_ELECTRICITY)      | 设备index                          |  电量的百分比[0,100]
*/
typedef int (*FN_COM_EVENT_CB)( unsigned long event, unsigned long param1, unsigned long param2 );

//
// 通用数据回调, 主要用于一些比较通用的回调交互;
// event: 参见 COM_DATA_EN;
// param1: 根据event 的不同具有不同的意义;
// param2: 根据event 的不同具有不同的意义;
/* event、param1、param2 组合如下:
*   event  								| param1                |  param2			|	pData
    1(CD_UNVARNISHED_TRANSMISSION)    	| 设备的index         	|  透出数据的长度  	|	具体的数据;
    2(CD_DEBUG_DATA)					| 保留					|  保留				|	调试数据,该数据以'\0' 为结束符;
*/
typedef int (*FN_COM_DATA_CB)( unsigned long event, unsigned long param1, unsigned long param2, char *pData );


/*
* fn:升级进度回调
* state: 升级状态, 见 UPDATE_STATE_EN;
* percent:
*   当state 为 UPDATE_DOWNLOAD_FILE 时表示下载进度
*   当state 为 UPDATE_WRITE_FLASH   时表示升级进度
*   其它状态，percent 没有意义
*/
typedef int (*FN_UPDATE_PERCENT_CB)( int state, int percent );

/*
* fn: 设置Wifi 结果回调函数;
* result: 表示设置wifi的结果,-1设置失败，0表示成功;
* ip: 成功连接后( result==0 )返回ip，其它情况为NULL;
*/
typedef int (*HWSDK_SEARCH_DEV_RESULT_CB)( char result, char *ip );

/*
* fn: 获取Wifi列表 结果回调函数
* wifiList: wifi 信息数组指针
* num: wifiList 数组大小, 表示有多少个wifi。
* totalnum: 总共有多少条wifi, 因为是返回多次回调，方便回调全部返回后马上返回， 不用等超时
*/
typedef int (*HWSDK_GET_WIFILIST_CB)( unsigned int sessIndex, HWSDK_WIFI_INFO_T *wifiList, int num, unsigned short totalnum );

/*
* fn:格式化sd卡进度回调
* state: 格式化状态, 见 FORMAT_STATE_EN;
* percent:
*   当state 为 FORMAT_ING 时表示格式化进度
*   其它状态，percent 没有意义
*/
typedef int (*HWSDK_FORMAT_PERCENT_CB)( int state, int percent );

//
// 初始化sdk 结构体
typedef struct
{
	char ipAddr[20];									    // APP 所在手机的IP 地址, 格式"192.168.025.210" 如果网络切换了, 则需要重新填充该变量;
    char hwpDns[128];                                       // 仅仅供开发人员/测试人员使用,华伍平台的DNS服务器地址，格式"###actapi.iotor.net###"，如果没有, 则使hwpDns[0] = '\0';
	char logPath[128];									    // 仅仅供开发人员/测试人员使用,日志存放路径，格式"##/5-smart/log##"，如果没有, 则使logPath[0] = '\0';
	unsigned char 			        cliType;				// 客户端类型, sdk 需要根据不同的客户端类型向服务器获取不同的数据, 取值范围CLI_TYPE_EN;
	unsigned long 			        clientIndex;			// 客户端全局唯一index, 由web 服务器分配,如果没有则传0;该值由本结构体的pComEventFunc 函数返回;
	unsigned long 					mngIp;					// 管理服务器IP 地址,如果没有则传0;该值由本结构体的pComEventFunc 函数返回;
	unsigned short					mngPort;				// 管理服务器端口,如果没有则传0;该值由本结构体的pComEventFunc 函数返回;		
	char 							paramReserved[3952];	// 参数预留空间;
	HW_STREAM_RECV_CB		        pStreamRecvFunc;		// 接收音视频流回调函数;	
	HW_PLAYBACK_RECV_CB	  	        pPlaybackRecvFunc;		// 接收回放音视频流回调函数;
	HW_SEARCH_RECORD_RES_CB         pSearchRecordResFunc;	// 录像搜索结果返回回调函数;
	HW_DEV_REPORT_MSG_CB	        pDevReportMsgFunc;		// 设备上报消息回调函数;	
	HW_DEV_ONOFF_CB			        pDevOnOffFunc;			// 设备上下线回调函数;	
	HW_DEV_RECV_PIC_CB		        pDevRecvPicFunc;	    // 接收到图片回调函数;
	FN_COM_EVENT_CB			        pComEventFunc;			// 事件回调, 主要用于一些比较通用的回调交互;
	FN_UPDATE_PERCENT_CB	        pUpdatePercentFunc;		// 升级进度回调;
    HWSDK_GET_WIFILIST_CB           pGetWifilistFunc;       // 获取wifi列表回调;
    HWSDK_FORMAT_PERCENT_CB         pFormatPercentFunc;     // 格式化sd进度回调;
    HWSDK_SEARCH_DEV_RESULT_CB      pSearchDevResFunc;      // 设备搜索返回回调;
    FN_COM_DATA_CB					pComDataFunc;			// 通用数据回调
	char			          		funcReserved[7*1024 - 16]; 	// 回调函数预留空间;
} PACK_ALIGN INIT_HWSDK_PARAM_T;

#ifdef WIN32
#pragma pack(pop)
#undef PACK_ALIGN
#else
#undef  PACK_ALIGN
#endif

#endif // __HWSDKTYPE_H__

