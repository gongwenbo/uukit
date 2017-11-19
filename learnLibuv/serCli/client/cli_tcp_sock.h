#ifndef CLI_TCP_SOCK_H
#define CLI_TCP_SOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <iostream>
#include <stdarg.h>
#include <unistd.h>

extern uv_work_t req_work;
extern uv_loop_t *loop;



int debug(const char* f,const int l,const char *format,...);
void echo_read(uv_stream_t *server, ssize_t nread, const uv_buf_t* buf);
void alloc_buffer(uv_handle_t *h, size_t size, uv_buf_t *buf);
void on_write_end(uv_write_t *req, int status);
void AfterWork(uv_work_t *req,int status);
void DataRS(uv_work_t *req);
void on_connect(uv_connect_t *req, int status);
void timer_cb(uv_timer_t* handle);


#endif







