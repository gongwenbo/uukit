/*
*******************************************************************************
**  Copyright ( c ) 2012, 深圳市有限公司, All rights reserved.
**  作者：梁桥江
**  当前版本：v1.0
**  创建日期: 2015.10.26
**  文件说明: 客户端sdk 接口函数
    使用注意事项: 
    1. 所有函数的返回值, 如果没有特别说明, 则返回0 表示成功; 返回-1 表示失败未知错误;
    	返回其它值所代表的意义请参见枚举 CERROR_TYPE_EN;
    	特别注意: 如果函数的放回值为指针, 而且为NULL, 则错误码在函数的 detail 参数返回,
    	格式为 "errno=%d",所以APP 可以根据detail 返回的值得前5 个字节是否为"errno "来
    	判断是错误信息来自本地还是服务器;
    2. 每个登录的用户只支持1 路回放, 不支持多路回放;
    3. 如果函数的参数注释有带"out" 关键字, 则表示该参数有返回值;
    4. 对于所有接口, 都以Hwsdk 开头, 紧接着是接口访问的对象关键字(如果没有则表示本地接口), 
       然后就是接口所实现的功能;
       接口访问的对象关键字为:
       1) Mng 管理服务器
       2) Dev 访问设备
       3) P2pd p2p 服务器
    5. 所有指针和数组参数, 除了有说明可以为NULL, 否则不能为NULL;
    6. 所有输入输出参数, 如果为中文, 都为UTF-8 格式;
    7. 带有"+++" 关键字部分为对接时比较容易犯错误部分, 请认真细读;
    8. 关于平台统一错误号:
       1) 所有函数的返回值使用错误号表示;
       2) 如果返回值是指针, 则在返回的详细信息后面加上错误号, 例如:
       		"This device is not exist|errno=40125"
       '|' 前面表示详细信息; 
       '|' 后面表示错误号; 
*******************************************************************************
*/ 

#ifndef __HWSDK_H__
#define __HWSDK_H__

#ifdef WIN32
#define HWSDK_API extern "C" __declspec(dllexport)
#else
#define HWSDK_API // extern "C"
#endif // #ifdef WIN32

#include "hwsdkType.h"
#include "const.h"

/*
* fn: 初始化SDK, 在调用其它接口函数前必须先调用本接口初始化资源;
* param: 初始化结构体, 里面的成员如果没有特别说明,
		则必须赋值, 不能为NULL, 否则会产生未知错误.
*/
HWSDK_API int HwsdkInit( INIT_HWSDK_PARAM_T *param );
//test 

void HwsdkTestDoorBeel(char *hostFromEngineer, unsigned long mngHostFromApp, unsigned short mngPortFromApp );


/*
* fn: 去初始化SDK, 如果不再使用sdk 接口, 或者需要重新初始化, 则
      需要先调用本接口进行释放资源.
*/
HWSDK_API int HwsdkDeInit();

/*
* fn: 检验账号是否能用;
* account: 账号，可为手机号、邮箱;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 0, 可用; -1, 不可用.
*/
HWSDK_API int HwsdkMngCheckRigster( char *account, char *language, char *detail, int detailSize );

/*
* fn: 申请注册码;
* account: 账号，可为手机号、邮箱;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* oemId：针对OEM客户的客户编码，在定制软件时事先设置, 如"oem8001";
* oemBrand：OEM品牌名称，在定制软件时事先设置, 如 "nobrand"为中性;
* timezone: 时区, [-12, +11];
* rigsterCode: out, 注册码;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngApplyRigsterCode( char *account, char *language, char *oemId, 
										char *oemBrand, float timezone, char rigsterCode[16],
										char *detail, int detailSize );

/*
* fn: 注册用户;
* account: 账号，可为手机号、邮箱;
* pwd1: 第一次输入的密码;
* pwd2: 第二次输入的密码;
* rigsterCode: 从接口HwsdkMngApplyRigsterCode() 获取到的注册码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* from: 用户来源，为客户端对应的IP;
* oemId：针对OEM客户的客户编码，在定制软件时事先设置, 如"oem8001";
* oemBrand：OEM品牌名称，在定制软件时事先设置, 如 "nobrand"为中性;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngRigster( char *account, char *pwd1, char *pwd2, char *rigsterCode, 
								char *language, char *from, char *oemId, 
								char *oemBrand, char *detail, int detailSize );

/*
* fn: 申请找回密码, 在忘记密码时, 用本接口申请一个验证码, 作为HwsdkMngRecoverPwd()
	  的入参, 重新找回密码;
* account: 账号，可为手机号、邮箱;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* oemId：针对OEM客户的客户编码，在定制软件时事先设置, 如"oem8001";
* oemBrand：OEM品牌名称，在定制软件时事先设置, 如 "nobrand"为中性;
* identifyCode: out, 验证码;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngApplyRecoverPwd( char *account, char *language, char *oemId, 
										char *oemBrand, float timezone, char *identifyCode,  
										char *detail, int detailSize );

/*
* fn: 找回密码;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* identifyCode: 验证码, 等于从HwsdkMngApplyRecoverPwd() 接口参数identifyCode 返回的值;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngRecoverPwd( char *account, char *pwd, char *language,
							char *identifyCode, char *detail, int detailSize );

/*
* fn: 使用旧密码修改新密码;
* account: 账号，可为手机号、邮箱;
* pwd: 旧密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* newPwd: 新密码;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngModifyPwd( char *account, char *pwd, char *language,
							char *newPwd, char *detail, int detailSize );

/*
* fn: 查询设备的拥有者把该设备分享给哪些用户;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devChannels: 要查询的设备通道, 格式为"AAAABBBB-ABCD-1234-ABCD-123456789001:2",
				":" 往前表示设备ID, 往后表示通道号;
* accountWhoIndate: out, 把该设备分享给那些账号(包括有效期), 多个账号用","分开, 
			账号和有效期用";"分开, 如果有效期为"0000-00-00 00:00:00" 表示永久有效,
			例如: "15818757328;2016-10-10 00:00:00,13922589635;0000-00-00 00:00:00",
			一个设备最多能分享给8 个用户;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngGetDevShareAccount( char *account, char *pwd, char *language, 
										 	char *devChannels, char accountWhoIndate[1024], 
										 	char *detail, int detailSize );

/*
* fn: 设置设备的拥有者把该设备分享给哪些用户;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devChannels: 要分享的设备通道, ":" 往前表示设备ID, 往后表示通道号, 多个通道用","区分,
			   例如 "AAAABBBB-ABCD-1234-ABCD-123456789001:2,AAAABBBB-ABCD-1234-ABCD-123456789002:1",
* accountWhoIndate: 把该设备分享给那些账号(包括有效期), 多个账号用","分开, 
			账号和有效期用";"分开, 如果有效期为"0000-00-00 00:00:00" 表示永久有效,
			例如: "15818757328;2016-10-10 00:00:00,13922589635;0000-00-00 00:00:00",
			一个设备最多能分享给8 个用户;
* detail: out, 错误信息, 如果同时修改多个通道, 则在detail 中返回错误号;
* detailSize: detail 指向空间的长度;
* 使用说明: 分享时, 本接口支持单设备通道单用户操作, 也支持多设备通道多用户操作,
            使用时根据实际情况填充参数即可;
*/
HWSDK_API int HwsdkMngSetDevShareAccount( char *account, char *pwd, char *language, 
											char *devChannels, char accountWhoIndate[1024],
											char *detail, int detailSize );
											
