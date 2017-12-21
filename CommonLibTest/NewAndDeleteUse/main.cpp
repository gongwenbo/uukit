#include "common.h"
using namespace std;
int main(int argc,char** argv){
	
	char* c_test=new char[100];
	//fill(c_test,c_test+100,1);
	sprintf(c_test,"hello");
	//char* c_test1=new char[100]("hello world!!");
	int* i_test=new int(12);
	cout<<"c_test:"<<c_test<<endl;
	//cout<<"c_test1"<<c_test1<<endl;
	cout<<"i_test"<<*i_test<<endl;
	cout<<"delete resource"<<endl;
	delete[] c_test;
	delete i_test;
		
}