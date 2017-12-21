
#ifndef HASH_RERIS_H
#define HASH_RERIS_H
#include "common.h"
using namespace std;
class redisOperator
{

private:	
	//一个操作redis数据库的句柄
	redisContext *c;
public:	
	redisOperator(void);

	//HDELL 删除key中的一个或者多个域,成功返回删除的个数(返回值可能和num不一致)
	int hashHdel(string& key,const int& num,const char** value);
	
	//HEXISTS 查看哈希表中是否存在给定域,存在返回1 否则 0
	int hashHexists(const string& key,const string& field);
	
	//HGET 返回哈希表 key 中给定域 field 的值。成功返回给定的域,否则NULL
	string hashHget(const string& key,const string& field);
	
	//HGETALL key 返回哈希表 key 中，所有的域和值。
	//成功返回true 否则false
	string hashHgetall(const string& key);
	
	//HINCRYBY为哈希表中的field域的值加上增量
	//返回值:field域的值(出错返回原值,写一条信息到log中)
	int hashHincrby(const string& key,const string& field,unsigned int incr);

	//HINCRBYFLOAT 为哈希表中的field域加上浮点增量incr
	//返回值:field域的值(出错写一条信息到log中)
	string hashHincrbyfloat(const string& key,const string& field ,float incr);

	//HKEYS 返回哈希表key中的所有域
	//不成功返回NULL
	string hashHkeys(const string& key);

	//HLEN 返回哈希表中域的数量
	//成功返回非0值
	int hashHlen(const string& key);

	//HMGET 返回哈希表key中一个或多个给定域的值
	//返回值:一个包含多个给定于的关联值的字符串,不存在的域返回NULL
	string hashHmset(const string& key,const int& num,const char**argc);

	//HMSET 同时将多个field-value对设置到哈希表key中
	void hashHmset(string& key,int num,char** field,char**value);

	//HSET 将哈希表key中的field的值设置为value
	//返回1 表示新建域,返回0 表示新值覆盖旧值
	bool hashHset(string& key,string& field ,const string& value);

	//HSETNX 将哈希表key中的field的值设置为value
	//成功返回1 否则 0
	bool hashHsetnx(string& key,string& field ,const string& value); 
	
	//HVALS 返回哈希表key中所有域的值
	//key不存在返回空
	string hashHvals(const string& key);
	
	string hashHmget(const string& key,const int& num,const char**field);

	//析构函数
	~redisOperator(void);
private:
	redisOperator(const redisOperator&);

};
#endif
