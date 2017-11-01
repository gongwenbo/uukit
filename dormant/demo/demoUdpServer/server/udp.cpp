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
#include "../../nmOsal/src/nmOsalPublicFun.h" 
#include "../../nmOsal/src/nmOsalQueue.h"
#include "../../nmOsal/inc/nmOsal.h"
#include "../../nmOsal/inc/nmOsalType.h"
int NUM=0;
using namespace std;
typedef struct Msg{
	int id;
	char _MSG[50];
	
}MSG;

uv_barrier_t blocker;
uv_rwlock_t numlock;


redisContext *pRedisContext;
uv_loop_t *loop;
uv_udp_t recv_socket;


static uv_sem_t sem_main;
static uv_sem_t protectQUe;

// message paramter 
unsigned long maxMsgs=5;
unsigned long ulRet = 0;
unsigned long m_hQueue;
unsigned long ulLen=0;
unsigned long ulResp = 0;
MSG _MSGsend,_MSGrecieve;
	

char *BUFFER=new char(50);  


void testRedis(void *Argv);
void worite_queu(uv_work_t *req);
void after(uv_work_t *req, int status);

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
		buf->base = (char*) malloc(suggested_size);
		buf->len = suggested_size;
		
}

static void on_send(uv_udp_send_t* req, int status) 
{   
    free(req);
    if (status) {
        fprintf(stderr, "uv_udp_send_cb error: %s\n", uv_strerror(status));
    }
}

	
void writeRedis(uv_udp_t *req, ssize_t nread, const uv_buf_t* buf, 
    const struct sockaddr *addr, unsigned flags) 
{
	
	if (nread <0) {
		fprintf(stderr, "Read error!\n");
		uv_close((uv_handle_t*) req, NULL);
		free(buf->base);
		return ;
	}
		
    else{
		
		uv_work_t *workReq=(uv_work_t*)malloc(sizeof(uv_work_t));
		char temp[50]; //global variable
		//uv_rwlock_wrlock(&numlock);
		strcpy(temp,buf->base);															
		workReq->data=(void*)temp;		
		//uv_rwlock_wrunlock(&numlock);
		cout<<"workReq.data:"<<(char*)workReq->data<<endl;
		
		uv_queue_work(loop, workReq, worite_queu, after);
		
		//uv_sem_wait(&protectQUe);
		//sleep(1);
		/*char _data[50];
		sprintf(_data,"%s",_MSGsend._MSG);
						
		uv_udp_send_t* _req = (uv_udp_send_t*)malloc(sizeof(uv_udp_send_t));
		uv_buf_t _buf = uv_buf_init(_data, sizeof(_data));
        int r = uv_udp_send(_req, req, &_buf, 1, addr, on_send);
		if (r) {
			fprintf(stderr, "uv_udp_send error: %s\n", uv_strerror(r));
		}
		*/
		sleep(1);
    }
	
}

void testRedis(void *Argv)
{
	
	char *buffer=(char*)Argv;
	
    char COMD[50];
	while(1){

		memset(COMD,0,sizeof(COMD));
		//uv_rwlock_rdlock(&numlock);
		ulResp = q_vreceive(m_hQueue,0,0,&_MSGrecieve,sizeof(_MSGrecieve),&ulLen);
		//uv_rwlock_rdunlock(&numlock);
		uv_sem_post(&protectQUe);
		sleep(1);
		if(ulResp!=0){
			cout<<"q_vreceiveERROR!!"<<endl;
			//return ;
			continue;
		}				
		
		snprintf(COMD,sizeof(COMD),"get %s",_MSGrecieve._MSG);		
		cout<<"COMD:"<<COMD<<endl;
		
		if((COMD!=NULL)){
			
			redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext,COMD);  //执行INFO命令	
			if (pRedisReply == NULL)  
			{  
				printf("Get Data failed\n");  
				redisFree(pRedisContext);  
				continue;  
			}  
			if (pRedisReply->type != REDIS_REPLY_STRING)  
			{  
				freeReplyObject(pRedisReply);  
				continue;  
			}
		
			std::cout << pRedisReply->str << std::endl;
			freeReplyObject(pRedisReply);
		}
		NUM++;
		cout<<"NUM:"<<NUM<<endl;
	}
	uv_barrier_wait(&blocker);
}
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
}

void MessageIni(){

	_MSGsend.id=12;
	sprintf(_MSGsend._MSG,"test");
	char msgname[50];
	sprintf(msgname,"msg");
	ulRet = q_vcreate(msgname,0,maxMsgs,sizeof(MSG),&m_hQueue);
	if(ulRet!=0){
		cout<<"q_vcreate error"<<endl;
		return;
	}
	cout<<"MessageIni success"<<endl;
	
}

void SemInitail(){
	cout<<"SemInitail"<<endl;
	uv_sem_init(&sem_main, 0);
	uv_sem_init(&protectQUe, 0);
}

void Recycle(){
	uv_barrier_wait(&blocker);
    uv_barrier_destroy(&blocker);
	uv_rwlock_destroy(&numlock);
	uv_sem_destroy(&sem_main);
	
}

void worite_queu(uv_work_t *req){
	
	sprintf(_MSGsend._MSG,"%s",(char*) req->data);
	if(0 != q_vsend(m_hQueue,&_MSGsend,sizeof(MSG)) )
		cout<<"q_vsend error!"<<endl;

	cout<<"send data:"<<_MSGsend._MSG<<endl;
	uv_sem_wait(&protectQUe);
	
}

void after(uv_work_t *req, int status) {
  fprintf(stderr, "worite_queu complete\n");
 // free(workReq);
  //uv_close((uv_handle_t*) &async, NULL);
}

int main() {
	

	SemInitail();
	MessageIni();
	InitRedis();
	uv_barrier_init(&blocker, 4);
	uv_rwlock_init(&numlock);
	sprintf(BUFFER,"redis INFO");
	uv_thread_t Threids;
	uv_thread_create(&Threids, testRedis, BUFFER);
		
	loop = uv_default_loop();
	uv_udp_init(loop, &recv_socket);
	struct sockaddr_in recv_addr ;
	uv_ip4_addr("0.0.0.0", 9999,&recv_addr);
	uv_udp_bind(&recv_socket, (const struct sockaddr*)&recv_addr, 0);
	
	//uv_work_
	//uv_queue_work(loop, &workReq, worite_queu, after);
	//uv_udp
	uv_udp_recv_start(&recv_socket, alloc_buffer, writeRedis);
	return uv_run(loop, UV_RUN_DEFAULT);
	Recycle();


}
