#pragma once
#include "common.h"
using namespace std;
class TrafficLight;
class GreeLight;
class Istate{
	public:
		Istate(TrafficLight* light){
			traffic_lit_=light;
		}
		virtual void Handle()=0;
		TrafficLight* traffic_lit_;		
};

class ReadLight:public Istate {
	public:
		ReadLight(TrafficLight* light):Istate(light){}
		void Handle();
};

class GreeLight:public Istate{
	public:
		GreeLight(TrafficLight* light):Istate(light){}
		void Handle();	
		
};
class TrafficLight{
	public:
		TrafficLight(){
			state_=new ReadLight(this);
		}
		void Request(){
			state_->Handle();
		}
		Istate* state_;
};


