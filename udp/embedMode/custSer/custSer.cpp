#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
#include<sys/types.h>
using namespace std;

int ifExePro(pid_t status){
	
	if(status==-1){
		
		cout<<"system error!"<<endl;
		return -1;
	}else{
		
		cout<<"exit status values:"<<status<<endl;
		if(WIFEXITED(status)){
			if(WEXITSTATUS(status)){
				cout<<"program success!"<<endl;
				return 0;
				
			}else{
				
				cout<<"program return fail"<<endl;
				return -1;
			}
			
		}else{
			
			cout<<"exit status="<<WIFEXITED(status)<<endl;
			return -1;
		}
		
	}	
	
	
}

int main(int argc,char* argv[])
{
	pid_t status;
	char program[200]="/tmp/client/ecli 127.0.0.1 8888";
	while(1){
		status=system(program);
		if(ifExePro(status)!=0)
			cout<<"fail!!!"<<endl;
		usleep(1000000);//microseconds
	}
	return 0;
	
}
