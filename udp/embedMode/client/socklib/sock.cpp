#include "../include/sock.h"

void error(std::string msg) {
    perror(msg.c_str());
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

int sendData(int sfd,NETCMD_pt buf,struct sockaddr_in serv_addr){
	
	socklen_t serverlen = sizeof(serv_addr);
	size_t len=sizeof(NETCMD_t);
    int n = sendto(sfd, (char*)buf, len, 0, (struct sockaddr*)&serv_addr, serverlen);
    if (n < 0){ 
		error("ERROR in sendto");
		return -1;
	} 
	printf("send data bytes:%d\n",n);
	return 0;	
}

int recieveDate(int sfd,NETCMD_pt reci_buf,struct sockaddr_in &serv_addr){
	
	char* buf=(char*)malloc(sizeof(NETCMD_t));
	memset(buf,0,sizeof(NETCMD_t));
	size_t len=sizeof(NETCMD_t);
	
	socklen_t serverlen = sizeof(serv_addr);
    int n = recvfrom(sfd, buf, len, 0, (struct sockaddr*)&serv_addr, &serverlen);
    if (n < 0){ 
		error("ERROR in recvfrom");
		return -1;
	}
	//memcpy(reci_buf,buf,sizeof(NETCMD_t));
	reci_buf=(NETCMD_pt)buf;
	free(buf);
    printf("Echo from server: %d\n", reci_buf->CMD);
    return 0;
	
}
