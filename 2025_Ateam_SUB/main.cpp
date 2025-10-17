#include "mbed.h"


#include "2021roboSeparateBoardLib_setting.hpp"

Serial pc(USBTX,USBRX);
Serial tombed(PA_0, PA_1);

char button  = 'n';
char ly_val = 0;

const float power = 0.5;
const float half_power = 0.25;
const float PPR = 2048;


class Motor{
private:
	PwmOut pwm1, pwm2;
	
public:
	Motor(PinName pin1, PinName pin2):
	pwm1(pin1), pwm2(pin2){
		freq(2000);
	}
	float set_power(float power){
		const float max = 1.0;
		if(power < -max){
			power = -max;
		}
		else if(power > max){
			power = max;
		}
		if(power < 0.0){
			power *= -1.0;
			pwm1 = power;
			pwm2 = 0.0;
		}
		else if(power == 0.0){
			pwm1 = 0.0;
			pwm2 = 1.0;
		}else{
			pwm1 = power;
			pwm2 = 1.0;
		}
		return power;
	}
	float operator=(const float power){
		//pc.printf("%f\n\r",power);
		return set_power(power);
	}
	uint32_t freq(const uint32_t f){
		const int t=1000000/f;
		pwm1.period_us(t);
		pwm2.period_us(t);
		return f;
	}
	
};

class Omuni{
private:

    // 配列でモーターを管理
    Motor** motors;
    int motor_count;
    float motor_max_power = 0.95f;
    const float PI = 3.14159265358979323846f;

    // 出力の計算
    void calculate_outputs(float x, float y, float rotation, float* outputs) {
    // オムニホイール用の出力計算
		float motor_angles[4];

		int i;

		float interval_angle = 360 / motor_count;
		float start_angle = interval_angle / 2 + 90;

		for (i = 0; i < motor_count; i++) {
			motor_angles[i] = start_angle + (i * interval_angle);
		}

		for (i = 0; i < motor_count; i++) {
			// ラジアンに変換
			float angle_rad = motor_angles[i] * PI / 180.0f;

			// 各モーターの出力計算
			outputs[i] =
				x * cos(angle_rad) +
				y * sin(angle_rad) +
				rotation; // マシン中心からWheelまでの距離が一定の場合（一定でない場合要改造）
		}
	}
    // 出力の正規化
    
public:
    // コンストラクタ
    Omuni(Motor* motor_array[], int motor_num) : motor_count(motor_num) {
		for (int i = 1; i < motor_count; i++) {
			if (motor_array[i] == motor_array[0]) {
				std::exit(-1);
			}
		}
		motors = motor_array;
	}
	
	
	void normalize_outputs(float* outputs) {
		// 出力の正規化
		float max_power = 0.6;
		for (int i = 0; i < motor_count; i++) {
			if(max_power < fabs(outputs[i])) {
				max_power = fabs(outputs[i]);
				
			}
			
		}
		
		// 出力を-0.95から0.95の範囲に正規化
		for (int i = 0; i < motor_count; i++) {
			outputs[i] = (outputs[i] / max_power) * motor_max_power;
		}
	}

	void set_motor_outputs(const float* outputs) {
		for (int i = 0; i < motor_count; i++) {
			*motors[i] = outputs[i];
		}
	}
    // 移動制御メソッド
    void move(float x, float y, float rotation) {
		
    // モーター出力を格納する配列 足回り4輪
		float outputs[4];
		int i;

		calculate_outputs(x, y, rotation, outputs);
    // 出力の正規化
		normalize_outputs(outputs);
		
		// for(i = 0; i<4; i++) {
			// pc.printf("%f ", outputs[i]);
		// }
		// pc.printf("\n");
		
    // モーターに出力を設定
		set_motor_outputs(outputs);
	}

};

