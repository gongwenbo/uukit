#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128
#include <iostream>
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <cstring>


using namespace std;

typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

uv_loop_t *loop=new uv_loop_t;
char* Command;
class initConec{
	private:
		uv_tcp_t server;
		char *_ip ;
		int _port;
		struct sockaddr_in _addr;
		int r;
		
	public:
		initConec(char* ip,int port,uv_connection_cb cb):_ip(ip),_port(port)
		{
			
			_ip=new char;
			uv_tcp_init(loop, &server);
			uv_ip4_addr(_ip,_port, &_addr);
			uv_tcp_bind(&server, (const struct sockaddr*)&_addr, 0);
			int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, cb);
			if (r) 
			{
				fprintf(stderr, "Listen error %s\n", uv_strerror(r));
				
			}
				
		}
		~initConec(){cout<<"delete initConec "<<endl;
			delete _ip;
		}
	
};

class reWrMode{
		
	public:
	
	void static free_write_req(uv_write_t *req) {
		write_req_t *wr = (write_req_t*) req;
		free(wr->buf.base);
		free(wr);
	}

	void static alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
		buf->base = (char*) malloc(suggested_size);
		buf->len = suggested_size;
	}

	void static echo_write(uv_write_t *req, int status) {
		if (status) {
			fprintf(stderr, "Write error %s\n", uv_strerror(status));
		}
		free_write_req(req);
	}

	void static echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) 
	{
		if (nread > 0) {
			write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
			req->buf = uv_buf_init(buf->base, nread);
			uv_write((uv_write_t*) req, client, &req->buf, 1, echo_write);
			Command=req->buf.base;
			cout<<"Command:"<<Command<<endl;
			cout<<"req->buf.base:"<<req->buf.base<<endl;
			return;
		}
		if (nread < 0) {
			if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
			uv_close((uv_handle_t*) client, NULL);
		}

		free(buf->base);
	}
	
	void static on_new_connection(uv_stream_t *server, int status) {
		if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
		}

		uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
		uv_tcp_init(loop, client);
		if (uv_accept(server, (uv_stream_t*) client) == 0) {
			uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
		}
		else {
			uv_close((uv_handle_t*) client, NULL);
		}
	}
	
};

class operRedis{
	
	private:
		struct timeval timeout;
		redisContext *pRedisContext;
		redisReply *pRedisReply;
		
	public:
		operRedis(){
			
			//pRedisContext=new redisContext;
			//pRedisReply=new redisReply;
			timeout.tv_sec=2;
			timeout.tv_usec=0;
		}
		int connetRedis(){
			pRedisContext = (redisContext*)redisConnectWithTimeout("127.0.0.1", 6379, timeout);
			 if ( (NULL == pRedisContext) || (pRedisContext->err) )
			{
				if (pRedisContext)
				{
					std::cout << "connect error:" << pRedisContext->errstr << std::endl;
				}
				else
				{
				std::cout << "connect error: can't allocate redis context." << std::endl;
				}
				return -1;
			}
		};
		int exeComand(char* _Command){
			cout<<"_Command::"<<Command<<endl;
			redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext,"INFO" );  //执行命令
			std::cout << pRedisReply->str << std::endl;
			freeReplyObject(pRedisReply); 
			return 0;
		};
		~operRedis(){
			cout<<"delete operRedis"<<endl;
			 
			//delete pRedisContext;
			//delete pRedisReply;
		};
};


int main(int argc,char* argv[])
{
	loop = uv_default_loop();
	if(argc<3)
		cout<<"input you ip and port!"<<endl;
	
	
	//reWrMode* objRW=new reWrMode();
    initConec* objInit=new initConec(argv[1],atoi(argv[2]),uv_connection_cb(reWrMode::on_new_connection));
	cout<<"next"<<endl;
	/*operRedis* oper_Redis=new operRedis();
	oper_Redis->connetRedis();
	oper_Redis->exeComand(Command);
	*///freeReplyObject(pRedisReply);
	return uv_run(loop, UV_RUN_DEFAULT);
	
}














