#pragma once
#include "common.h"
using namespace std;
class ThreadPool{
	public:
		ThreadPool(uint32_t thread_num){
			for(uint32_t i=0;i<thread_num;i++){
				threads.emplace_back(std::thread([=](){
					std::function<void()> func;
					std::thread::id th_id;
					for(;;){
						std::unique_lock<std::mutex> my_mux(mux);
						cv.wait(my_mux,[](){return 1;});
						if(tasks_.empty())
							continue;
						func=tasks_.front();
						tasks_.pop_front();
						my_mux.unlock();
						func();
						th_id=std::this_thread::get_id();
						cout<<th_id<<"\n";
						
					}					
					
				}));

				
			}
		};
		~ThreadPool(){
			for(auto& i:threads){
				i.join();
			}
		}
		template<class F,class... ARG>
		auto AddTask(F&& f,ARG&&... args)->
			std::future<typename std::result_of<F(ARG...)>::type>
		{
			using ret_type=typename std::result_of<F(ARG...)>::type ;
			auto task_add=std::make_shared<std::packaged_task<ret_type()>>(
				std::bind(std::forward<F>(f),std::forward<ARG>(args)...)
			);

				
				std::future<ret_type> ret=task_add->get_future();
			
			{
				std::lock_guard<std::mutex> loc(mux);
				tasks_.emplace_back([=](){
					(*task_add)();
				});
				
			}
			cv.notify_one();
			
			return ret;
			
		}
				
	public:
		std::deque<std::function<void()>> tasks_;
		std::vector<std::thread> threads;
		std::mutex mux;
		std::condition_variable cv;
};

uint32_t AddFun(uint32_t a,uint32_t b);

void TestThreadPool();