/*
* fn: 取消设备分享;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devChannels: 要查询的设备通道, 格式为"AAAABBBB-ABCD-1234-ABCD-123456789001:2",
				":" 往前表示设备ID, 往后表示通道号;
* accountWho: 对哪些账号取消分享, 多个账号用","分开, 			
			例如: "15818757328,13922589635", 一个设备最多能分享给8 个用户;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* 使用说明: 取消设备分享时, 本接口支持单个设备通道单用户用户操作, 也支持多设备通道多用户操作,
            使用时根据实际情况填充参数即可;
*/
HWSDK_API int HwsdkMngDelDevShareAccount( char *account, char *pwd, char *language, 
											char *devChannels, char accountWho[1024], 
											char *detail, int detailSize );

/* 
* fn: 取消被分享设备分享;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devChannels: 要查询的设备通道, 格式为"AAAABBBB-ABCD-1234-ABCD-123456789001:2",
				":" 往前表示设备ID, 往后表示通道号;
	多个通道以','隔开, 例如:"AAAABBBB-ABCD-1234-ABCD-123456789001:2,AAAABBBB-ABCD-1234-ABCD-123456789001:0";
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* 使用说明: 取消设备分享时, 本接口支持单个设备通道单用户用户操作, 也支持多设备通道多用户操作,
            使用时根据实际情况填充参数即可;
*/
HWSDK_API int HwsdkMngDelBeshareDevs( char *account, char *pwd, char *language, 
									char *devChannels, char *detail, int detailSize );


/*  
* fn: 用户登陆;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* oemId：针对OEM客户的客户编码，在定制软件时事先设置, 如"oem8001";
* oemBrand：OEM品牌名称，在定制软件时事先设置；如 "nobrand"为中性;
* pLoginRes: out, 借助登陆接口, 返回一些简单的用户信息;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 0, 登陆成功; 否则登陆失败, 失败信息在detail 返回;
*/
HWSDK_API int HwsdkMngLogin( char *account, char *pwd, char *language,
							char *oemId, char *oemBrand, LOGIN_RES_T *pLoginRes, 
							char *detail, int detailSize );

/* 
* fn: 添加设备;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* nodeName: 设备所在的节点名称, 如果添加到父节点, 该变量为 NULL;
* devIds: 设备ID（序列号），每台设备的唯一识别码，可以同时提交多个，每个ID之间使用半角逗号分隔;
			如: "ABCD-HUAWU-123,ABCD-HUAWU-125";
* groupName: 分组名字, 用于在添加设备时指定分组;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 如果所有ID 都添加成功, 则返回成功(0); 否则返回失败的ID 和该ID 对应的失败信息;
	如果有多个设备添加失败, 则用分号隔开, 例如:
	123456789000:The device ID has been used by other user.;999000999000:The device ID has been used by other user.;
*/
HWSDK_API int HwsdkMngAddDev( char *account, char *pwd, char *language, char *nodeName,
								char *devIds, char *groupName, char *detail, int detailSize );

/* 
* fn: 修改通道;
* account: 账号，可为手机号、邮箱;
* pwd：用户密码;        
* language：用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devId：设备ID(序列号), 如果多个设备ID,使用逗号隔开,比如"AAAABBBB-ABCD-1234-ABCD-123456789002,
		AAAABBBB-ABCD-1234-ABCD-123456789003,AAAABBBB-ABCD-1234-ABCD-123456789007,AAAABBBB-ABCD-1234-ABCD-123456789008",
		逗号之间的设备ID 是独立的, 可以相同;      
* channels: 多个通道的时候需要使用逗号隔开,比如"0,1,2,3";
* chnType: 见HW_CHN_TYPE_EN, 需要格式化成字符串, 多个通道的时候需要使用逗号隔开,比如"0,0,2,1",
			他的值取决于获取设备列表的返回值中的通道结构体, 比如如果该通道是属于 WEBS_DEV_INFO_T 
			下的CAMERA_ATTR_T(目前只有这个,以后增加设备类型后会扩展) 属性, 那么 chnType == CHN_TYPE_CAMERA;
* channelNames: 要修改的通道名字, dev_ch有多少个逗号, 他就有多少个逗号, 而且需要使用UTF-8 编码(三个字节表示一个中文);
	// 比如: 大门口,仓库货架,pingyin,后门 则
	// %E5%A4%A7%E9%97%A8%E5%8F%A3,%E4%BB%93%E5%BA%93%E8%B4%A7%E6%9E%B6,pingyin,%E5%90%8E%E9%97%A8
* group: 组名, 添加分组后组的名称, 把本相机添加到该组下, 比如"group_a1,group_a2,group_a1,group_0";
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;	  
* return: 如果所有通道修改成功, 则返回成功(0); 否则返回失败的ID;
	如果有多个通道修改失败, 则用分号隔开, 例如:0:失败原因,可以为空;1:失败原因,可以为空;
* +++使用特别说明: 
	1. 通道序号从0开始;
	2. 设备ID(非空), 设备通道(非空)、通道名称(允许为空)、分组名称(允许为空), 必须一一对应;
  举例: devId: "AAAABBBB-ABCD-1234-ABCD-123456789002,
				AAAABBBB-ABCD-1234-ABCD-123456789003,
				AAAABBBB-ABCD-1234-ABCD-123456789007,
				AAAABBBB-ABCD-1234-ABCD-123456789008";
		channels: "0,1,2,3"; 
		chnType: "0,0,1,2"
		channelNames:"A,B,C,D"; 
		group:"G1,G2,,GN"; 
  表示:
  1. 设备AAAABBBB-ABCD-1234-ABCD-123456789002 通道1 视频通道 名称为 A, 被分到G1 组;
  2. 设备AAAABBBB-ABCD-1234-ABCD-123456789003 通道2 视频通道 名称为 B, 被分到G2 组;
  3. 设备AAAABBBB-ABCD-1234-ABCD-123456789007 通道3 开关通道 名称为 C, 被分到默认组;
  4. 设备AAAABBBB-ABCD-1234-ABCD-123456789008 通道4 数字通道 名称为 D, 被分到GN 组;
* detail: out, 错误信息, 如果同时修改多个通道, 则在detail 中返回错误号;
* detailSize: detail 指向空间的长度
*/
HWSDK_API int HwsdkMngModifyChn( char *account, char *pwd, char *language,
						char *devId, char *channels, char *chnType, char *channelNames, 
						char *group, char *detail, int detailSize );

