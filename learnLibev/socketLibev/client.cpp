#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int conncServer(char* ip,int port,int& socketfd);
int reWrFun(int fd);

int main(int argc,char* argv[])
{
	int sockFd;
	while(1){
	if(conncServer(argv[1],atoi(argv[2]),sockFd)!=0)
		cout<<"error:conncServer"<<endl;
	
	if (reWrFun(sockFd)!=0)
		cout<<"error:reWrFun"<<endl;
	};
}
int conncServer(char* ip,int port,int& socketfd)  //connect server 
{
	struct sockaddr_in serv_addr;
    struct hostent *server;
	int portno,sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
      perror("ERROR opening socket");
      return -1;
   }
   
	portno = port;
	server = gethostbyname(ip);
	if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      return -1;
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      return -1;
   }
   socketfd=sockfd; //return fd 
   	return 0;
	
};

int reWrFun(int fd){   //operate socket fd
	
	char buffer[256]; 
	printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
	int n=0;
	
	n = write(fd, buffer, strlen(buffer));  //write socket fd
	if (n < 0) {
      perror("ERROR writing to socket");
	  return -1;
    }
	
	bzero(buffer,256);
	
	n = read(fd, buffer, 255);
    if (n < 0) {
      perror("ERROR reading from socket");
      return -1;
	}
	
   printf("%s\n",buffer);
   return 0;
	
};












