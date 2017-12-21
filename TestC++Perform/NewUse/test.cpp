#include "test.h"
Foo::Foo(std::string sname,int iold){
	iold_=new int(iold);
	sname_=sname;
}
Foo::~Foo(){
	std::cout<<"delete Foo"<<std::endl;
	delete iold_;	
}

void Foo::display(){
			
	std::cout<<"sname_:"<<sname_<<std::endl;
	std::cout<<"iold_:"<<*iold_<<std::endl;
}