/* 
* fn: 删除设备;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devId：设备ID, 删除设备只能一个一个删除;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngDelDev( char *account, char *pwd, char *language, char *devId, 
										char *detail, int detailSize );

/* 特别注意: 节点的概念作用于对相机分组
* fn: 添加节点;
* account: 账号，可为手机号、邮箱;
* pwd: 密码; 
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* nodeName：节点名称;
* parentNodeName: 父节点名称, 如果为NULL, 表示根节点;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/						
HWSDK_API int HwsdkMngAddNode( char *account, char *pwd, char *language, char *nodeName, 
								char *parentNodeName, char *detail, int detailSize );

/* 
* fn: 修改节点;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* nodeName：节点名称;
* parentNodeName: 父节点名称, 如果为NULL, 表示根节点;
* nodeIndex: 该节点的全局唯一索引;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/						
HWSDK_API int HwsdkMngModifyNode( char *account, char *pwd, char *language, char *nodeName, 
						char *parentNodeName, unsigned int nodeIndex, 
						char *detail, int detailSize );

/* 
* fn: 删除节点;
* account: 账号，可为手机号、邮箱;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* nodeName：节点名称;
* parentNodeName: 父节点名称, 如果为NULL, 表示根节点;
* nodeIndex: 该节点的全局唯一索引;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngDelNode( char *account, char *pwd, char *language, char *nodeName, 
				 		char *parentNodeName, unsigned int nodeIndex, 
				 		char *detail, int detailSize );

/* 
* fn: 查询设备信息;
* account: 账号，可为手机号、邮箱;;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devId：设备ID(序列号);
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 从服务器获取到的设备的信息, 如果为NULL, 则获取失败或者设备不可用,
	详细失败信息在 detail 返回;
* 特别注意: 返回的结果必须使用HwsdkMngReleaseDevInfo() 释放, 否则可能会造成内存泄漏;
*/
HWSDK_API WEBS_DEV_INFO_T *HwsdkMngGetDevInfo( char *account, char *pwd, char *language, char *devId, 
													char *detail, int detailSize );

/* 
* fn: 释放HwsdkMngGetDevInfo() 的返回值;
*/
HWSDK_API void HwsdkMngReleaseDevInfo( WEBS_DEV_INFO_T *pDevInfo );

/* 
* fn: 获取设备列表;
* account: 账号，可为手机号、邮箱;;
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 从服务器获取到的设备的信息, 如果为NULL, 则获取失败或者设备不可用,
	详细失败信息在 detail 返回;
* 注意: 返回的值必须使用 HwsdkMngReleaseDevList 释放;
*/
HWSDK_API WEBS_DEV_LIST_T *HwsdkMngGetDevList( char *account, char *pwd, char *language,
												char *detail, int detailSize );
/* 
* fn: 释放HwsdkMngGetDevList() 的返回值;
*/
HWSDK_API void HwsdkMngReleaseDevList( WEBS_DEV_LIST_T *pDevList );

/*
* fn:  获取客户端配置信息;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* user_lang %s：用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* oemId：针对OEM客户的客户编码，在定制软件时事先设置, 如"oem8001";
* oemBrand：OEM品牌名称，在定制软件时事先设置；如 "nobrand"为中性;
* appOs: app 的所在的操作系统, "android" or "ios" or "windows", 不能为空;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 从服务器获取到的设备的信息, 如果为NULL, 则获取失败或者设备不可用,
	详细失败信息在 detail 返回;
* 注意: 该接口的返回值必须使用 HwsdkMngReleaseClientInfo() 释放;
*/
HWSDK_API WEBS_CLIENT_INFO_T *HwsdkMngGetClientInfo( char *language, char *oemId, char *oemBrand,
													char *appOs, char *detail, int detailSize );

/*
* fn: 释放HwsdkMngGetClientInfo() 的返回值;
*/
HWSDK_API void HwsdkMngReleaseClientInfo( WEBS_CLIENT_INFO_T *pClientInfo );

/* 
* fn: 获取消息推送策略;
* account: 账号，可为手机号、邮箱
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* timezone: 时区, [-12, +11];
* pntq: out, 消息推送时间段(Push Notification time quantum), 取值范围见 HW_PNTQ_EN;
* dayScheme: out, 当pntq = PNTQ_DAY时生效, 白天策略的时间段选项,每个字节表示半小时,48 = 24小时 X 2;
	使用十六进制表示, 例如 dayScheme[0] == 0x1, 则表示00:00:00~00:30:00 生效, 否则不生效, 其他时间段类推;
* nightScheme: out, 当pntq = PNTQ_NIGHT时生效, 晚上策略的时间段选项,每个字节表示半小时,48 = 24小时 X 2;
  	使用十六进制表示, 例如 nightScheme[0] == 0x1, 则表示00:00:00~00:30:00 生效, 否则不生效, 其他时间段类推;
  注意白天和晚上的时间段设置完全独立.
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngGetPushNotificationScheme( char *account, char *pwd, char *language, float timezone,
											int *pntq, char dayScheme[48], char nightScheme[48],
											char *detail, int detailSize );

/*
* fn: 设置消息推送策略;
* account: 账号，可为手机号、邮箱
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* pntq: 消息推送时间段(Push Notification time quantum), 取值范围见 HW_PNTQ_EN;
* dayScheme: 当pntq = PNTQ_DAY时生效, 白天策略的时间段选项,每个字节表示半小时,48 = 24小时 X 2;
	使用十六进制表示, 例如 dayScheme[0] == 0x1, 则表示00:00:00~00:30:00 生效, 否则不生效, 其他时间段类推;
* nightScheme: 当pntq = PNTQ_NIGHT时生效, 晚上策略的时间段选项,每个字节表示半小时,48 = 24小时 X 2;
  	使用十六进制表示, 例如 nightScheme[0] == 0x1, 则表示00:00:00~00:30:00 生效, 否则不生效, 其他时间段类推;
  注意白天和晚上的时间段设置完全独立.
* timezone: 时区, [-12, +11];
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngSetPushNotificationScheme( char *account, char *pwd, char *language,
											int pntq, char dayScheme[48], char nightScheme[48],
											float timezone, char *detail, int detailSize );

/*
* fn: 修改用户信息
* account: 账号，可为手机号、邮箱
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* nickname：昵称;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngModifyUsrInfo( char *account, char *pwd, char *language, char *nickname, 
			  							char *detail, int detailSize );

/*
* fn: 获取头像图片
* account: 账号，可为手机号、邮箱
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* headPic：out, head picture, 头像图片, 暂定为JPG 格式;
* headPicSize: in, headPic 指向空间的大小; out, 头像图片的大小
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngGetHeadPic( char *account, char *pwd, char *language, 
									char *headPic, int *headPicSize,
				  					char *detail, int detailSize );

/*
* fn: 修改头像图片
* account: 账号，可为手机号、邮箱
* pwd: 密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* headPic：head picture, 头像图片, 暂定为JPG 格式;
* headPicSize: 头像图片的大小
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngModifyHeadPic( char *account, char *pwd, char *language, 
								char *headPic, int headPicSize,
			  					char *detail, int detailSize );

/*
* fn: 获取所有通道的新消息的数量;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* timezone: 时区, [-12, +11];
* days: 本地保存的天数;
* recType: 记录类型, 参见HW_REC_TYPE_EN;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 所有通道未读的消息条数, 以及最新消息图片的名字(如果存在);
*/
HWSDK_API ALL_NEW_MSG_SIZE_T *HwsdkMngGetHistoryAlarmSize( char *account, char *pwd, char *language, 										
											float timezone, int days, int recType, char *detail, int detailSize );