class regularC_ms{
private:
	unsigned long interval;
	unsigned long nextTime;
	Timer t;
public:
	regularC_ms(unsigned long intervalArg,unsigned long start=0):
	interval(intervalArg)
	{
		t.start();
		nextTime=start;
	}
	bool ist(){
		if(nextTime<(unsigned long)t.read_ms()){
			nextTime=interval+t.read_ms();
			return true;
		}else{
			return false;
		}
	}
	void set(unsigned long val){interval=val;}
	unsigned long read(){return interval;}
	operator bool(){return ist();}
};

class oneshotC_ms{
private:
	bool isActive;
	long nextTime;
	Timer t;
public:
	oneshotC_ms():isActive(false),nextTime(0){
		t.start();
	}
	long fromNowTo(const long wait){
		if(wait>=0){
			nextTime=wait+t.read_ms();
			isActive=true;
		}else{
			isActive=false;
		}
		return wait;
	}
	bool ist(){
		//pc.printf("isActive%s\n",isActive?"true":"false");
		if(isActive){
			return t.read_ms()>=nextTime;
		}
		return false;
	}
	operator bool(){return ist();}
	long operator=(const long wait){
		return fromNowTo(wait);
	}
};

class whileC_ms{
private:
	bool isActive;
	long nextTime;
	Timer t;
public:
	whileC_ms():isActive(false),nextTime(0){
		t.start();
	}
	long fromNowTo(const long wait){
		if(wait>=0){
			nextTime=wait+t.read_ms();
			isActive=true;
		}else{
			isActive=false;
		}
		return wait;
	}
	bool ist(){
		//pc.printf("isActive%s\n",isActive?"true":"false");
		if(isActive){
			return t.read_ms()<nextTime;
		}
		return false;
	}
	operator bool(){return ist();}
	long operator=(const long wait){
		return fromNowTo(wait);
	}
};

void getC()
{	

	button = tombed.getc();
	ly_val = tombed.getc();
	//pc.printf("%c%c\n", button, ly_val);
}

void getCmc()
{
	//pc.printf("%s\n",pc.getc());
    //受信割り込み処理
	/*
    const char receive = pc.getc();
	pc.printf("%c\n",receive);
	if(receive == 'c'){
		if(crawleron){
			crawleron = false;
		}else{
			crawleron = true;
		}
	}else if(receive == 'v'){
		if(slow_move){
			slow_move = false;
		}else{
			slow_move = true;
		}
	}else{	
		button = receive;
	}
	*/
}

Motor motor1(PB_4,PC_8);
Motor motor2(PC_9,PB_8);
Motor motor3(PB_3,PA_10);
Motor motor4(PB_10,PB_5);
// Motor motor5(PA_11,PB_2);

regularC_ms test(50);
int main(){
	
	
	pc.baud(9600);
	pc.attach(getCmc,Serial::RxIrq);
	pc.printf("hello\n");
	wait_ms(1000);
	
	tombed.attach(getC, Serial::RxIrq);
	tombed.baud(115200);
	wait_ms(1000);

	
	// pc.printf("hello\n");
	//rob::xbeeCore.setup();
	/*
	while(1){
		if(test){
			im920.send(&val,1);
		}
	}*/
	// myled=0;
	//This is a test code
	
	while(true){
		static rob::regularC_ms printTime(100);
		
		
		
		switch(button){
				
			case 'l': // L1
				motor2 = -power;
				break;
				
			case 'k': // L2
				motor2 = power;
				break;
				
			case 'p': // バツ
				motor3 = -power;
				break;
			
			case 'h': // サンカク
				motor3 = power;
				break;
				
			case 'r': // R1
				motor4 = -power;
				break;
				
			case 't': // R2
				motor4 = power;
				break;
				
			case 'n':
				if(ly_val == 'q') {
					motor1 = power;
				} else if(ly_val == 'e') {
					motor1 = -power;
				} else {
					motor1 = 0.0;
					motor2 = 0.0;
					motor3 = 0.0;
					motor4 = 0.0;
				}
				break;
			default:
				motor1 = 0.0;
				motor2 = 0.0;
				motor3 = 0.0;
				motor4 = 0.0;
				
				break;
		}
	}

    return 0;
}