#include "common.h"
#include "redis.h"

//hash 
using namespace std;
int hashHdel(char* key,char* field,char* result){
	
	int n=sprintf(result,"hdel %s %s",key,field);
	if(n<0)
		return -1;
	else	
		return 0;
	
}
int hashHget(char* key,char* field,char* result){
	
	int n=sprintf(result,"hget %s %s",key,field);
	if(n<0)
		return -1;
	else	
		return 0;
} 
int hashHset(char* key,char* field,char* values,char* result){
	int n=sprintf(result,"hset %s %s '%s'",key,field,values);
	if(n<0)
		return -1;
	else
		return 0;
}

redisContext* InitRedis(){
 
	redisContext *c;
    const char *hostname =  "127.0.0.1";
    int port = 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
	return c;
}

int exeRedis(redisContext *c,char* COMD )
{
	
	redisReply *reply;
    reply = (redisReply*)redisCommand(c,COMD);
	if (reply == NULL)  
	{  
		printf("Get Data failed\n");  
		redisFree(c);  
		return -1;
	}  
	if (reply->type != REDIS_REPLY_STRING)  
	{  
		cout<<"REDIS_REPLY_STRING error!"<<endl;
		freeReplyObject(reply);  
		return -1;
	}
	
    printf("RETURN: %s\n", reply->str);
    freeReplyObject(reply);
	//redisFree(c);
	return 0;
}