/* 
* fn: 释放 HwsdkMngGetHistoryAlarmSize() 返回的链表;
* ptr: 接口 HwsdkMngGetHistoryAlarmSize() 的返回值;
*/														
HWSDK_API void HwsdkMngFreetHistoryAlarmSizeResult( ALL_NEW_MSG_SIZE_T *ptr );	

/*
* fn: 获取所有通道的新消息的数量;
	HwsdkMngGetHistoryAlarmSizeEx() 和HwsdkMngGetHistoryAlarmSize() 的区别是
	1. HwsdkMngGetHistoryAlarmSizeEx(): 返回的结果没有日期的概念;
	2. HwsdkMngGetHistoryAlarmSize():返回的结果有区分今天、昨天、前天、三天前;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* timezone: 时区, [-12, +11];
* days: 本地保存的天数;
* recType: 记录类型, 参见HW_REC_TYPE_EN;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 所有通道未读的消息条数, 以及最新消息图片的名字(如果存在);
*/
HWSDK_API ANYDAY_NEW_MSG_SIZE_T *HwsdkMngGetHistoryAlarmSizeEx( char *account, char *pwd, char *language, 										
										float timezone, int days, int recType, char *detail, int detailSize );
/* 
* fn: 释放HwsdkMngGetHistoryAlarmSizeEx() 返回的链表;
* ptr: 接口HwsdkMngGetHistoryAlarmSizeEx() 的返回值;
*/														
HWSDK_API void HwsdkMngFreetHistoryAlarmSizeResultEx( ANYDAY_NEW_MSG_SIZE_T *ptr );


/*
* fn: 查询历史报警消息, 根据用户的操作, 分为按时间段查询、向上拉查询、向下拉查询;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devId: 设备ID(序列号);
* chnType: 通道类型, 见HW_CHN_TYPE_EN, 它的值应该与HwsdkMngGetHistoryAlarmSize() 返回值中的
			anyDay->chnType 一致;
* chn: 通道号, 该参数和chnType 配合使用, 表示不同通道类型的通道号;
* tsBegin: 开始时间, 格式为 "2016-01-02 00:30:22", 当AA_TIME == appAction, 时有效;
* tsEnd: 结束时间, 格式为 "2016-01-02 00:30:22", 当AA_TIME == appAction, 时有效;
* timezone: 时区, [-12, +11], 当AA_TIME == appAction, 时有效;
* appAction: 根据用户的操作, 取值范围见 APP_ACTION_EN;
* msgIndex: 对应 ALARM_MSG_T 里面的 msgIndex, 它和appAction配合使用, 表示从某条消息开始查找;
* days: 本地保存的天数;
* recType: 记录类型, 参见HW_REC_TYPE_EN;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 历史报警消息链表, 该链表需要使用HwsdkMngReleaseHistoryAlarmMsgResult() 释放;
* 注意: 每次最多返回500 条;
*/
HWSDK_API ALARM_MSG_T *HwsdkMngGetHistoryAlarmMsg( char *user, char *pwd, char *language, 
													char *devId, unsigned char chnType, int chn,
													char tsBegin[20], char tsEnd[20],float timezone,
													unsigned char appAction, unsigned int msgIndex, 
													int days, int recType, char *detail, int detailSize );										
/*
* fn: 释放HwsdkMngGetHistoryAlarmMsg() 返回的链表;
* ptr: 接口HwsdkMngGetHistoryAlarmMsg() 的返回值;
*/														
HWSDK_API void HwsdkMngReleaseHistoryAlarmMsgResult( ALARM_MSG_T *ptr );
HWSDK_API void HwsdkDoorBellsRelease( DOOR_BELL_T *ptr ); //door bells


/*
* fn: 查询历史报警消息, 根据用户的操作, 分为按时间段查询、向上拉查询、向下拉查询;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devId: 设备ID(序列号);
* chnType: 通道类型, 见HW_CHN_TYPE_EN, 它的值应该与HwsdkMngGetHistoryAlarmSizeEx() 返回值中的
			anyDay->chnType 一致;
* chn: 通道号, 该参数和chnType 配合使用, 表示不同通道类型的通道号;
* ts: 某天的日期时间, 格式为 "2016-01-02 00:30:22", 当AA_TIME == appAction, 时有效;
* timezone: 时区, [-12, +11], 当AA_TIME == appAction, 时有效;
* appAction: 根据用户的操作, 取值范围见 APP_ACTION_EN;
* msgIndex: 对应 ALARM_MSG_T 里面的 msgIndex, 它和appAction配合使用, 表示从某条消息开始查找;
* days: 本地保存的天数;
* recType: 记录类型, 参见HW_REC_TYPE_EN;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 历史报警消息链表, 该链表需要使用 HwsdkMngReleaseHistoryAlarmMsgResultEx() 释放;
* 注意: 每次最多返回500 条;
*/
HWSDK_API ALARM_MSG_T *HwsdkMngGetHistoryAlarmMsgEx( char *user, char *pwd, char *language, 
													char *devId, unsigned char chnType, int chn,
													char ts[20],float timezone,
													unsigned char appAction, unsigned int msgIndex, 
													int days, int recType, char *detail, int detailSize );


/*
this is a funtion about getting door bell from webs
data:12.08
*/

HWSDK_API DOOR_BELL_T *HwsdkMegGetDoorBell( char *user, char *pwd, char *language, 
											char *devId, unsigned char chnType, int chn,
											float timezone,											
											char *detail, int detailSize );


/* 
* fn: 释放HwsdkMngGetHistoryAlarmMsgEx() 返回的链表;
* ptr: 接口HwsdkMngGetHistoryAlarmMsgEx() 的返回值;
*/
HWSDK_API void HwsdkMngReleaseHistoryAlarmMsgResultEx( ALARM_MSG_T *ptr );

/* 
* fn: 添加分组;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* groupName: 组的名字;
* groupNum: 等于目前最大组数加1, 取值范围[1,10]. 不管目前有多少个组, 填10 都表示添加到最后;
* groupIndex: out, 所添加数组的全局唯一的index;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngAddGroup( char *account, char *pwd, char *language, 
								char groupName[48], int groupNum,
								unsigned int *groupIndex, char *detail, int detailSize );

/* 
* fn: 修改分组;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* groupName: 组的名字, 可修改;
* groupIndex: 组的全局唯一的index, 不可修改. 它可以从添加组接口或者查询设备列表接口获取;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngModifyGroup( char *account, char *pwd, char *language, 
								char groupName[48], unsigned int groupIndex, 
								char *detail, int detailSize );
/* 
* fn: 删除分组;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* groupName: 组的名字, 可修改;
* groupIndex: 组的全局唯一的index, 不可修改. 它可以从添加组接口或者查询设备列表接口获取;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 历史报警消息链表, 该链表需要使用HwsdkMngFreetHistoryAlarmMsgResult() 释放;
*/
HWSDK_API int HwsdkMngDeleteGroup( char *account, char *pwd, char *language, 
								char groupName[48], unsigned int groupIndex, 
								char *detail, int detailSize );
