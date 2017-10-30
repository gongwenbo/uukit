#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ev.h>

#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <unistd.h>

#define DEFAULT_PORT    3333
#define BUF_SIZE        4096

int sd; // socket descriptor
int addr_len = sizeof(addr);
char buffer[BUF_SIZE];

static void udp_cb(EV_P_ ev_io *w, int revents);
void configUdp(struct sockaddr_in &ipAddrs,int port,int &fd);
void evOpere();

int main(int argc,char* )
{
	struct sockaddr_in addr;
	int fd;
	configUdp(addr,DEFAULT_PORT,fd);
	
	
	
}


static void udp_cb(EV_P_ ev_io *w, int revents) {
    puts("udp socket has become readable");
    socklen_t bytes = recvfrom(sd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*) &addr, (socklen_t *) &addr_len);

    buffer[bytes] = '\0';

    printf("udp client said: %s", buffer);
 
    sendto(sd, buffer, bytes, 0, (struct sockaddr*) &addr, sizeof(addr));
}

void configUdp(struct sockaddr_in &ipAddrs,int port,int &fd){
	
	struct sockaddr_in addr;
	
	sd = socket(PF_INET, SOCK_DGRAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sd, (struct sockaddr*) &addr, sizeof(addr)) != 0)
        perror("bind");
	
	ipAddrs=addr;
	fd=sd;
};

void evOpere(){
	struct ev_loop *loop = ev_default_loop(0);
    ev_io udp_watcher;
    ev_io_init(&udp_watcher, udp_cb, sd, EV_READ);
    ev_io_start(loop, &udp_watcher);
    ev_loop(loop, 0);
	
};




