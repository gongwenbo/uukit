#include "common.h"
#include "media.h"
int main(int argc,char** argv){
	//Istate* rlight=new ReadLight();
	auto traffic=std::make_shared<TrafficLight>();
	int i=std::atoi(argv[1]);
	while(i--){
		traffic->Request();
	}
	
}