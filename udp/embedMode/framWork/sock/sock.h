#ifndef SOCK_H_
#define SOCK_H_
//date 11.8 by gong
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <iostream>
#define MAX_MSG 10
struct form_cli{
	
	unsigned int 	sign;	
	unsigned short 	cmdLen;	//包括 头长度
	unsigned short	CMD;
	unsigned char   cmdInfo[400];
	
}; 

using namespace std;
void error(string str);

int recieveData(int sfd,void* buf,struct sockaddr_in &clientaddr);

int buiSocAndBind(int &sfd,int port);

int sendData(int sfd,void* buf,struct sockaddr_in cli_addr);


#endif