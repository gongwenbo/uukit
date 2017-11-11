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

void error(char *msg);

int initailSock(int &sfd,char *host_nam,int port,struct sockaddr_in &ser_addr);

int sendData(int sfd,char *buf,struct sockaddr_in serv_addr);

int recieveDate(int sfd,char *buf,struct sockaddr_in &serv_addr);

#endif