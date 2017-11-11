#include "sock.h"

void error(string str) {
  perror(str.c_str());
  exit(1);
}

int buiSocAndBind(int &sfd,int port){

	int optval; /* flag value for setsockopt */
	struct sockaddr_in serveraddr; /* server's addr */
	
	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sfd < 0){ 
		error("ERROR opening socket");
		return -1;
	}

	optval = 1;
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

	//build server's Internet address
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);

	//bind socket with a port 
	if (bind(sfd, (struct sockaddr *) &serveraddr, 
	   sizeof(serveraddr)) < 0) {
		
		error("ERROR on binding");	
		return -1;
	}	
	return 0;
}

int sendData(int sfd,char* buf,struct sockaddr_in cli_addr){
	
	//send data
	int n; /* message byte size */
	socklen_t clientlen= sizeof(cli_addr);
	
    n = sendto(sfd, buf, strlen(buf), 0, 
	  (struct sockaddr *) &cli_addr, clientlen);
    if (n < 0) {
		error("ERROR in sendto");
		return -1;
	}	
	return 0;
	//business...
}

int recieveData(int sfd,char* buf,struct sockaddr_in &clientaddr){

	int n=0;
	struct hostent *hostp; /* client host info */
	char *hostaddrp; /* dotted decimal host addr string */
	socklen_t clientlen = sizeof(clientaddr);
	n = recvfrom(sfd, buf, 1024, 0,
		 (struct sockaddr *) &clientaddr, &clientlen);
    if (n < 0){
		error("ERROR in recvfrom");
		return -1;
	}

    //gethostbyaddr: determine who sent the datagram
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
		error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
		error("ERROR on inet_ntoa\n");
	
    printf("server received datagram from %s (%s)::%u\n", 
	   hostp->h_name, hostaddrp,clientaddr.sin_port);
    printf("server received %d/%d bytes: %s\n", strlen(buf), n, buf);
	return 0;
	//business .....	
}













