#ifndef REDIS_H
#define REDIS_H
#include "common.h"

using namespace std;
void hashHdel(char* key,char* field,char* result);
void hashHget(char* key,char* field,char* result);
void hashHset(char* key,char* field,char* values,char* result);
redisContext* InitRedis();
void exeRedis(redisContext *pRedisContext,char* COMD );

#endif