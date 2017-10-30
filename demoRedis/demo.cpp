#include<hiredis/hiredis.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

void testRedis(string IP,int port,struct timeval timeout);

int main(int argc,char* argv[])
{
	struct timeval timeout={2,0};
	testRedis((string)argv[1],atoi(argv[2]),timeout);
	

}

void testRedis(string IP,int port,struct timeval timeout){

	redisContext *pRedisContext=(redisContext*)redisConnectWithTimeout(IP,port,timeout);
	if((pRedisContext==NULL)||(pRedisContext->err)){

		if(pRedisContext){

			cout<<"connect error:"<<pRedisContext-err<<endl;

		}
		else{
			cout<<"connect error:can not allocate redis context"<<endl;

		}
		return -1;
	}

	redisReply *pRedisReply=(redisReply*)redisCommand(pRedisContext,"INFO");
	cout<<"INFO:"<<pRedisReply->str<<endl
	freeReplyObject(pRedisReply);
};
