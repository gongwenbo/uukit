#ifndef TCP_CLI_H
#define TCP_CLI_H
#include "common.h"

class TcpCli{

	private:
		uv_tcp_t* tcp_client_;
		uv_connect_t* connect_req_;
		struct sockaddr_in* req_addr_;
	public:
		//TcpCli();
		TcpCli(uv_loop_t* loop_pts);
		~TcpCli();
		static void OnConnection(uv_connect_t *req, int status);
		
};
#endif

