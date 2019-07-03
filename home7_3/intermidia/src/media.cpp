#include "media.h"
void ReadLight::Handle(){
	cout<<"ReadLight \n";
	traffic_lit_->state_=new GreeLight(this->traffic_lit_);
}
void GreeLight::Handle(){
	cout<<"GreenLight \n";
	traffic_lit_->state_=new ReadLight(this->traffic_lit_);
}