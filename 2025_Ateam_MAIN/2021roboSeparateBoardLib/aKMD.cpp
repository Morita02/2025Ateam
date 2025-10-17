#include "aKmd.hpp"
#include "useful.hpp"

namespace rob{

float aKMD::setForce(const float v){
	setShutdown(false);
	return set(v);
}

float aKMD::set(float v){
	const float max=0.97;
	if(v<-max){
		v=-max;
	}else if(v>max){
		v=max;
	}
	if(v<0.0){
		pwm1=-v;
		pwm2=0.0;
	}else{
		pwm1=0.0;
		pwm2=v;
	}
	return v;
}

uint32_t aKMD::freq(const uint32_t f){
	const int t=1000000/f;
	pwm1.period_us(t);
	pwm2.period_us(t);
	return f;
}

bool aKMD::setShutdown(const bool v){
	out3=!v;
	return v;
}

}//namespace rob