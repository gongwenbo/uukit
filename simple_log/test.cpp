#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cerrno>
#include<fstream>

#define DEBUG(msg...) printf("[DEBUG:%s,%s,%d]",__FILE__,__func__,__LINE__);printf(msg);printf("\r\n"); 
#define ERROR(msg...) fprintf(stderr,"[ERROR:%s,%s,%d]",__FILE__,__func__,__LINE__);printf(msg);printf("\r\n");
int main(int argc,char* argv[]){


	DEBUG("test:%d",100);	
	char temp[30];
	strcpy(temp,"ok");
	ERROR("test error %s",temp);


}
