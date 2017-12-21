#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
class Foo{
	
	private:
		std::string sname_;
		int* iold_;
	public:
		//Foo();
		Foo(std::string sname,int iold);
		~Foo();
		void display();
	
};

#endif
