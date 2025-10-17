#include "mbed.h"
#include "mu3.h"
#include "IM920.hpp"
#include "2021roboSeparateBoardLib_setting.hpp"
#include <cstdlib>
#include <algorithm>
#include <cmath>



/*
   0   3
   
   1   2
*/
mu3 mu3a;

//DigitalOut emergency(PC_0);

DigitalIn Limit1(PA_13);
DigitalIn Limit2(PA_14);

Serial tombed(PB_6, PB_7);//ピンヘッダの方
//Serial tombed(PA_0, PA_1);//ピンソケットの方

char direction  = 'n';
char recievedata[64];
int16_t lx_v = 300, ly_v = 300, rx_v = 300, ry_v = 300; //受信してないときの適当な値
float lx=0.0, ly=0.0, rx=0.0, ry=0.0;



int receive_count = 0;

const int16_t STICK_MIN_VALUE = 0;
const int16_t STICK_MAX_VALUE = 255;
const float DEADZONE = 12.0f; //-128~128の範囲のときのデッドゾーン

const float PPR = 2048;


//新MD
class Motor{
private:
	PwmOut pwm1, pwm2;
	bool isReverse;
public:
	Motor(PinName pin1, PinName pin2, bool isReverseArg):
	pwm1(pin1), pwm2(pin2), isReverse(isReverseArg){
		freq(2000);
	}
	float set_power(float power){
		const float max = 1.0;
		if(isReverse)power*=(-1.0f);
		
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
		//int i;

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

void getC(const uint8_t* data)
{

	
	//pc.printf("%s\n",data);
	
	//でばっぐ
	/*
	int i;
	for(i = 0; i< 9; i++) {
		pc.printf("%x", data[i]);
		pc.printf(" ");
	}
	pc.printf("\n");
	*/
	//ボタン,lx下位,lx上位,ly下位,ly上位,rx下位,rx上位,ry下位,ry上位の順(合計9byte)
	if(receive_count < 10) {
		receive_count++;
	} else {
		/*
		for(i = 0; i< 9; i++) {
			pc.printf("%x", data[i]);
			pc.printf(" ");
		}
		pc.printf("\n");
		*/
		direction = data[0];
		lx_v = static_cast<int16_t>(static_cast<uint8_t>(data[1]) | (static_cast<uint8_t>(data[2]) << 8));
		ly_v = static_cast<int16_t>(static_cast<uint8_t>(data[3]) | (static_cast<uint8_t>(data[4]) << 8));
		rx_v = static_cast<int16_t>(static_cast<uint8_t>(data[5]) | (static_cast<uint8_t>(data[6]) << 8));
		ry_v = static_cast<int16_t>(static_cast<uint8_t>(data[7]) | (static_cast<uint8_t>(data[8]) << 8));
		
	}
	
	
	//でばっぐ
	//pc.printf("%c, %d, %d, %d, %d", direction, lx_v, ly_v, rx_v, ry_v);
	//pc.printf("\n");
	
		
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
		
	}
	*/
}

void getMbed() {}

void sendMbed() {
	char buf[2];
	
	buf[0] = direction;
	if(ly == 1.0f)
		buf[1] = 'q';
	else if(ly == -1.0f)
		buf[1] = 'e';
	else
		buf[1] = 'z';
	//pc.printf("%c%c\n",buf[0],buf[1]);
	tombed.printf("%c%c", buf[0],buf[1]);
	
}
float stick_normalize(int16_t raw_val) {
	float value = static_cast<float>(raw_val);
	
	if(value > 255.0f) value = 127.5f;
	
	float out_val = ((value - 127.5f) / 127.5f);
	
	if(fabs(out_val) < (DEADZONE / 127.5f)) out_val = 0.0f;
	
	
	/*
	//0～255の値を-128～128の範囲に直す
	value -= ((STICK_MAX_VALUE - STICK_MIN_VALUE) / 2.0f);
	
	// デッドゾーンの実装
	if (fabs(value) < DEADZONE) value = 0.0f;
	
	return value;
	*/
	return out_val;
}

//rob::aRotaryEncoder &Encoder = rob::rotaryEncoder2;


Motor motor1(PB_4,PC_8,false);
Motor motor2(PC_9,PB_8,false);
Motor motor3(PB_3,PA_10,false);
Motor motor4(PB_10,PB_5,false);
Motor motor5(PA_11,PB_2,false);

Motor* motor_array[4] = {&motor1, &motor2, &motor3, &motor4};

Omuni omni(motor_array, 4);
//rob::aRohmMD &motor5=rob::motor5;
//rob::aRohmMD &motor6=rob::motor6;
//DigitalOut remote_stop(PC_0);
// DigitalOut myled(LED1);
regularC_ms test(50);

int main(){
	
	bool isPress1 = false;
	bool isPress2 = false;
	pc.baud(9600);
	pc.attach(getCmc,Serial::RxIrq);
	pc.printf("hello\n");
	wait_ms(1000);
	mu3serial.baud(19200);
	mu3a.set(15,110,2,1);//ch,groupID,myNum,sendNum 1から254までで適当に決める。相手と合わせる。
	mu3a.attach(getC);
	
	
	mu3serial.printf("@rc");
	mu3serial.printf("\r\n");
	mu3a.setup();
	
	tombed.baud(115200);
	tombed.attach(getMbed, Serial::RxIrq);
	
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
	//emergency = 1;
	while(true){
		static rob::regularC_ms printTime(100);
		
		
		// lx = stick_normalize(lx_v);
		ly = -stick_normalize(ly_v);
		rx = stick_normalize(rx_v);
		// ry = -stick_normalize(ry_v);
		
		sendMbed();
		
		rx *= 0.5;
		
		if(Limit1) {
			isPress1 = false;
		} else {
			isPress1 = true;
		}
		
		if(Limit2) {
			isPress2 = false;
		} else {
			isPress2 = true;
		}
		
		//pc.printf("%f, %f, %f, %f\n", lx, ly, rx, ry);
		
		// if(printTime){
			// pc.printf("%d, %d\n",isPress1 , isPress2);
			
			// pc.printf("%f, %f, %f, %f\n", lx, ly, rx, ry);
			
		// }
		
		
		
		
		
		switch(direction){
			case 'i':
				if(!isPress1) {
					motor5 = -0.5;//これ展開
				} else {
					motor5 = 0.0;
				}
				break;
			
			case 'o':
				// motor5 = 0.8;
				if(!isPress2) {
					motor5 = 0.5;//これ閉廷
				} else {
					motor5 = 0.0;
				}
				break;
			case 'w':
				motor1 = 0.5;
				motor2 = -0.5;
				motor3 = -0.5;
				motor4 = 0.5;
				motor5 = 0.0;
				//x = 1;
				//omni.move(0.0, 0.0, 0.0);
				
				break;
			
			case 's':
				motor1 = -0.5;
				motor2 = 0.5;
				motor3 = 0.5;
				motor4 = -0.5;
				motor5 = 0.0;
				
				break;
			
			case 'a':
				motor1 = 0.5;
				motor2 = 0.5;
				motor3 = -0.5;
				motor4 = -0.5;
				motor5 = 0.0;
				
				break;
			case 'd':
				motor1 = -0.5;
				motor2 = -0.5;
				motor3 = 0.5;
				motor4 = 0.5;
				motor5 = 0.0;
				break;
			case 'n':
				
				omni.move(0.0,0.0,rx);
				
				motor5 = 0.0;
				break;
			default:
				motor1 = 0.0;
				motor2 = 0.0;
				motor3 = 0.0;
				motor4 = 0.0;
				motor5 = 0.0;
				break;
		}
		
		
		
	}

    return 0;
}