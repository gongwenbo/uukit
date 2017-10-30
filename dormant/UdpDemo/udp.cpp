#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <iostream>
#include <hiredis/hiredis.h>
#include <string> 
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h> 
#include <sys/shm.h> 
#define TEXT_SZ 100
struct shared_use_st  
{  
    int written;//作为一个标志，非0：表示可读，0表示可写  
    char text[TEXT_SZ];//记录写入和读取的文本  
}; 

uv_barrier_t blocker;
uv_rwlock_t numlock;
void testRedis(void *Argv);
using namespace std;
redisContext *pRedisContext;
uv_loop_t *loop;
uv_udp_t recv_socket;

char *BUFFER=new char(50);   
void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
		buf->base = (char*) malloc(suggested_size);
		buf->len = suggested_size;
		
}
	
void writeRedis(uv_udp_t *req, ssize_t nread, const uv_buf_t* buf, 
    const struct sockaddr *addr, unsigned flags) 
{
	
	if (nread == -1) {
		fprintf(stderr, "Read error!\n");
		uv_close((uv_handle_t*) req, NULL);
		free(buf->base);
    
	}
	
	//cout<<"buf->base:"<<buf->base<<endl;	
	//testRedis(buf->base);
	if(nread < 3) return ;
	uv_rwlock_wrlock(&numlock);
	strcpy(BUFFER,buf->base);
	cout<<"BUFFER1:"<<BUFFER<<endl;
	uv_rwlock_wrunlock(&numlock);
	
	
};

void testRedis(void *Argv)
{
	
	char *buffer=(char*)Argv;
	
    char COMD[50];
	//sprintf(COMD,"test");
	for(int i=1000;i>0;i--){
		uv_rwlock_rdlock(&numlock);
		strncpy(COMD,BUFFER,sizeof(COMD));
		cout<<"BUFFER2:"<<BUFFER<<endl;
		uv_rwlock_rdunlock(&numlock);
		
		//cout<<"COMD:"<<COMD<<endl;
			sleep(1);
		//sprintf(COMD,"name");
		/*
		if(COMD!=NULL){
		redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext,"get %s",COMD);  //执行INFO命令	
		std::cout << pRedisReply->str << std::endl;
		freeReplyObject(pRedisReply);
	}
	*/
	}
	uv_barrier_wait(&blocker);
};
void InitRedis(){
	struct timeval timeout = {2, 0};    //2s的超时时间
	pRedisContext = (redisContext*)redisConnectWithTimeout("127.0.0.1", 6379, timeout);
    if ( (NULL == pRedisContext) || (pRedisContext->err) )
    {
        if (pRedisContext)
        {
            cout << "connect error:" << pRedisContext->errstr <<endl;
        }
        else
        {
            cout << "connect error: can't allocate redis context." <<endl;
        }        
    }
};

int main() {
	
	InitRedis();
	uv_barrier_init(&blocker, 4);
	uv_rwlock_init(&numlock);
	sprintf(BUFFER,"INFO");
	uv_thread_t Threids;
	uv_thread_create(&Threids, testRedis, BUFFER);
		
	loop = uv_default_loop();
	uv_udp_init(loop, &recv_socket);
	struct sockaddr_in recv_addr ;
	uv_ip4_addr("0.0.0.0", 9999,&recv_addr);
	uv_udp_bind(&recv_socket, (const struct sockaddr*)&recv_addr, 0);

	uv_udp_recv_start(&recv_socket, alloc_buffer, writeRedis);
	return uv_run(loop, UV_RUN_DEFAULT);
	
	uv_barrier_wait(&blocker);
    uv_barrier_destroy(&blocker);
	uv_rwlock_destroy(&numlock);

}
