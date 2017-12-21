#include "hwsdk.h"
#include "hwsdkType.h"
#include "test.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#define SIZE_DETAIL 2*1024

using namespace std;
void intital_param(INIT_HWSDK_PARAM_T *param){
	

	sprintf(param->ipAddr,"192.168.1.99");
	sprintf(param->hwpDns,"0");
	param->cliType=CLI_ANDROID_PHONE;
	param->mngIp=0;
	param->mngPort=0;
	#if 0
	param
	param
	param
	param
	param
	param
	param
	param
	param
	param
	param
	param
	#endif
	
	
	
	
}

int main(int argc,char** argv){
	#if 0
	
	std::string user="350817634@qq.com";
	std::string pwd="678630";
	std::string language="zh-cn";
	//std::string dev_id="HW-M11101C-00003199";
	int dev_num=1;
	char* devId;
	//devId_multi[0]="HW-M21102-00000070";
	//devId_multi[1]="HW-M21102-00000077";
	devId="HW-M11101C-00003199";
	std::string channel_type="1";
	int channel_value=0;
	float time_zone=8;
	char detail[SIZE_DETAIL];
	int detail_size=SIZE_DETAIL;
		
	//initial sdk	
	
	HwsdkTestDoorBeel("",0,0);
	

	DOOR_BELL_T* return_door_bell_msg=HwsdkMegGetDoorBell((char*)user.c_str(), (char*)pwd.c_str(), (char*)language.c_str(), 
															devId,(const char)(*channel_type.c_str()), channel_value,
															time_zone, detail, detail_size);
	
	cout<<"return:"<<detail<<endl;
	cout<<"alms_time: "<<return_door_bell_msg->tsUtc<<endl;
	cout<<"srvTime:"<<return_door_bell_msg->srvTime<<endl;
	//cout<<"detail:"<<return_door_bell_msg->detail<<endl;
	cout<<"delete door bells====================!"<<endl;
	HwsdkDoorBellsRelease(return_door_bell_msg); //delete 
	
	#else
		
	cout<<"initial sdk"<<endl;
	//TestProcon();
	//P2pcInit();
	INIT_HWSDK_PARAM_T *param;
	intital_param(param);
	HwsdkInit(param);
		
	unsigned long *context;
	int ret=HwsdkDevRealTimeStreamStop(45242,0,'0',context);
	cout<<"context:"<<context<<endl;
	cout<<"ret->:"<<ret<<endl;
	
	#endif		
	return 0;

}