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
 
    redisContext *context = redisConnect("127.0.0.1", 6379);//默认端口，本机redis-server服务开启
    if(context->err) {
        redisFree(context); 
        printf("connect redisServer err:%s\n", context->errstr);
     
    } 
	return context;
}

int update_ttl(redisContext *context,char* key){
	
	char command[50];
	sprintf(command,"expire %s 120",key);
	
	redisReply *reply = (redisReply *)redisCommand(context, command);

    if(NULL == reply) {
        printf("command execute failure\n");
        redisFree(context);
        return -1;
    }
	else return 0;
	
	
}

int exeRedis(redisContext *c,char* COMD,int flag )
{
	
	redisReply *reply;
	sprintf(COMD,"get kkk");
    reply = (redisReply*)redisCommand(c,"get kkk");
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
	
	if(flag==1)  //1 echo 0 no printf
    printf("RETURN: %s\n", reply->str);
	//strcpy(_return,reply->str);
	freeReplyObject(reply);
	//redisFree(c);
	return 0;
}