#include "test.h"
int main(int argc,char** argv){
	
	Foo *obja=new Foo("obja",0);
	Foo *objb=new Foo("objb",1);
	obja->display();
	objb->display();
	delete obja;
	delete objb;
	
}