/*
* fn: 给分组排序;
* account: 账号，可为手机号、邮箱;
* pwd: 要修改的新密码;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* groupIndexs: string, 所有组的index, 用半角逗号","隔开, 例如:"50,59,47,48,52,53,54,55,56,49";
* groupNums: string, 所有组的number, 用半角逗号","隔开, 例如:"1,2,3,4,54,5,6,7,8,9,10";
  注意: groupIndexs 和 groupNums 必须一一对应;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
* return: 历史报警消息链表, 该链表需要使用HwsdkMngFreetHistoryAlarmMsgResult() 释放;
*/
HWSDK_API int HwsdkMngSortGroup( char *account, char *pwd, char *language, 
									char *groupIndexs, char *groupNums,
									char *detail, int detailSize );
/*
* fn: 上报手机信息;
* 1) user_name：拟注册用户名;
* 2) user_pws：用户密码;
* 3) user_lang：用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* 4) latitudeNs: 纬度方向, 等于CD_NORTHERN_LATITUDE 或CD_SOUTH_LATITUDE;
* 5) latitude: 位置纬度，浮点数, 用字符串表示, 例如"25.32456923542";
* 6) longitudeEw: 经度方向,等于CD_WEST_LONGITUDE 或CD_EAST_LONGITUDE;
* 7) longitude: 位置经度，浮点数, 用字符串表示, 例如"25.32456923546";
* 8) alias: 别名，固定使用客户端品牌，如果是中性的，则为nobrand，该别名必须向推送服务器注册(例如小米推送), 可以为NULL;
* 9) regid: 客户端在推送服务器登记的账号，默认使用"C"加客户端索引为识别，例如：C10002, 可以为NULL;
* 10) mobile_brand: 手机品牌，如：SAMSUNG, 可以为NULL;
* 11) mobile_model: 手机型号, 可以为NULL;
* 12) os: 操作系统, 可以为NULL;
* 13) version: 操作系统版本号, 可以为NULL;
* 14) cpu: 处理器信息，如: 1.2GHz 4核, 可以为NULL;
* 15) memory: 存储卡容量, 可以为NULL;
* 16) kernel: 内核版本, 可以为NULL;
* 17) baseband: 基带版本, 可以为NULL;
* 18) timezone: 时区, 可以为NULL;
* 19) clientBrand: 客户端品牌，如果是中性版本，暂定nobrand, 可以为NULL;
* 20) clientVersion: 客户端APP 软件版本, 可以为NULL;
* 21) countryCode: 国家代码，如中国：CN, 可以为NULL;
* 22) countryName: 国家名称，如：China, 可以为NULL;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngReportPhoneInfo( char *user, char *pwd, char *language, char latitudeNs, char *latitude, 
								char longitudeEw, char *longitude, char *alias, char *regid, char *mobileBrand, 
								char *mobileModel, char *os, char *version, char *cpu, char *memory, 								
								char *kernel, char *baseband, 	
								float timezone, char *clientBrand, char *clientVersion, char *countryCode, char *countryName, 
								char *detail, int detailSize );
/*
* fn: 上报设备信息;
* user_name：拟注册用户名;
* user_pws：用户密码;
* user_lang：用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devId: 设备ID;
* latitudeNs: 纬度方向, 等于CD_NORTHERN_LATITUDE 或CD_SOUTH_LATITUDE;
* latitude: 位置纬度，浮点数, 用字符串表示, 例如"25.32456923541";
* longitudeEw: 经度方向,等于CD_WEST_LONGITUDE 或CD_EAST_LONGITUDE;
* longitude: 位置经度，浮点数, 用字符串表示, 例如"25.32456923542";
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngReportDeviceInfo( char *user, char *pwd, char *language, char *devId,
								char latitudeNs, char *latitude, char longitudeEw, char *longitude,
								char *detail, int detailSize );

/*
* fn: 用户反馈;
* user_name：拟注册用户名;
* user_pws：用户密码;
* user_lang：用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* user_email %s: 用户email;
* user_mobile %s: 用户手机号码;
* client_brand %s: 商标, 例如"5-smart";
* client_version %s: 客户端APP 版本号,例如(V1.0.0.1);
* content: 用户上报的内容;
* detail: out, 错误信息
* detailSize: detail 指向空间的长度
*/
HWSDK_API int HwsdkMngUserFeekback( char *user, char *pwd, char *language, char *userEmail,
						char *userMobile, char *clientBrand, char *clientVersion,
						char *content, char *detail, int detailSize );								

/*
* fn: 检查设备ID 是否能用
* user: 用户名
* pwd: 密码 
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写
* devId: 设备ID;
* devCode: out, 设备编码;
* detail: out, 错误信息;
	注意: 当查询的ID 存在, 而且被其他用户占用, 那么在本变量会同时返回占用该ID 的账号信息,
	格式为: "失败信息|dev_user=占用该ID 的账号信息", 例如:
	"The device is used by other user. you can contact your provider. |dev_user=156****5961",
	'|dev_user=' 前面为失败信息, "|dev_user=" 后面为占用的账号信息(如果存在);
* detailSize: detail 指向空间的长度
*/
int HwsdkMngCheckDevId( char *user, char *pwd, char *language,  
					char *devId, char *devCode, char *detail, int detailSize );

/*
* fn: 检查验证码是否可用;
* user: 用户名;
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* identifying_code：需要检查的验证码;
* timezone: 时区;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
HWSDK_API int HwsdkMngCheckCfgCode( char *user, char *language, char *cfgCode, 
				  					float timezone, char *detail, int detailSize );

/*
* fn: 获取设备升级版本信息;
* user: 账号;
* pwd: 密码; 
* language: 用户语言代码，如: zh-cn，en-us等，按照国际标准代码填写;
* devCode: 设备编码, 该入参来自于设备列表结构体的devCode;
* pVersionParam: out, 返回升级软件对应的一些参数信息;
* pRomInfo: out, 升级软体的信息;
* romInfoSize: pRomInfo 指向空间的大小, 建议APP 传8K 的空间进来;
* detail: out, 错误信息;
* detailSize: detail 指向空间的长度;
*/
int HwsdkMngGedDevRomInfo( char *user, char *pwd, char *language, char *devCode, 
					   		HWSDK_DEV_VERSION_PARAM *pVersionParam, char *pRomInfo, 
					   		int romInfoSize, char *detail, int detailSize );

/*
* fn: 请求实时流;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* chnType; 0, 主码流; 1, 子码流;
* context: out( out 表示该参数输出结果,下同 ), 如果请求成功, 则由该参数返回取流的上下文,
			该函数立即返回, 视频流将以回调的方式传给APP;
* return: ==0, 表示请求成功; 否则, 失败. 请求失败, 则延迟20 秒再重新调用本函数;
*/
HWSDK_API int HwsdkDevRealTimeStreamStart( unsigned int devIndex, int channel, unsigned char chnType, unsigned long *context );

