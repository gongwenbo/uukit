//date 11.8
#include "./include/sock.h"
#define CMD_A "start_vf_preview" 	
#define CMD_B "stop_vf_preview" 	
#define CMD_C "start_vf_record"		
#define CMD_D "stop_vf_record"		
#define	CMD_E "start_vf_photo"		
#define CMD_F "stop_vf_photo"		

int ParseCommond(LIVE_CMD_TYPE_EN &em_comm,char*comm){
	
	if(strcmp(comm,CMD_A)==0){
		em_comm=CMD_START_RAVS; 
		return 0;
	}
	else if(strcmp(comm,CMD_B)==0){
		em_comm=CMD_STOP_RAVS; 
		return 0;
	}
	else if(strcmp(comm,CMD_C)==0){
		em_comm=CMD_START_REC; 
		return 0;
	}	
	else if(strcmp(comm,CMD_D)==0){
		em_comm=CMD_STOP_REC; 
		return 0;
	}
	else if(strcmp(comm,CMD_E)==0){
		em_comm=CMD_START_PHOTO; 
		return 0;
	}
	else if(strcmp(comm,CMD_F)==0){
		em_comm=CMD_STOP_PHOTO; 
		return 0;
	}
	else return -1;	
}

int main(int argc, char *argv[]) {

	printf("start!\n");
	int sockfd, portno;
	struct sockaddr_in serveraddr;
	struct sockaddr_in backServerAdd;
	char hostname[100];
		
    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s  <commond> <parameter>\n", argv[0]);
       exit(0);
    }
    
	sprintf(hostname,"127.0.0.1");
	portno=8888;
	
	
	LIVE_CMD_TYPE_EN reci_commond;
	NETCMD_pt send_msg=(NETCMD_pt)malloc(sizeof(NETCMD_t));
	NETCMD_pt reci_buf=(NETCMD_pt)malloc(sizeof(NETCMD_t));	
	memset(send_msg,0,sizeof(NETCMD_t));
	memset(reci_buf,0,sizeof(NETCMD_t));
	
	if(ParseCommond(reci_commond,argv[1])!=0){
		printf("ERROR:ParseCommond\n");
		return -1;
	}
	
	printf ("reci_commond:%d",reci_commond);
	send_msg->CMD=reci_commond;
	
	strncpy((char*)send_msg->cmdInfo,argv[2],strlen(argv[2]));
	send_msg->cmdLen=8+strlen(argv[2]);
	
	initailSock(sockfd,hostname,portno,serveraddr);
	
	while(1){				
	if(sendData(sockfd,send_msg,serveraddr)!=0){
		printf("error:sendData");
	
	}

	if(recieveDate(sockfd,reci_buf,backServerAdd)!=0){
		printf("error:recieveDate");		
			
	}
	
	memset(reci_buf,0,sizeof(NETCMD_t));		
	sleep(1);
	}
	
	free(send_msg);
	free(reci_buf);
	return 0;

}