//date 11.8
#ifndef SOCK_H_
#define SOCK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define MAX_MSG 10
#include <iostream>

typedef enum _live_cmd_type_en
{//命令需要分设备发的还是客户端发的	
	cmd_reservse = 0,					//心跳     DU=>P2PS,CU=>P2PS  D&C =>TTS
	CMD_START_RAVS,						//start_vf_preview= 1
	CMD_STOP_RAVS,						//stop_vf_preview	= 2	
	CMD_START_REC,						//start_vf_record
	CMD_STOP_REC,						//stop_vf_record
	CMD_START_PHOTO,						//start_vf_photo
	CMD_STOP_PHOTO,						//stop_vf_photo
	CMD_SET_UTC,						//  SET UTC TIME  消息体 存

	NETCMD_GET_DEVCFG_REQ	=	0x1001,
	NETCMD_SET_DEVCFG_REQ	=	0x1002,
	NETCMD_SET_DEVWIFI_REQ	=	0x1003,
	
	NETCMD_GET_DEVCFG_RESP	=	0x8001,
	NETCMD_SET_DEVCFG_RESP	=	0x8002,
	NETCMD_SET_DEVWIFI_RESP	=	0x8003,
}LIVE_CMD_TYPE_EN;

typedef struct _net_cmd_struct
{
	unsigned int 	sign;	
	unsigned short 	cmdLen;	//包括 头长度
	unsigned short	CMD;
	unsigned char   cmdInfo[400];
}NETCMD_t,*NETCMD_pt;


void error(std::string msg);

int initailSock(int &sfd,char *host_nam,int port,struct sockaddr_in &ser_addr);

int sendData(int sfd,NETCMD_pt buf,struct sockaddr_in serv_addr);

int recieveDate(int sfd,NETCMD_pt reci_buf,struct sockaddr_in &serv_addr);

#endif