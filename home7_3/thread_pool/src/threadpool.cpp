#include "threadpool.h"
void TestThreadPool(){
	auto Run=std::make_shared<ThreadPool>(4);
	std::deque<std::future<uint32_t>> rets;
	for(int i=0;i<10;i++){
		rets.emplace_back(Run->AddTask(std::move(AddFun),i,i+10));
	}
	for(auto& i:rets){
		cout<<i.get()<<"\n";
	}
		
}

uint32_t AddFun(uint32_t a,uint32_t b){
	usleep(1000);
	return (a+b);
}