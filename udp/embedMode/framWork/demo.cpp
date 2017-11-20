//video online data:11.9 by gong
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdint.h>
#include "./include/cJSON.h"

//commond package
#define start_vf_preview 	1
#define stop_vf_preview 	2
#define start_vf_record		3
#define stop_vf_record		4
#define	start_vf_photo		5





#define stop_vf_photo		6


#define modify_time			7
#define MAX_MSG 10

#include "./sock/sock.h"
#include "./rtmp/src/play.h"
#define BUFSIZE 1024

#include "./nmOsal/src/nmOsalPublicFun.h" 
#include "./nmOsal/src/nmOsalQueue.h"
#include "./nmOsal/inc/nmOsal.h"
#include "./nmOsal/inc/nmOsalType.h"

//business
#include "./include/common.h"


char gfile_name[50]="json.json";
char push_url[200];

unsigned long m_hQueue;
unsigned long maxMsgs=10;

unsigned long from_hQueue;
unsigned long max_from_Msgs=8;
	
using namespace std;

typedef struct msg_data{
	
	char buf_msg[200];
	void *para;//reserve
			
}MSG_RS;

struct TrecordStaMsgBack{
	char* cmd;
	int time_sec;
	int time_usec;
		
};

struct TrecordStopMsgBack{
	
	char* cmd;
	char* file_name;
	
};

int paramHandle(MSG_RS request){
	
	for(int i=0;i<MAX_MSG;i++){
		
		int result; 
		//result=SetParamConfig(request.index[i], request.data[i],sizeof(request.data[i]),0 );   //lib at t20demo
		if(result!=0){
			cout<<"error:SetParamConfig!"<<endl;
			return -1;
		}else{return 0;}
		
	}	
}

int readConf(const char* file_name,const char* obj,const char* child_obj ,char* back){
	
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
	//char* tem=cJSON_Print(cJSON_GetObjectItem(data_json, child_obj));
	strcpy(back,cJSON_GetObjectItem(data_json, child_obj)->valuestring);
	free(data);	
	return 0;
}


void* pullVideo(void *agrv){
	
	unsigned long ulResp = 0;
	unsigned long ulLen=0;
	MSG_RS r_msg;
	while(1){
	ulResp = q_vreceive(m_hQueue,1,0,&r_msg,sizeof(MSG_RS),&ulLen);
	if(ulResp!=0){
		cout<<"q_vreceiveERROR!!"<<endl;
		continue;
	}
	cout<<"pullVideo start ,url:"<<r_msg.buf_msg<<endl;
	rtmp_start(r_msg.buf_msg);
	}
}

int stopVideo(){
	
	cout<<"stop Push Video"<<endl;
	//rtmp_pause();
	
}
int busiVidHandleStart(){
		
	char rtmp_url[100]="rtmp_url";
	char ip[3]="ip";
	char ip_val[200];
	char port[5]="port";
	char port_val[30];
	char sn[3]="sn";
	char sn_val[100];
	MSG_RS send_msg;
	
	
	readConf(gfile_name,rtmp_url,ip,ip_val);
	readConf(gfile_name,rtmp_url,port,port_val);
	readConf(gfile_name,rtmp_url,sn,sn_val);

	strcpy(push_url,"rtmp://");
	strcat(push_url,ip_val);
	strcat(push_url,":");
	strcat(push_url,port_val);
	strcat(push_url,sn_val);
	strcpy(send_msg.buf_msg,push_url);
	
	if(0 != q_vsend(m_hQueue,&send_msg,sizeof(MSG_RS)) )
		cout<<"q_vsend error!"<<endl;
	
	//pullVideo(push_url);	
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
	cout<<"sndmsg 127.0.0.1 2"<<endl;   //##�?始录制回调成
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
		cout<<"busiVidHandleStop URL faild"<<endl;
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
	printf("start take phone");
	
	//sample_get_jpeg_snap();
	
	
}

int busiPhotoHandleClose(){
	
	cout<<"busiPhotoHandleClose"<<endl;
	//close photo....

}

//modify time 
int busiMdityTime()
{
	printf("start busiModityTime\n");
	return 0;

}


int CommondParse(struct form_cli from_commond)
{
	
	switch(from_commond.CMD){
		
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
		case modify_time:
			busiMdityTime();
			break;
		default :
			cout<<"error:cmd"<<endl;
			break;		
		
	}
		
}

void* InternetDataHandle(void *agrv){
		
	int sockfd;
	struct sockaddr_in clientaddr;
	sockfd = *(((int**)agrv)[0]);
	clientaddr = *(((struct sockaddr_in**)agrv)[1]);
	void* buf_global=(void*)malloc(sizeof(struct form_cli));
	memset(buf_global,0,sizeof(struct form_cli));
	while (1) 
	{
	
	//recieve data
	//bzero(buf_global, BUFSIZE);
	if(recieveData(sockfd,buf_global,clientaddr)!=0){
		
		cout<<"ERROR:recieveData"<<endl;
		continue ;
	}
	
	struct form_cli *from_client_msg=(struct form_cli *)buf_global;
	printf("from_client_msg::CMD:%d,cmdInfo:%s\n",from_client_msg->CMD,from_client_msg->cmdInfo);

	
	if(sendData(sockfd,buf_global,clientaddr)!=0){
		cout<<"ERROR:sendData"<<endl;
		continue ;
	}

	if(0 != q_vsend(from_hQueue,from_client_msg,sizeof(struct form_cli)) )
		cout<<"q_vsend4 error!"<<endl;
    sleep(1);
    
	}	
	free(buf_global);	
}


int main(int argc,char* argv[])
{

	int port;
	int sockfd;
	struct sockaddr_in clientaddr; /* client addr */
	pthread_t pid_inter;
	pthread_t pid_push_v;
	int error_intet;
	int error_push_video;
	struct form_cli get_msg_from_cli;
	unsigned long from_ulLen=0;
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s \n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);  //port info
	
	if(buiSocAndBind(sockfd,port)!=0) //socket bind
		return -1;
	
	//initial m_hQueue
	unsigned long res_m_hQueue =q_vcreate("msg",0,maxMsgs,sizeof(MSG_RS),&m_hQueue);
	if(res_m_hQueue!=0)
		cout<<"q_vcreate1 error"<<endl;
	
	//initial from_hQueue
	unsigned long res_from_hQueue=q_vcreate("from_msg",0,max_from_Msgs,sizeof(struct form_cli),&from_hQueue);
	if(res_from_hQueue!=0)
		cout<<"q_vcreate2 error"<<endl;

	
	//transform argv
	void* args_inter[2]={(void*)&sockfd,(void*)&clientaddr};
	
	//deal with internet event  
	error_intet=pthread_create(&pid_inter,NULL,&InternetDataHandle,args_inter);
	if(error_intet!=0)
		cout<<"create thread1 fail"<<endl;
	
	//deal with push video 
	error_push_video=pthread_create(&pid_push_v,NULL,&pullVideo,NULL);
	if(error_push_video!=0)
		cout<<"create thread2 fail"<<endl;	
	
	cout<<"return main"<<endl;
	while(1){
		if(0!=q_vreceive(from_hQueue,1,0,&get_msg_from_cli,sizeof(struct form_cli),&from_ulLen))
			cout<<"q_vreceiveERROR!!4"<<endl;
		CommondParse(get_msg_from_cli);
		sleep(1);
	}
	
	pthread_join(pid_inter,NULL);
	pthread_join(pid_push_v,NULL);
	return 0;
				
}

