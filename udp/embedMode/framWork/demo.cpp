//video online data:11.9 by gong

//#include "./json/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdint.h>
//#include "./param/paramConfig.h"
#include "./include/cJSON.h"
//commond package
#define start_vf_preview 	0x4
#define stop_vf_preview 	0x5
#define start_vf_record		0x17
#define stop_vf_record		0x18
#define	start_vf_photo		0x6
#define stop_vf_photo		0x7
#define MAX_MSG 10

char gfile_name[50]="json.json";

using namespace std;
struct reci_msg{
	//old parameter
	short flag; //0->old,1->business
	int index[MAX_MSG];
	void* data[MAX_MSG];
	//add business 
	char cmd[20];  //inlude video,record and photo
	void* handle_para;  //reserve 
		
};


struct TrecordStaMsgBack{
	char* cmd;
	int time_sec;
	int time_usec;
		
};

struct TrecordStopMsgBack{
	
	char* cmd;
	char* file_name;
	
};

int paramHandle(struct reci_msg request){
	
	for(int i=0;i<MAX_MSG;i++){
		
		int result; 
		//result=SetParamConfig(request.index[i], request.data[i],sizeof(request.data[i]),0 );   //lib at t20demo
		if(result!=0){
			cout<<"error:SetParamConfig!"<<endl;
			return -1;
		}else{return 0;}
		
	}	
}

//deal with video
/*int readConf(const char* file_name,const char* obj,const char* child_obj ,char* back){
		
	Json::Reader reader;
	Json::Value values;
	std::ifstream file_stream;
	file_stream.open(file_name,std::ios::binary);
	if(reader.parse(file_stream,values)){
				
		//url_=values["rtmp_url"].asString();
		if(!values[obj].isNull()){
			
			Json::Value data=values[obj];
			if(!data[child_obj].isNull()){
				const char* tem=data[child_obj].asCString();
				memcpy(back,tem,100);
				return 0;
				
			}else{
				cout<<"error:json data"<<endl;
				return -1;
			}
			
		}else{
			cout<<"error:json obj"<<endl;
			return -1;
			
		}		
			
	}else{
		cout<<"error:reader.parse"<<endl;
		return -1;				
	}
		
}
*/

int readConf(const char* file_name,const char* obj,const char* child_obj ,char* back){
	
	cout<<"readCond"<<endl;
	FILE *fp=fopen(file_name,"r");
	fseek(fp,0,SEEK_END);
	long len=ftell(fp);
	fseek(fp,0,SEEK_SET);
	
	char* data=(char*)malloc(len+1);
	fread(data,1,len,fp);
	fclose(fp);
	//printf("file::%s",data);
	
	//parse json
	cJSON *root_json = cJSON_Parse(data);
	if (NULL == root_json)
    {
        printf("error:%s\n", cJSON_GetErrorPtr());
        cJSON_Delete(root_json);
        return -1;
    }
	cJSON *data_json = cJSON_GetObjectItem(root_json, obj);
	char* tem=cJSON_Print(cJSON_GetObjectItem(data_json, child_obj));
	strcpy(back,tem);
	free(data);	
	return 0;
}


int pullVideo(char *url){
	
	cout<<"pullVideo url:"<<url<<endl;
	//.....other..
	
}

int stopVideo(){
	
	cout<<"stopVideo"<<endl;
	//..stop;
	
}
int busiVidHandleStart(){
	
	cout<<"busiVidHandleStart"<<endl;
	
	char rtmp_url[100]="rtmp_url";
	char ip[100]="ip";
	char ip_val[200];
	char sn[100]="sn";
	char sn_val[100];
	char url[200];
	
	readConf(gfile_name,rtmp_url,ip,ip_val);
	readConf(gfile_name,rtmp_url,sn,sn_val);
	printf("ip_val:%s\n",ip_val);
	strcpy(url,"rtmp://");
	strcat(url,ip_val);
	strcat(url,":1935/live/");
	strcat(url,sn_val);
	
	pullVideo(url);	
}

int busiVidHandleStop(){
	
	cout<<"busiVidHandleStop"<<endl;
	int stopVideo();
	
}

//record video
int RecordStartCallBack(struct timeval &tv){
	
	cout<<"RecordCallBack"<<endl;
	cout<<tv.tv_sec<<"::"<<tv.tv_usec<<endl;
	return 0;
	
}

int busiRecordHandleStart(){
	
	cout<<"busiRecordHandleStart"<<endl;
	cout<<"sndmsg 127.0.0.1 2"<<endl;   //##开始录制回调成
	struct timeval tv;
	gettimeofday(&tv,NULL);
	RecordStartCallBack(tv);	
	return 0;
	
}

int RecordStopCallBack(char* file){
	
	cout<<"RecordStopCallBack"<<endl;
	cout<<"file_name:"<<file<<endl;
	return 0;
	
}

int busiRecordHandleStop(){
	
	cout<<"busiRecordHandleStop"<<endl;
	cout<<"sndmsg 127.0.0.1 1"<<endl;
	char file_name_back[200];
	char record[100]="record";
	char file_name[100]="filename";
	char file_name_val[100];
	if(readConf(gfile_name,record,file_name,file_name_val)!=0){
		cout<<"busiVidHandleStart URL faild"<<endl;
		return -1;
	}
	RecordStopCallBack(file_name_val);
	
	return 0;
}

//take photo

int busiPhotoHandleStart(){
	
	char photo[100]="photo";
	char httpurl[100]="httpurl";
	char username[100]="username";
	char uid[100]="uid";
	
	char httpurl_val[100];
	char username_val[100];
	char uid_val[100];
	
	readConf(gfile_name,photo,httpurl,httpurl_val);
	readConf(gfile_name,photo,username,username_val);
	readConf(gfile_name,photo,uid,uid_val);
	
	cout<<httpurl_val<<endl;
	cout<<username_val<<endl;
	cout<<uid_val<<endl;
	cout<<"take photo"<<endl;
	
}

int busiPhotoHandleClose(){
	
	cout<<"busiPhotoHandleClose"<<endl;
	//close photo....

}

int cmdAnalfile_streamfile_streamHandle(int cmd)
{
	switch(cmd){
		
		case start_vf_preview:
			busiVidHandleStart();
			break;
		case stop_vf_preview:
			busiVidHandleStop();
			break;
		case start_vf_record:
			busiRecordHandleStart();
			break;
		case stop_vf_record:
			busiRecordHandleStop();
			break;
		case start_vf_photo:
			busiPhotoHandleStart();	
			break;
		case stop_vf_photo:
			busiPhotoHandleClose();
			break;
		default :
			cout<<"error:cmd"<<endl;
			break;		
		
	}
		
}

int main(int argc,char* argv[])
{
	cout<<"start all"<<endl;
	char obj[100]="record";
	char child_obj[100]="filename";
	cmdAnalfile_streamfile_streamHandle(start_vf_preview);
	printf("***");
	cmdAnalfile_streamfile_streamHandle(stop_vf_preview);
	printf("***");
	cmdAnalfile_streamfile_streamHandle(start_vf_record);
	printf("***");
	cmdAnalfile_streamfile_streamHandle(stop_vf_record);
	printf("***");
	cmdAnalfile_streamfile_streamHandle(start_vf_photo);
	printf("***");
	cmdAnalfile_streamfile_streamHandle(stop_vf_photo);
	printf("***");	
		
}

















