#include <iostream>  
#include <string>  
#include <stdio.h>  
#include <hiredis/hiredis.h>  
#include <sys/time.h>  
#include <time.h>  
using namespace std;  
  
char *m_szRedisHost="127.0.0.1";  //redis地址  
uint16_t m_iRedisPort=6379;  //redis端口  
int timeout=4000000; //超时时间  
//struct timeval redisTimeout;  
struct timeval redisTimeout = {2, 0};    //2s的超时时间
//redisTimeout.tv_sec=2;  
//redisTimeout.tv_usec=0;  
  
bool RedisConnectWithTimeout(redisContext* redis_context)  
{  
    if (redis_context != NULL)  
    {  
        redisFree(redis_context);  
    }  
    redis_context = redisConnectWithTimeout(  
                            m_szRedisHost,  
                            m_iRedisPort,  
                            redisTimeout);  
    if (redis_context == NULL or redis_context->err)  
    {  
        printf("Connect to redisServer faile\n");  
        return false;  
    }  
    if (redisSetTimeout(redis_context, redisTimeout) != REDIS_OK)  
    {  
        printf("Connect to redisServer time out\n");  
        return false;  
    }  
    return true;  
}  
void GetData(redisContext* redis_context,string &strUserId,string &result)  
{  
    redisReply *reply;  
    string strCommand = "HGET user_" + strUserId;  
    reply = static_cast<redisReply*>(redisCommand(redis_context, strCommand.c_str()));  
    if (reply == NULL)  
    {  
        printf("Get Data failed\n");  
        redisFree(redis_context);  
        return;  
    }  
    if (reply->type != REDIS_REPLY_STRING)  
    {  
        freeReplyObject(reply);  
        return;  
    }  
    result = string(reply->str, reply->len);  
    freeReplyObject(reply);  
}  
int main()  
{  
    redisContext* redis_context;  
    string userId = "01";  
    string result;  
    if (RedisConnectWithTimeout(redis_context))  
    {  
        GetData(redis_context,userId,result);  
    }  
    return 0;  
} 