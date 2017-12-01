#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include <uv.h>
#include <stdarg.h>
#include <iostream>
#include <unistd.h>
#include "run.h"
#include "log.h"



#define PORT 8888//server port  

//#define socketaddr struct sockaddr_in;

extern uv_loop_t* loop;
extern uv_work_t req_work;

#endif

