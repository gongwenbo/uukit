//test 10.24
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>

#define BUFSIZE 1024
char buf[BUFSIZE];
using namespace std;

void error(string msg);
int configUdp(char* ip,int port,int &fd,struct sockaddr_in &serverAddr);
int reWropere(struct sockaddr_in serAddr,int fd);


int main(int argc,char* argv[])
{
	struct sockaddr_in serAdd;
	int fd;
	configUdp(argv[1],atoi(argv[2]),fd,serAdd);
	bzero(buf, BUFSIZE);
	while(1){
    printf("Please enter msg: ");
    fgets(buf, BUFSIZE, stdin);
	reWropere(serAdd,fd);
	};
	return 0;
}

void error(string msg) {
    perror(msg.c_str());
    exit(0);
};

int configUdp(char* ip,int port,int &fd,struct sockaddr_in &serverAddr){
	
	struct sockaddr_in serveraddr;
	char* hostname=ip;
	int portno=port;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct hostent *server;
    if (sockfd < 0) {
        error("ERROR opening socket");
		return -1;
	}
    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        return -1;
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);
	
	fd=sockfd;
	serverAddr=serveraddr;
	return 0;
	
};

int reWropere(struct sockaddr_in serAddr,int fd){
	
	int sockfd=fd,n=0;
	struct sockaddr_in serveraddr=serAddr;
	socklen_t serverlen=sizeof(serveraddr);
	
	n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serveraddr, serverlen);
    if (n < 0) {
		error("ERROR in sendto");
		return -1;
	}
    /* print the server's reply */
    n = recvfrom(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serveraddr, &serverlen);
    if (n < 0) {
		error("ERROR in recvfrom");
		return -1;
	}
    printf("Echo from server: %s", buf);
    return 0;
	
};




