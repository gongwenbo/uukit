//date 11.8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 1024

int sockfd, portno, n;
struct sockaddr_in serveraddr;
struct sockaddr_in backServerAdd;
char *hostname;
char buf[BUFSIZE];

void error(char *msg) {
    perror(msg);
    exit(0);
}

int initailSock(int &sfd,char *host_nam,int port,struct sockaddr_in &ser_addr){
    
	/* socket: create the socket */
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0) 
        error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */
	struct hostent *server;
    server = gethostbyname(host_nam);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", host_nam);
        exit(0);
    }

    /* build the server's Internet address */
    bzero((char *) &ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&ser_addr.sin_addr.s_addr, server->h_length);
    ser_addr.sin_port = htons(port);	
	return 0;
	
}

int sendData(int sfd,char *buf,struct sockaddr_in serv_addr){
	
	socklen_t serverlen = sizeof(serv_addr);
    n = sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&serv_addr, serverlen);
    if (n < 0){ 
		error("ERROR in sendto");
		return -1;
	}  
	return 0;	
}

int recieveDate(int sfd,char *buf,struct sockaddr_in &serv_addr){
	
	socklen_t serverlen = sizeof(serv_addr);
    n = recvfrom(sfd, buf, strlen(buf), 0, (struct sockaddr*)&serv_addr, &serverlen);
    if (n < 0){ 
		error("ERROR in recvfrom");
		return -1;
	}
    printf("Echo from server: %s\n", buf);
    return 0;
	
}
int main(int argc, char **argv) {


    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);
	initailSock(sockfd,hostname,portno,serveraddr);
	
	/* get a message from the user */
	bzero(buf, BUFSIZE);
	sprintf(buf,"test upd server!");
	
	while(1){
		
		//fgets(buf, BUFSIZE, stdin);		
		if(sendData(sockfd,buf,serveraddr)!=0){
			printf("error:sendData");
			continue ;
		}
	
		if(recieveDate(sockfd,buf,backServerAdd)!=0){
			printf("error:recieveDate");
			continue ;			
			
		}
			
		sleep(1);
	}
	return 0;

}