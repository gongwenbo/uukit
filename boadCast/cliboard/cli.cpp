#include<stdio.h>
#include<stdlib.h>
#include<uv.h>
#include<iostream>

#define PORT 8888
#define SERVER_PORT 8889

using namespace std;
uv_loop_t *loop;
uv_udp_t send_socket;
uv_udp_t recieve_socket;
uv_udp_send_t send_req;
uv_buf_t* msg;

//apply buf
void allow_buffer(uv_handle_t* handle,size_t suggested_size,uv_buf_t* buf){
	*buf=uv_buf_int((char*)malloc(suggested_size),suggested_size);
		
}

void RecieveRead(uv_udp_t* req,long nread,const uv_buf_t* buf,
const struct sockaddr* addr,unsigned flags)
{
	if(nread==-1){
		fprintf(stderr,"read error!!\n");
		uv_close((uv_handle_t*)req,NULL);
		free(buf->base);
		return;		
	}
	
	char from_host[30];
	uv_ip4_name((struct sockaddr_in*)addr,form_host,sizeof(from_host));
	fprintf(stderr,"remoteIP:%s",from_host);
	
	for(int i=0;i<nread;i++){
		cout<<"recieve data:"<<buf->base[i]<<endl;
				
	}
	
	free(buf->base);
	//uv_udp_recv_stop(req);
	
}

void SendFun(uv_udp_send_t*req,int status){
	
	if(status==-1){
		cout<<"send error!!"<<endl;
		return ;
	}else{
		cout<<"send succedd!!"<<endl;
		
	}
	
}


int main(int argc,char* argv[])
{
	loop=uv_default_loop();
	//recieve config
	struct sockaddr_in recv_addr;
	uv_udp_init(loop,&recieve_socket);
	uv_ip4_addr("0.0.0.0",PORT,&recv_addr);
	uv_udp_bind(&recieve_socket,(struct sockaddr*)&recv_addr,0);
	uv_udp_recv_start(&recieve_socket,allow_buffer,RecieveRead);
	
	//send socket config
	struct sockaddr_in send_addr;
	uv_udp_init(loop,&send_socket);
	uv_ip4_addr("0.0.0.0",SERVER_PORT,&send_addr);
	//uv_udp_bind(&send_socket,(struct sockaddr*)&send_addr,0)
	
	allow_buffer((uv_handle_t*)&send_req,32,&msg);
	
	uv_udp_send(&send_req,&send_socket,&msg,1,(struct sockaddr*)&send_addr,SendFun);
	
	return uv_run(loop,UV_RUN_DEFAULT);
	
}
