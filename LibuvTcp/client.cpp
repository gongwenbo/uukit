/*
libuv tcp 客户端
2018-04-15 
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <uv.h>
#define BUFFER_SIZE 5  //发送buffer的大小

void after_write(uv_write_t *req, int status)
{
    printf("after_write\n");
    assert(!status);
}

void on_connect(uv_connect_t *req, int status)
{
    printf("on_connect\n");
    assert(!status);

    char req_message[100]="test libuv\n"; //发送的消息
	
	uv_buf_t* bufs(new uv_buf_t[BUFFER_SIZE]);
	bufs->base=req_message;
	bufs->len=strlen(req_message);

    uv_stream_t *tcp = req->handle;
    uv_write_t write_req;
    uv_write(&write_req, tcp, bufs, BUFFER_SIZE, after_write);  //给套接字写数据
	
	delete[] bufs;
}

int main(int argc, char const *argv[])
{
    uv_tcp_t socket;
    assert(!uv_tcp_init(uv_default_loop(), &socket));

    struct sockaddr_in dest;
    assert(!uv_ip4_addr("127.0.0.1", 8000, &dest));

    uv_connect_t connect;
    assert(!uv_tcp_connect(&connect, &socket, (struct sockaddr *) &dest, on_connect));
    uv_run(uv_default_loop(), UV_RUN_ONCE);
    return 0;
}