/*
* fn: 停止某个通道的实时流;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* chnType; 0, 主码流; 1, 子码流;
* context: 从 HwsdkDevRealTimeStreamStart() 得到的 context;
* 注意: 如果要实现某个通道的断线重连, 则必须使用本接口释放 HwsdkRealTimeStreamStart()
        函数成功后占用的资源;
*/
HWSDK_API int HwsdkDevRealTimeStreamStop( unsigned int devIndex, int channel, unsigned char chnType, 
													unsigned long *context );

/*
* fn: 请求音频流指令;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 请求该设备那个通道的流;
 */
HWSDK_API int HwsdkDevAudioStart( unsigned int devIndex, int channel );

/*
* fn: 停止音频流指令;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 请求该设备那个通道的流;
*/
HWSDK_API int HwsdkDevAudioStop( unsigned int devIndex, int channel );

/*
* fn: 搜索某个通道的录像文件;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* date[20]: 录像日期,按天来检索, 时间格式"2016-03-28";
* type: 录像类型,用来支持搜索报警、事件录像;
* searchNum: 搜索量, 1按天搜索返回,2按月搜索返回;
* searchChnType: 搜索回放的清晰度,0高清,1标清;
* context: out, 上下文, 回放时, 将以该上下文做标识回调录像给APP;
* 注意: 搜索录像的结果以回调的方式返回, 参考 HW_SEARCH_RECORD_RES_CB;
*/
HWSDK_API int HwsdkDevSearchRecord( unsigned int devIndex, int channel, char date[20],
                                    unsigned char type, unsigned char searchNum, unsigned char searchChnType, unsigned long *context );

/*
* fn: 释放 HwsdkDevSearchRecord() 获取到的资源;
	1. 告诉设备我不再关心该相机的回放数据了;
	2. 释放该相机回放的本地资源;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* chnType: 回放的清晰度,0 高清,1 标清,同回放控制请求的chnType保持一致;
*/
HWSDK_API int HwsdkDevReleaseSearchRecord( unsigned int devIndex, int channel, unsigned char chnType );

/*
* fn: 回放控制;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* cmd: 回放命令，参见 REPLAY_CMD_EN;
* param: 回放参数:
    1. 如果cmd 是RC_SPEED, 则此参数表示速度，参见REPLAY_CMD_EN;
    2. 如果命令是RC_FILE, 此参数表示从当前时间段的第几分钟进行回放, 
       取值范围与 REPLAY_START_CB 回调的参数howManyFile返回的值相关;
    3. 如果cmd 是其它值，该参数无效;
* dt: 时间控制: 
    1. 如果cmd 是RC_FILE, 格式"2016-03-30 18:30:00",当cmd 是RC_FILE 时, 表示把回放时间;
        切换到该时间目前精确到分钟, 也就是最后一个冒号后面的秒数为00;
    2. 如果cmd 是其它值，该参数无效;
* chnType: 回放清晰度，0高清， 1标清;
* playbackCnt: 每请求一次回放或切换回放文件加1, 用于防止切换回放文件时收到上次回放的数据,范围[1,127];
* return: 该函数立即返回, 回放的流将以回调的方式传给APP, 回调里是小包数据，需要在回调函数里组成视频侦;
*/
HWSDK_API int HwsdkDevPlaybackCtlChntype( unsigned int devIndex, int channel, int cmd, int param, char dt[20], char chnType, unsigned char playbackCnt );

/*
* fn: 客户端往设备端发送语音流;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 一般就只有1 个mic, 填0 即可;
* pAudioData: 由手机或者电脑采集编码后的音频数据, 裸流;
* len: 音频裸流数据长度;
* encType: 编码类型: 100, g711a; 101, g711u, 默认100;
* sampleRate: 采样率: 0, 8000; 1, 16000, 默认0;
* bitWidth: 位宽: 0, 8bit; 1, 16bit, 默认1, 目前海思的芯片只支持16bit;
* chnMod: 通道模式: 0, 单通道(Mone); 1, 立体声, 默认0;
 */
HWSDK_API int HwsdkDevTalkBackCuToDu( unsigned int devIndex, int channel, char *pAudioData, int len,
										unsigned char encType, unsigned char sampleRate, 
										unsigned char bitWidth, unsigned char chnMod );

/*
* fn: 获取设备状态;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* model[32]: out, 设备型号;
* id[52]: out, 最长支持48 个字节的的ID;
* devType[16]:out, 设备类型 "nvr/ipc/dvr";
* version[16]: out, 版本号,如"v1.23";
* vch: out, 视频通道数;
* ach: out, 音频通道数;
* kin: out, 输入开关量数量;
* kout: out, 输出开关量数量;
* vencStandard[16]: out, 当前视频编码标准, 如"jpeg/fmpeg4/h.264/h.265";
* aencStardard[16]: out, 当前音频编码标准, 如"AAC/g711a/g711u/g726/mp3";
* allResolution[84]: out, 设备所支持的所有分辨率, 用半角分号区分开来: "1920X1080;1080X720;640X360;704X576";
* diskNum: out, 总共有多少个磁盘, 最多支持8 个;
* diskAttr[8]: out, 每个硬盘的信息数组;
* pNetInfo:  out, 网络信息; 
*/
HWSDK_API int HwsdkDevStatus( unsigned int devIndex, char model[32], char id[52], char devType[16], char version[16],
                                 unsigned char *vch, unsigned char *ach, unsigned char *kin, unsigned char *kout,
                                 char vencStandard[16], char aencStardard[16], char allResolution[84], unsigned char *diskNum,
                                 HWSDK_DISK_ATTR_T *diskattr, HWSDK_NET_INFO_T *pNetInfo );

/*
* fn: 获取设备更多参数;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* pMultiConf: out,设备参数的结构指针;
*/
HWSDK_API int HwsdkGetMultiConf( unsigned int devIndex, int channel, HWSDK_GET_MULTI_CONF_T *pMultiConf );

/*
* fn: 云台控制, 通道相关;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* type: 控制类型，取值见PTZ_CTRL_E;
* motion: 暂时保留;
* param: 控制参数, 可以为:
			1. 移动速度范围：speed [0,63];
			2. 巡航轨迹范围：Track [1-16]; 
			3. 预置点范围: SelprePoint[1-255].
            4. 预制位：[0, 55];
*/
HWSDK_API int HwsdkDevPtzCtl( unsigned int devIndex, int channel, unsigned char type,
                           			unsigned char motion, unsigned char param );

/*
* fn: 强制插入I帧, 通道相关;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
*/
HWSDK_API int HwsdkDevForceIframe( unsigned int devIndex, int channel );

/*
* fn: 网络效果调整( 清晰度----流畅性，自适应网络 ), 通道相关;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* level: 等级[1,10];
   1-5  对应的主码流：2048kbps、1536kbps、1024kbps、768kbps、512kbps;
   6-10 对应子码流：  512kbps、384kbps、256kbps、128kbps、80kbps;
*/
HWSDK_API int HwsdkDevSelfAdaption( unsigned int devIndex, int channel, unsigned char level );

/*
* fn: 获取设备WIFI 属性;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* user[33]: out, 用户名;
* passwd[65]: out, 密码;
*/
HWSDK_API int HwsdkDevGetWifiAttr( unsigned int devIndex, char user[33], char passwd[65] );

