#ifndef A_KMD_HPP_INCLUDE_GUARD
#define A_KMD_HPP_INCLUDE_GUARD
#include "mbed.h"

namespace rob{
	
//後でインターフェースを書こう！！

class aKMD{
	private:
	PwmOut pwm1,pwm2;
	DigitalOut out3;
	
	//pwmのチャンネルをまたいでいるので勝手に変更した場合の動作を保証できないためprivate
	uint32_t freq(const uint32_t f);
	
	public:
	aKMD(const PinName pinPwm1,const PinName pinPwm2,const PinName pinOut3):
		pwm1(pinPwm1),pwm2(pinPwm2),out3(pinOut3)
	{
		freq(2000);	
	}
	
	//強制的に出力する
	float setForce(const float v);
	
	//出力するがシャットダウンしている場合は出力しない
	float set(float v);
	
	//シャットダウンするかどうかをtrueかfalseで指定する
	bool setShutdown(const bool v);
	
	float operator=(const float v){
		return setForce(v);
	}
};


}//namespace rob



#endif