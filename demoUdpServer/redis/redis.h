#ifndef REDIS_H
#define REDIS_H
#include "common.h"

using namespace std;
int hashHdel(char* key,char* field,char* result);
int hashHget(char* key,char* field,char* result);
int hashHset(char* key,char* field,char* values,char* result);
redisContext* InitRedis();
int exeRedis(redisContext *c,char* COMD,int flag );
int update_ttl(redisContext *context,char* key);

#endif