#include "test.h"
#include <cstring>
using namespace std;
int main(int argc,char** argv){
	
	std::string str_test("hello world !");
	str_test.append(" iphone se");	
    test_strsep(str_test);
	
	//assign
	str_test.assign("add new contest! ");
	str_test.push_back('c');
	test_strsep(str_test);
	
	//copy
	char *buffer=new char[str_test.length()];
	std::size_t copy_num=str_test.copy(buffer,str_test.length()-1,0);
	cout<<"copy_num->"<<copy_num<<endl;
	std::cout<<"copy from str_test:"<<buffer<<std::endl;
	delete buffer;
	
	//insert 
	string insert_test_buffer("insert test");
	str_test.insert(str_test.length()-1,insert_test_buffer);
	cout<<"insert_test:"<<str_test<<endl;
	
	return 0;
	
}