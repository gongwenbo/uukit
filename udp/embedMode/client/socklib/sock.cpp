#include "../include/sock.h"

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
    int n = sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&serv_addr, serverlen);
    if (n < 0){ 
		error("ERROR in sendto");
		return -1;
	}  
	return 0;	
}



int recieveDate(int sfd,char *buf,struct sockaddr_in &serv_addr){
	
	socklen_t serverlen = sizeof(serv_addr);
    int n = recvfrom(sfd, buf, strlen(buf), 0, (struct sockaddr*)&serv_addr, &serverlen);
    if (n < 0){ 
		error("ERROR in recvfrom");
		return -1;
	}
    printf("Echo from server: %s\n", buf);
    return 0;
	
}


