#include "test.h"

void test_strsep(std::string& str){
	
	char *fonud;
	char *tem=new char[strlen(str.c_str())+1];
	strcpy(tem,str.c_str());
	
	std::cout<<"test_strsep begin"<<std::endl;
	while((fonud=strsep(&tem," "))!=NULL){
		
		std::cout<<fonud<<std::endl;
		
		
	}	
	delete tem;
}