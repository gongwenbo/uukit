
#include "common.h"
using namespace std;

TcpCli::TcpCli(uv_loop_t* loop_pts){

	tcp_client_=new uv_tcp_t();
	connect_req_=new uv_connect_t();
	req_addr_=new sockaddr_in();
	
	uv_tcp_init(loop_pts, tcp_client_);
	uv_ip4_addr("127.0.0.1",PORT,req_addr_);
	cout<<"connection server port:"<<PORT<<endl;
	
	uv_tcp_connect(connect_req_, tcp_client_, (const struct sockaddr*)req_addr_, TcpCli::OnConnection);

}

TcpCli::~TcpCli(){
	
	delete tcp_client_;
	delete connect_req_;
	delete req_addr_;

}

void TcpCli::OnConnection(uv_connect_t *req, int status) {
	if (status == -1) {
		fprintf(stderr, "error on_write_end");
		return;
	}	
	Log::debug(__func__,__LINE__,"TcpCli::OnConnection");
	req_work.data=(void*)(req->handle);
		
}

