#include "common.h"

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
uv_udp_t dev_socket;

uv_work_t *workReq=(uv_work_t*)malloc(sizeof(uv_work_t));

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
void handleDevData(uv_work_t *req);
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


static void send_resp(uv_udp_t* handle, char* data, const struct sockaddr* addr) 
{
    uv_udp_send_t* req = (uv_udp_send_t* )malloc(sizeof(uv_udp_send_t));
    uv_buf_t buf = uv_buf_init((char*) data, sizeof(data));
    int r = uv_udp_send(req, handle, &buf, 1, addr, on_send);
    if (r) {
        fprintf(stderr, "uv_udp_send error: %s\n", uv_strerror(r));
    }
}


	
void devCB(uv_udp_t *req, ssize_t nread, const uv_buf_t* buf,  //device call back
    const struct sockaddr *addr, unsigned flags) 
{
	
	if (nread <0) {
		fprintf(stderr, "Read error!\n");
		uv_close((uv_handle_t*) req, NULL);
		free(buf->base);
		return ;
	}
		
    else{
		
		
		char temp[50];
		//uv_rwlock_wrlock(&numlock);
		strcpy(temp,buf->base);															
		workReq->data=(void*)temp;		
		//uv_rwlock_wrunlock(&numlock);
		cout<<"workReq.data:"<<(char*)workReq->data<<endl;
		
		char _data[50];
		sprintf(_data,"%s",temp);
		if(_data!=NULL)
		send_resp(req,_data, addr);
		else return;
	

		//uv_queue_work(loop, workReq, handleDevData, after);  //异步调用
		
		//uv_sem_wait(&protectQUe);
		

    }
	
}

void testRedis(void *Argv)
{
	
	char *buffer=(char*)Argv;
	pRedisContext=InitRedis();
	
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
		if(_MSGrecieve._MSG!=NULL)
			exeRedis(pRedisContext,COMD);
		else	
			continue;

	}
	
	uv_barrier_wait(&blocker);
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

void handleDevData(uv_work_t *req){
	
	sprintf(_MSGsend._MSG,"%s",(char*) req->data);
	if(0 != q_vsend(m_hQueue,&_MSGsend,sizeof(MSG)) )
		cout<<"q_vsend error!"<<endl;

	cout<<"send data:"<<_MSGsend._MSG<<endl;
	uv_sem_wait(&protectQUe);
	
}

void after(uv_work_t *req, int status) {
  fprintf(stderr, "handleDevData complete\n");
  free(workReq);
  //uv_close((uv_handle_t*) &async, NULL);
}

int main() {
	

	SemInitail();
	MessageIni();
	//InitRedis();
	uv_barrier_init(&blocker, 4);
	uv_rwlock_init(&numlock);
	sprintf(BUFFER,"redis INFO");
	uv_thread_t Threids;
	uv_thread_create(&Threids, testRedis, BUFFER);
		
	loop = uv_default_loop();
	uv_udp_init(loop, &dev_socket);
	struct sockaddr_in dev_addr ;
	uv_ip4_addr("0.0.0.0", 9999,&dev_addr);
	uv_udp_bind(&dev_socket, (const struct sockaddr*)&dev_addr, 0);
	
	uv_udp_recv_start(&dev_socket, alloc_buffer, devCB);
	return uv_run(loop, UV_RUN_DEFAULT);
	Recycle();


}
