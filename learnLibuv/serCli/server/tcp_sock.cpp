#include "tcp_sock.h"
using namespace std;

void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf) {
    size = 1024;
    buf->base = (char*)malloc(size);
    buf->len = size;
}

void echo_read(uv_stream_t *client_stream, ssize_t nread, const uv_buf_t *buf) {
    
    if (nread == UV_EOF) {
        printf("<EOF>\n");
    }
	debug(__func__,__LINE__,"echo_read:%s\n",buf->base);

	//return data to client 
	uv_write_t write_req;
	char message[200] = "return data:";
	strcat(message,buf->base);  //data append 
	
	int len = strlen(message);
	int buf_count = 1;
	char buffer_size[200];
	uv_buf_t buf_back = uv_buf_init(buffer_size, sizeof(buffer_size));
	buf_back.len = len;
	buf_back.base = message;
		
	uv_write(&write_req, client_stream, &buf_back, buf_count, on_write_end);
	cout<<"server uv_write "<<endl;
	
}

void on_write_end(uv_write_t *req, int status) {
  if (status == -1) {
    fprintf(stderr, "error on_write_end");
    return;
  }

}


void on_new_connection(uv_stream_t *server, int status) {

    if (status < 0) {
        fprintf(stderr, "on_new_connection(%p): error %s\n", server, uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
    } else {
        uv_close((uv_handle_t*)client, NULL);
		free(client);
		return ;
    }
	

}

int TcpInit(uv_tcp_t* server_socket,uv_loop_t* loop){

	struct sockaddr_in addr;	
    uv_tcp_init(loop, server_socket);
	
    printf("Running on port %d\n", DEFAULT_PORT);
    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
    uv_tcp_bind(server_socket, (const struct sockaddr *)&addr, 0);

    int r = uv_listen((uv_stream_t *)server_socket, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error: %s\n", uv_strerror(r));
        return 1;
    }else{

		cout<<"success TcpInit"<<endl;	
		return 0;

	}	

}
