/*
* fn: 设备WIFI 属性设置;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* user[33]: 用户名;
* passwd[65]: 密码;
*/
HWSDK_API int HwsdkDevSetWifiAttr( unsigned int devIndex, char user[33], char passwd[65] );

/*
* fn: 获取移动侦测配置;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* armFlag: out, 0, 撤防(设备不启动移动侦测); 1, 布防(设备启动移动侦测);
* sensitiveLevel: out, 灵敏度, [1,5], 值越大灵敏度越高;
*/
HWSDK_API int HwsdkDevGetMdConf( unsigned int devIndex, int channel, unsigned char *armFlag, unsigned char *sensitiveLevel );

/*
* fn: 设置移动侦测配置;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* armFlag: 0, 撤防(设备不启动移动侦测); 1, 布防(设备启动移动侦测);
* sensitiveLevel: 灵敏度, [1,5], 值越大灵敏度越高;
*/
HWSDK_API int HwsdkDevSetMdConf( unsigned int devIndex, int channel, unsigned char armFlag, unsigned char sensitiveLevel );

/*
* fn: 升级;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
*/
HWSDK_API int HwsdkDevUpdate( unsigned int devIndex );

/*
* fn: 恢复默认参数;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* defaultNetwork: 0, 不用恢复网络参数, 也就是说恢复除了网络参数以外的所有配置; 需要恢复网络参数;
*/
HWSDK_API int HwsdkDevCtlDefaultParam( unsigned int devIndex, unsigned char defaultNetwork );

/*
* fn: 重启;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
*/
HWSDK_API int HwsdkDevReboot( unsigned int devIndex );

/*
* fn: 获取一张图片;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* picType: 要获取的图片类型, 取值范围参见:PIC_TYPE_EN;
* eventType: 
	1) 当PIC_TYPE_REALTIME == picType, 表示表示获取设备当前截取的一张图片, eventType 无效;
	2) 当PIC_TYPE_ALARM = picType, 为报警类型, 对应ALARM_MSG_T 里面的AlmType 参数;
	3) PIC_TYPE_PRESET == picType, 表示表示获取获取某个预置位的图片, eventType 无效;
* chn: 
	1) 当PIC_TYPE_REALTIME == picType, 表示视频的通道号;
	2) 当PIC_TYPE_ALARM = picType, 对应ALARM_MSG_T 里面的chn 参数;
	3) PIC_TYPE_PRESET == picType, 表示预置位所在的视频通道号;
* context: 上下文,
	1) 当PIC_TYPE_REALTIME == picType, 该参数没意义;
	2) 当PIC_TYPE_ALARM = picType,对应ALARM_MSG_T 里面的picture 参数;
	3) PIC_TYPE_PRESET == picType, 表示预置位号[1,8], 用字符串表示, 例如:"1"、"2"、"3";
* 注意: 图片将以回调的方式返回;
*/
HWSDK_API int HwsdkDevGetPic( unsigned int devIndex, unsigned int picType, unsigned int eventType, int chn, char context[64] );

/*
 * fn: 一次获取多张图片
 * devIndex: 设备的全局唯一索引, 由web 服务器分配;
 * picParms: 参数数组
 * picNum: picParms 数组的大小
*/
HWSDK_API int HwsdkDevGetBulkPic( unsigned int devIndex, HWSDK_GET_PIC_PARAM_T *picParms, int picNum );

/*  
* fn: smartLink设置IPC;
* devId: 设备ID;
* localAddr: 手机当前wifi 的IP 地址, 格式为"192.168.111.222";
* passwdBuff: 手机端已连接的wifi端密码，不得超过64字节;
*/
HWSDK_API int HwsdkDevSeekWifi( char *devId, char *localAddr,char *ssidBuff,  char *passwdBuff );

/*
* fn: 停止smartlink配置
*/
HWSDK_API int HwsdkDevStopSeekWifi();

/*  
* fn: 设置IPC端的时间, 该接口在HwsdkDevSeekWifi() 的回调函数(参数 pCallback)返回smart link 的结果后使用,
	  如果smart link 成功, 则调用本函数给设备端设置时间, 否则, 不用调用本函数;
* timeZone: 手机当前所在时区;
* timeZoneMin: 时区小数对应的分钟数,如:时区为8.5,timeZone=8,timeZoneMin=30;
* utcDate: utc时间，格式为 "2016-10-01 22:00:11";
* devIP: 设备端ip地址, 该值从HwsdkSeekWifi() 的回调函数(参数 pCallback)中返回;
* 返回值: 设置结果返回函数, 成功为0，失败为-1;
*/
HWSDK_API int HwsdkDevSynDate(int timeZone, unsigned char timeZoneMin, char *utcDate, char *devIP);

/*
fn : 应用层通过该接口给sdk 传递事件
* event: 参见 COM_EVENT_EN;
* param1: 根据event 的不同具有不同的意义;
* param2: 根据event 的不同具有不同的意义;
	event、param1、param2 组合如下:
   	event  						| param1                |  param2
    1(APP进入后台休眠)    		| 无意义       			|  无意义  
    2(APP从后台休眠返回)		| 无意义				|  无意义
    3(APP的网络状态发生变化)	| 当前上外网的IP 地址	|  无意义

* 使用说明: 
	(1) 当event == 3 时, param1 为手机当前上外网的IP 地址, 而且是本地套接字的unsigned int 格式,
	比如: 如果当前使用IP 是 "192.168.99.91", 则param1 为0xC0A8635B;	
*/
int HwsdkEventFromAppToSdk( unsigned int event, unsigned int param1, unsigned int param2 );

/*
* fn: 获取录像配置;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* isOnlyAlarmRec: out, 是否只录制报警录像;
* isOnlyAlarmRec: out, 录像时是否录制音频;
*/
int HwsdkDevGetRecordConf( unsigned int devIndex, unsigned char *isOnlyAlarmRec, unsigned char *isAudioRec );

/*
* fn: 设置录像配置;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* isOnlyAlarmRec: 是否只录制报警录像;
* isAudioRec: 录像时是否录制音频;
*/
HWSDK_API int HwsdkDevSetRecordConf( unsigned int devIndex, unsigned char isOnlyAlarmRec, unsigned char isAudioRec );

/*
* fn: 格式化磁盘;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
*/
HWSDK_API int HwsdkDevFormatDisk( unsigned int devIndex );

/*
* fn: 获取设备端wifi列表
*     返回列表在回调函数 pGetWifilistFunc 里
*/
HWSDK_API int HwsdkDevGetWifilist( unsigned int devIndex );

/*
* fn: 设置画面翻转
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* rotate: 0, 不翻转; 1, 180度翻转; ... 见 HW_ROTATE_EN;
*/
HWSDK_API int HwsdkDevSetRotate( unsigned int devIndex, int channel, unsigned char rotate );

/*
* fn: 设置电源频率
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* pwrFreq: 设备电源频率, 一般来说只有50Hz 和60Hz这两种选择;
*/
HWSDK_API int HwsdkDevSetPwrFreq( unsigned int devIndex, unsigned short pwrFreq );

