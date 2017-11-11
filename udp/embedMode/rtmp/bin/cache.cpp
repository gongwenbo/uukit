#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cache.h"

#include <deque>
#include <mutex>
static std::deque<Cache> cache;
std::mutex queue_mutex; // 队列互斥锁

int cache_free()
{
	for(std::deque<Cache>::iterator it=cache.begin(); it!=cache.end(); ++it){
		if(it->data != NULL)
		free(it->data);
	}
}

int cache_push(unsigned char *ptr, int size)
{
	if(size == 0) return 0;
	
	if(cache.size() < Cache_Num){
		//分配缓存空间
		Cache buff;
		buff.pos = 0;
		buff.size = size;
		buff.data = (unsigned char *)malloc(size);
		memset(buff.data, 0, size);
		memcpy(buff.data, ptr, size);
		
		//拿锁
		std::unique_lock<std::mutex> lock(queue_mutex);
		cache.push_back(buff);
	}
	else{			
		//分配缓存空间
		Cache buff;
		buff.pos = 0;
		buff.size = size;
		buff.data = (unsigned char *)malloc(size);
		memset(buff.data, 0, size);
		memcpy(buff.data, ptr, size);
		
		//拿锁
		std::unique_lock<std::mutex> lock(queue_mutex);
		cache.pop_front();
		cache.push_back(buff);
	}
	return cache.size();
}

int cache_poll(unsigned char *ptr, int size)
{	
	int timeout = 20; 
	unsigned int poll_size = 0;
	
	if(cache.size() == 0)
	return poll_size;

#define out cache.front()
	//取队列首元素
	//Cache out = cache.front();
	//printf("######00: %d %d        %d         %d\n", out.size,out.pos,  poll_size, size);
	while(out.size - out.pos < size - poll_size)
	{
		memcpy(ptr + poll_size, out.data + out.pos, out.size - out.pos);
		poll_size += out.size - out.pos;
		
		//拿锁
		queue_mutex.lock();
		cache.pop_front();
		queue_mutex.unlock();
		
		
		while(out.size == 0)
		{
			if(cache.size() == 0)
			{
				if(timeout--)
				{
				usleep(100 * 1000);
				continue;
				//return poll_size;
				}
			}
		
			
			//拿锁
			queue_mutex.lock();
			cache.pop_front();
			queue_mutex.unlock();
		}
		
		if(cache.size() == 0)
			usleep(100 * 1000);
			//return poll_size;
	}
	
	if(out.size - out.pos == size - poll_size)
	{
		memcpy(ptr + poll_size, out.data + out.pos, size - poll_size);
		
		//拿锁
		std::unique_lock<std::mutex> lock(queue_mutex);
		cache.pop_front();
		
		return size;
	}
	else if(out.size - out.pos > size - poll_size)
	{
		memcpy(ptr + poll_size, out.data + out.pos, size - poll_size);
		
		//拿锁
		std::unique_lock<std::mutex> lock(queue_mutex);
		cache.front().pos += size - poll_size;
		
		return size;
	}
}

