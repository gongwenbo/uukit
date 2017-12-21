#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis/hiredis.h>
#include <iostream>
#include <unistd.h>
using namespace std;

redisContext* intialConnecRedis(){
	   
    redisContext *c;
    const char *hostname = "127.0.0.1";
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

int updateDevTTL(redisContext *c,char* key){
	
	redisReply *reply;
	reply = (redisReply *)redisCommand(c,"expire %s 20",key);
    printf("return: %s\n", reply->str);
    freeReplyObject(reply);
	return 0;	
	
}

int updateDevStatus(redisContext *c,char* key,char* feild,char* values)
{
	redisReply *reply;
	char command[50];
	sprintf(command,"hset %s %s %s",key,feild,values);
	reply = (redisReply *)redisCommand(c,command);
    printf("return: %s\n", reply->str);
    freeReplyObject(reply);
	return 0;
	
}

int readDevStatus(redisContext *c,char* key,char* feild)
{
	redisReply *reply;
	char command[50];
	sprintf(command,"hget %s %s",key,feild);
	reply = (redisReply *)redisCommand(c,command);
    printf("return status : %s\n", reply->str);
    freeReplyObject(reply);
	return 0;
	
}

int switchDatebase(redisContext *c,char* dateName){
	
	redisReply *reply;
	char command[50];
	sprintf(command,"select %s",dateName);
	reply = (redisReply *)redisCommand(c,command);
    printf("switchDatebase : %s\n", reply->str);
    freeReplyObject(reply);
	return 0;
	
	
	
}

int updateDevInfo(redisContext *redisHandel){
	redisReply *reply;
	redisAppendCommand(redisHandel,"SET foo bar");
	redisAppendCommand(redisHandel,"GET foo");
	
	redisGetReply(redisHandel,(void**)&reply); // SET命令的返回
	cout<<"SET foo bar:"<<reply->str<<endl;
	freeReplyObject(reply);
	
	redisGetReply(redisHandel,&reply); // GET命令的返回
	cout<<"GET foo"<<reply->str<<endl;
	freeReplyObject(reply);
	
	
}
int main(int argc, char **argv) {

	redisContext *connecRedis=intialConnecRedis();
	
	while(1){
		
	//switchDatebase(connecRedis,"0");
		
	//updateDevStatus(connecRedis,"id","status","test");
	
	//updateDevTTL(connecRedis,"id");
	
	updateDevInfo(connecRedis);
	
	sleep(5);
	
	readDevStatus(connecRedis,"id","status");

    
	}
    /* Disconnects and frees the context */
	redisFree(connecRedis);
	

    return 0;
}