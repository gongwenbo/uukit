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
#define start_vf_preview 	0x4
#define stop_vf_preview 	0x5
#define start_vf_record		0x17
#define stop_vf_record		0x18
#define	start_vf_photo		0x6
#define stop_vf_photo		0x7
#define MAX_MSG 10

#include "./sock/sock.h"
#define BUFSIZE 1024

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

int cmdAnalfile_streamfile_streamHandle(char* commond)
{
	
	int cmd;
	printf("commond:%s\n",commond);
	if(strcmp(commond,"start_vf_preview")==1)
		cmd=start_vf_preview;
	else if(strcmp(commond,"stop_vf_preview")==1)
		cmd=stop_vf_preview;
	else if(strcmp(commond,"start_vf_record")==1)
		cmd=start_vf_record;	
	else if(strcmp(commond,"stop_vf_record")==1)
		cmd=stop_vf_record;	
	else if(strcmp(commond,"start_vf_photo")==1)
		cmd=start_vf_photo;	
	else if(strcmp(commond,"stop_vf_photo")==1)
		cmd=stop_vf_photo;	
	else cmd=0;
	printf("cmd:%x\n",cmd);

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

void* threadFunc(void *agrv){
	
	char buf[BUFSIZE]; /* message buf */	
	int sockfd;
	struct sockaddr_in clientaddr;
	sockfd = *(((int**)agrv)[0]);
	clientaddr = *(((struct sockaddr_in**)agrv)[1]);
		
	while (1) 
	{
	
	//recieve data
	bzero(buf, BUFSIZE);
	if(recieveData(sockfd,buf,clientaddr)!=0){
		
		cout<<"ERROR:recieveData"<<endl;
		continue ;
	}
	
	cmdAnalfile_streamfile_streamHandle(buf);
	
	//send data
	if(sendData(sockfd,buf,clientaddr)!=0){
		cout<<"ERROR:sendData"<<endl;
		continue ;
	}
    sleep(1);
    
	}	
		
}


int main(int argc,char* argv[])
{

	int port;
	int sockfd;
	struct sockaddr_in clientaddr; /* client addr */
	pthread_t pid;
	int error;
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s \n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);  //port info
	
	if(buiSocAndBind(sockfd,port)!=0) //socket bind
		return -1;
		
		//transform argv
	void* args[2]={(void*)&sockfd,(void*)&clientaddr};
	//create thread 
	error=pthread_create(&pid,NULL,&threadFunc,args);
	if(error!=0)
		cout<<"create thread fail"<<endl;
	cout<<"return main"<<endl;
	
	pthread_join(pid,NULL);
	return 0;
				
}

















