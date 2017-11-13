#ifndef SRCJSON_H_
#define SRCJSON_H_

#include "../include/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int readConf(const char* file_name,const char* obj,const char* child_obj ,char* back);

#endif