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
#include "socket_uv.h"
#include "log.h"

//mysql head_file
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


extern uv_loop_t* loop;


#endif