/*
* fn: 设备登录,主要用于根据报警消息连接到设备,获取报警图片;
* devIndex: 设备自己的index, 全局唯一的索引;
* ip: 设备端IP;
* p2pIp: P2P 服务器的IP 地址;
* p2pPort: P2P 服务器的IP 端口;
* tssIp: 转发服务器IP 地址;
* tssPort: 转发服务器端口;
* return: 0,返回正常;其他,错误;
*/
HWSDK_API int HwsdkOpenDev( unsigned int devIndex, char *ip, char *p2pIp, unsigned short p2pPort,
    char *tssIp, unsigned short tssPort );

/*
* fn: 根据设备ID组播查找设备端,设备端匹配成功后返回,用户可直接添加设备;
*     主要的使用场景是:
*        设备端使用有线连接的方式连接到网络（没有或未使用wifi,目的和smarLink相同）;
*     注意：接口最大阻塞时间是3s，需保证设备端和客户端在同一网段,否则可能无法发现设备
* devId: 设备ID;
* tz:    客户端时区
* tzMin: 时区小数对应的分钟数,如:时区为8.5,tz=8,tzMin=30;
* time:  客户端时间
* retrun: 0,成功;-1,未知错误;其他,参照HW_CERROR_TYPE_EN;
*/
HWSDK_API int HwsdkMulticastFindDev( char *devId, int tz, unsigned char tzMin, unsigned int time );

/*
* fn: 启用动态码率;
* 流程: 如果客户端每3S丢失超过[7,10]帧时请求降低码率,此时如果如果有多个客户端播放同一个设备通道的视频;
*      逐一降低码率档位,反之请求2分减半码率档位（如从10档调整为5档,7档调整为4档）,调整码率后状态保持稳定一段时间,修改状态改为稳定;
*      稳定状态维持较长时间（20S以上）后,尝试提高码率,每次提高一档;循环这个过程;
*/
HWSDK_API void HwsdkStartVarBitrate();

/*
* fn: 关闭动态码率;
*/
HWSDK_API void HwsdkStopVarBitrate();

/*
* fn: 获取迅美设备模式参数,最长阻塞5S;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* xmInsMode: out, 参数值见 HWSDK_XM_INS_MODE_E;
* xmFisheyeMode: out, 鱼眼模式, 参数值见 HWSDK_XM_FISHEYE_MODE_E;
*/
HWSDK_API int HwsdkDevGetXMSetting( unsigned int devIndex, int channel, unsigned char *xmInsMode, unsigned char *xmFisheyeMode );

/*
* fn: 设置迅美设备模式参数,最长阻塞3S;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
* channel: 通道号,[0,设备支持的通道数);
* xmInsMode: 参数值见 HWSDK_XM_INS_MODE_E;
* xmFisheyeMode: 鱼眼模式, 参数值见 HWSDK_XM_FISHEYE_MODE_E;
*/
HWSDK_API int HwsdkDevSetXMSetting( unsigned int devIndex, int channel, unsigned char xmInsMode, unsigned char xmFisheyeMode );

/*
* fn: 生成传输声波的裸流数据,wave 格式;
* wifiSsid: wifi 名字;
* wifiPwd: wifi 密码;
* localAddr: 手机当前wifi 的IP 地址,  格式为"192.168.111.222";
* pBuf: out, 存放生成后的wave 音乐数据;
* bufSize: pBuf 所指向空间的大小，所需分配内存2M;
* resultSize: out, 返回pBuf 中数据的长度;
* platform:  平台的选择，1  海思   2 君正 

* pBufSsid: out, 存放生成后的wave 音乐Ssid数据,所需分配内存1M;
* bufSizeSsid: pBuf 所指向空间的Ssid大小;
* resultSizeSsid: out, 返回pBuf 中数据的Ssid长度;

* 特别说明: 采用声波的方式添加设备, 需要同时使用本接口和 HwsdkMulticastFindDev 接口;
*/
HWSDK_API int HwsdkGenWtoswSoundData( char *wifiSsid, char *wifiPwd, char *localAddr, char *pBuf, int bufSize, int *resultSize ,int platform,char *pBufSsid, int bufSizeSsid, int *resultSizeSsid);

/*
* fn: 获取NVR设备的通道状态信息;
* devIndex: 设备的全局唯一索引, 由web 服务器分配;
*/
HWSDK_API int HwsdkDevGetNVRChannelState( unsigned int devIndex );

/*
* fn: 设置设备音量;
* devIndex: 设备的全局唯一索引,由web 服务器分配;
* volume: 音量,范围[0-100];
* slaveVolume: 从机扬声器音量[0-100];
* micVol: 唛克风音量[0-100];
* slaveMicVol: 从机唛克风音量[0-100];
*/
HWSDK_API int HwsdkDevSetDevVolume( unsigned int devIndex, unsigned char volume, unsigned char slaveVolume, unsigned char micVol, unsigned char slaveMicVol );

/*
* fn: 播放铃声;
* devIndex: 设备唯一标识ID;
* param: 播放参数;
*/
HWSDK_API int HwsdkDevPlayRing( unsigned int devIndex, unsigned char param );

/*
* fn: 通知设备更新铃声;
* devIndex: 设备唯一标识ID;
*/
HWSDK_API int HwsdkDevUpdateRing( unsigned int devIndex );

/*
* fn: 获取设备电量,结果通过事件(CE_DEV_ELECTRICITY)回调返回,设备端也会主动上报设备电量;
* devIndex: 设备唯一标识ID;
*/
HWSDK_API int HwsdkDevGetElectricity( unsigned int devIndex );

/*
* fn: 设置PIR,被动式红外探测功能;
* devIndex: 设备唯一标识ID;
* pirSnap: 感应拍照 0,关闭 1,打开;
*/
HWSDK_API int HwsdkDevSetPIR( unsigned int devIndex, unsigned char pirSnap );

/*
* fn: 唤醒门铃设备;
* devIndex: 设备唯一标识ID;
* retrun: 0,请求成功;非0为异常错误;
*/
HWSDK_API int HwsdkDevWakeupDoorbell(unsigned int devIndex);

/*
* fn: 设置某个模拟开关量的状态;
* devIndex: 设备的index;
* chnKout: 设备的kout 通道, 取值范围[0,8), 目前最多支持8 个通道 ;
* state: 0, 关; 1, 开;
*/
HWSDK_API int HwsdkDevSetSwitchKout( unsigned int devIndex, unsigned char chnKout, char state );

/*
* fn: 获取设备所有模拟开关量的状态, 目前最多支持8, 设备实际有多少个, 需要根据
      设备列表结构体WEBS_DEV_INFO_T 的koutNum 成员;
* devIndex: 设备的index;
* chnKout: 设备的kout 通道, 取值范围[0,8), 目前最多支持8 个通道 ;
* state: 0, 关; 1, 开;
*/
HWSDK_API int HwsdkDevGetSwitchKout( unsigned int devIndex, char koutState[8] );

/*
* fn: 透明传输接口;
* devIndex: 设备的index;
* data: 要透传的数据;
* len: 透明传输的长度, 必须<= 1168;
* 说明: Ut = unvarnished transmission;
*/
HWSDK_API int HwsdkDevUtFromClientToDev( uint devIndex, char *data, int len );

#endif // __HWSDK_H__

