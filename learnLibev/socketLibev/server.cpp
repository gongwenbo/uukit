#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ev.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <unistd.h>  // problem solved! it compiles!

#define PORT 9000
#define IP "127.0.0.1"

int create_socket(); 
void accept_socket_cb(struct ev_loop *loop,ev_io *w, int revents);
void recv_socket_cb(struct ev_loop *loop,ev_io *w, int revents);
void write_socket_cb(struct ev_loop *loop,ev_io *w, int revents);


int main(int argc, char *argv[])
{
    int s = create_socket();
    if(s < 0){
        return -1;
    }

    ev_io ev_io_watcher;
    struct ev_loop *loop = ev_loop_new(EVBACKEND_EPOLL);

    ev_io_init(&ev_io_watcher, accept_socket_cb,s, EV_READ);
    ev_io_start(loop,&ev_io_watcher); 
    ev_loop(loop,0);
    ev_loop_destroy(loop);

    return 0;
}


int create_socket()
{
    struct sockaddr_in addr;
    int s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s == -1){
        perror("create socket error \n");
        return -1;
    }

    int so_reuseaddr = 1;
    setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&so_reuseaddr,sizeof(so_reuseaddr));
    bzero(&addr, sizeof(addr));
    addr.sin_family = PF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);

    if(bind(s, (struct sockaddr *) &addr, sizeof(struct sockaddr))== -1){
        perror("bind socket error \n");
        return -1;
    }


    if(listen(s,32) == -1){
        perror("listen socket error\n");
        return -1;
    }

    printf("bind %s,listen %d \n",IP,PORT);

    return s;
}


void accept_socket_cb(struct ev_loop *loop,ev_io *w, int revents)
{
    int fd; 
    int s = w->fd;
    struct sockaddr_in sin;
    socklen_t addrlen = sizeof(struct sockaddr);
    do{
        fd = accept(s, (struct sockaddr *)&sin, &addrlen);
        if(fd > 0){
            break;
        }

        if(errno == EAGAIN || errno == EWOULDBLOCK){
            continue;
        }
    }while(1);

    ev_io* accept_watcher = (ev_io*)malloc(sizeof(ev_io));

    memset(accept_watcher,0x00,sizeof(ev_io));

    ev_io_init(accept_watcher,recv_socket_cb,fd,EV_READ);
    ev_io_start(loop,accept_watcher);
}

#define MAX_BUF_LEN  1024
void recv_socket_cb(struct ev_loop *loop,ev_io *w, int revents)
{
    char buf[MAX_BUF_LEN] = {0};
    int ret = 0;

    do{
        ret = recv(w->fd,buf,MAX_BUF_LEN - 1, 0);

        if(ret > 0){
            printf("recv message:\n'%s'\n",buf);
            ev_io_stop(loop,  w);
            ev_io_init(w,write_socket_cb,w->fd,EV_WRITE);
            ev_io_start(loop,w);
            return;
        }

        if(ret == 0){
            printf("remote socket closed \n");
            break;
        }

        if(errno == EAGAIN ||errno == EWOULDBLOCK){
            continue;
        }
        break;
    }while(1);

    close(w->fd);
    ev_io_stop(loop,w);
    free(w);
}


void write_socket_cb(struct ev_loop *loop,ev_io *w, int revents)
{
    char buf[MAX_BUF_LEN] = {0};

    snprintf(buf,MAX_BUF_LEN - 1, "this is test message from libev \n");

    write(w->fd,buf,strlen(buf));

    ev_io_stop(loop,  w);
    ev_io_init(w,recv_socket_cb,w->fd,EV_READ);
    ev_io_start(loop,w);
}