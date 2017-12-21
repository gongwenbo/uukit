#include "hashRedis.h"
#include "common.h"
using namespace std;
redisOperator::redisOperator(void)
{
	const char *hostname = "127.0.0.1";
	int port = 6379;
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout(hostname, port, timeout);
	//cacheHandle handle(c,hostname);
	
	if (c == NULL || c->err)
	{
		if (c)
		{
			printf("Connection error: %s\n",c->errstr);
			redisFree(c);
		}
		else
		{
			cout<<"Connection error: can't allocate redis context\n";
		}
		exit(-1);
	}

}

//HDELL 删除key中的一个或者多个域,成功返回删除的个数(返回值可能和num不一致)
int redisOperator::hashHdel(string& key,const int& num,const char** value)
{
	int tmp = 0;
	redisReply *reply;
	for(int i= 1 ;i < num;i++)
	{
		reply = (redisReply*)redisCommand(c,"HDEL %s %s",key.c_str(),value[i]);
		if(reply->type == REDIS_REPLY_INTEGER)
			tmp += reply -> integer;
	}
	freeReplyObject(reply);
	return tmp;	
}

//HEXISTS 查看哈希表中是否存在给定域,存在返回1 否则 0
int redisOperator::hashHexists(const string& key,const string& field)
{
	int tmp = 0;
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HEXISTS %s %s",key.c_str(),field.c_str());
	if(reply->type == REDIS_REPLY_INTEGER)
		tmp = reply->integer;
	freeReplyObject(reply);
	return tmp;
}

//HGET 返回哈希表 key 中给定域 field 的值。成功返回给定的域,否则NULL
string redisOperator::hashHget(const string& key,const string& field)
{
	
	string tmp("");
	redisReply *reply;

	//reply = (redisReply*)redisCommand(c,"HGET %s %s",key.c_str(),field.c_str());
	
	if(reply->type == REDIS_REPLY_STRING)
		tmp = reply->str;
	freeReplyObject(reply);
	return tmp;
}

//HGETALL key 返回哈希表 key 中，所有的域和值。
//成功返回true 否则false
string redisOperator::hashHgetall(const string& key)
{
	string tmp("");
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HGETALL %s ",key.c_str());
	if(reply->type == REDIS_REPLY_ARRAY)
	{
		for(unsigned int j = 0 ; j< reply->elements;j++)
		{  
			tmp += reply->element[j]->str;
			tmp += "\n";
			tmp += hashHget(key,reply->element[j]->str);
			tmp += "\n";
			j++;
		}
		freeReplyObject(reply);
		tmp=tmp.substr(0,tmp.length()-1);		
	}

	return tmp;
}

//HINCRYBY为哈希表中的field域的值加上增量
//返回值:field域的值(出错返回-1,写一条信息到log中)
int redisOperator::hashHincrby(const string& key,const string& field,unsigned int incr)
{
	int tmp = -1;
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HINCRBY %s %s %d",key.c_str(),field.c_str(),incr);
	if(reply->type == REDIS_REPLY_INTEGER)
	{
		tmp=reply->integer;
	}
	else

	freeReplyObject(reply);
	return tmp;
}

//HINCRBYFLOAT 为哈希表中的field域加上浮点增量incr
//返回值:field域的值(出错写一条信息到log中)
string redisOperator::hashHincrbyfloat(const string& key,const string& field ,float incr)
{
	string tmp("");
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HINCRBYFLOAT %s %s %f",key.c_str(),field.c_str(),incr);
	if(reply->type == REDIS_REPLY_STRING)
	{
		tmp=reply->str;
	}

	freeReplyObject(reply);
	return tmp;
}

//HKEYS 返回哈希表key中的所有域
//不成功返回NULL
string redisOperator::hashHkeys(const string& key)
{
	string tmp("");
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HKEYS %s ",key.c_str());
	if(reply->type == REDIS_REPLY_ARRAY)
	{
		for(unsigned int j = 0 ; j< reply->elements;j++)
		{
			tmp += reply->element[j]->str;
			tmp += "\n";
		}
		tmp=tmp.substr(0,tmp.length()-1);
	}

	return tmp;
}

//HLEN 返回哈希表中域的数量
//成功返回非0值
int redisOperator::hashHlen(const string& key)
{
	int tmp = 0;
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HLEN %s ",key.c_str());
	if(reply->type == REDIS_REPLY_INTEGER)
	{
		tmp = reply->integer;
	}
	return tmp;
}

//HMGET 返回哈希表key中一个或多个给定域的值
//返回值:一个包含多个给定于的关联值的字符串,不存在的域不反回
string redisOperator::hashHmget(const string& key,const int& num,const char**field)
{
	string tmp("");
	redisReply *reply;
	for(int i = 0;i< num;i++)
	{
		reply = (redisReply*)redisCommand(c,"HGET %s %s",key.c_str(),field[i]);
		if(reply->type == REDIS_REPLY_STRING)
		{
			tmp += reply->str;
			tmp += "\n";
		}
		freeReplyObject(reply);
	}
	tmp = tmp.substr(0,tmp.length()-1);
	return tmp;
}

//HMSET 同时将多个field-value对设置到哈希表key中
void redisOperator::hashHmset(string& key,int num,char**field,char**value)
{
	redisReply *reply;
	for(int i= 0 ;i < num;i++)
	{
		reply = (redisReply*)redisCommand(c,"HSET %s %s %s",key.c_str(),field[i],value[i]);
		if(reply->type == REDIS_REPLY_ERROR)
		{
			//错误处理
			cout<<"an err occur"<<endl;
			abort();
		}
		freeReplyObject(reply);
	}
}

//HSET 将哈希表key中的field的值设置为value
//返回1 表示新建域,返回0 表示新值覆盖旧值
bool redisOperator::redisOperator::hashHset(string& key,string& field ,const string& value)
{
	int tmp=0;
	redisReply *reply;
	//reply = (redisReply*)redisCommand(c,"HSET %s %s %s",key.c_str(),field.c_str(),value.c_str());
	reply = (redisReply*)redisCommand(c,"set okk 'kkkkkk'");
	if(reply->type == REDIS_REPLY_INTEGER)
		tmp += reply -> integer;
	freeReplyObject(reply);
	return tmp!=0?true:false;
}

//HSETNX 将哈希表key中的field的值设置为value
//成功返回1 否则 0
bool redisOperator::hashHsetnx(string& key,string& field ,const string& value) 
{
	int tmp=0;
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HSETNX %s %s %s",key.c_str(),field.c_str(),value.c_str());
	if(reply->type == REDIS_REPLY_INTEGER)
		tmp += reply -> integer;
	freeReplyObject(reply);
	return (tmp!=0?true:false);
}

//HVALS 返回哈希表key中所有域的值
//key不存在返回空
//NOTE 该函数测试未通过
string redisOperator::hashHvals(const string& key)
{
	string tmp("");
	redisReply *reply;
	reply = (redisReply*)redisCommand(c,"HGETALL %s ",key.c_str());
	if(reply->type == REDIS_REPLY_ARRAY)
	{
		for(unsigned int j = 0 ; j< reply->elements;j++)
		{  
			tmp += hashHget(key,reply->element[j]->str);
			tmp += "\n";
			j++;
		}
		freeReplyObject(reply);
		tmp=tmp.substr(0,tmp.length()-1);		
	}
	return tmp;
}

//析构函数
redisOperator::~redisOperator(void)
{
	redisFree(c);
}
redisOperator::redisOperator(const redisOperator&)
{
}
