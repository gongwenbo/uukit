//date 11.8
#include "./include/sock.h"

#define BUFSIZE 1024

int sockfd, portno;
struct sockaddr_in serveraddr;
struct sockaddr_in backServerAdd;
char *hostname;
char buf[BUFSIZE];

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
	sprintf(buf,"start_vf_photo");
	
	while(1){
		
		//fgets(buf, BUFSIZE, stdin);		
		if(sendData(sockfd,buf,serveraddr)!=0){
			printf("error:sendData");
			continue ;
		}
		memset(buf,1,sizeof(buf));
		if(recieveDate(sockfd,buf,backServerAdd)!=0){
			printf("error:recieveDate");
			continue ;			
			
		}
			
		sleep(1);
	}
	return 0;

}