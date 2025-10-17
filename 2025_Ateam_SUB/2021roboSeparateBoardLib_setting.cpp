#include "2021roboSeparateBoardLib_setting.hpp"


namespace rob{


//									 PWM1,PWM2,OUT3
#define ROBOSEPARATEBOARD_MD1_PINSET PB_4,PC_8,PA_15
#define ROBOSEPARATEBOARD_MD2_PINSET PC_9,PB_8,PD_2
#define ROBOSEPARATEBOARD_MD3_PINSET PB_3,PA_10,PC_2
#define ROBOSEPARATEBOARD_MD4_PINSET PB_10,PB_5,PC_3
#define ROBOSEPARATEBOARD_MD5_PINSET PA_11,PB_2,PB_12

#ifdef ENABLE_motor1_AS_KMD
	aKMD motor1(ROBOSEPARATEBOARD_MD1_PINSET);
#elif defined(ENABLE_motor1_AS_ROHMMD)
	aRohmMD motor1(ROBOSEPARATEBOARD_MD1_PINSET);
#endif

#ifdef ENABLE_motor2_AS_KMD
	aKMD motor2(ROBOSEPARATEBOARD_MD2_PINSET);
#elif defined(ENABLE_motor2_AS_ROHMMD)
	aRohmMD motor2(ROBOSEPARATEBOARD_MD2_PINSET);
#endif

#ifdef ENABLE_motor3_AS_KMD
	aKMD motor3(ROBOSEPARATEBOARD_MD3_PINSET);
#elif defined(ENABLE_motor3_AS_ROHMMD)
	aRohmMD motor3(ROBOSEPARATEBOARD_MD3_PINSET);
#endif

#ifdef ENABLE_motor4_AS_KMD
	aKMD motor4(ROBOSEPARATEBOARD_MD4_PINSET);
#elif defined(ENABLE_motor4_AS_ROHMMD)
	aRohmMD motor4(ROBOSEPARATEBOARD_MD4_PINSET);
#endif

#ifdef ENABLE_motor5_AS_KMD
	aKMD motor5(ROBOSEPARATEBOARD_MD5_PINSET);
#elif defined(ENABLE_motor5_AS_ROHMMD)
	aRohmMD motor5(ROBOSEPARATEBOARD_MD5_PINSET);
#endif


#ifdef ENABLE_rotaryEncoder1
//aRotaryEncoder rotaryEncoder1(PA_11,PA_12,PullDown);
//パッチ修正後
aRotaryEncoder rotaryEncoder1(PC_5,PC_4,PullDown);
//aRotaryEncoder rotaryEncoder1(PC_4,PA_11,PullDown);
#endif

#ifdef ENABLE_rotaryEncoder2
aRotaryEncoder rotaryEncoder2(PA_8,PA_9,PullDown);
#endif

#ifdef ENABLE_imu03a
//mosi miso slck csPin
a_imu03a imu03a(PC_12,PC_11,PC_10,PB_1);
#endif

#ifdef ENABLE_xbeeCore
//tx rx 
aXbeeCoreCallback<VAL_xbeeCore_nodeNum> xbeeCore(PC_6,PC_7,VAL_xbeeCore_serialSpeed);
#endif

#ifdef ENABLE_switchJ7
DigitalIn switchJ7(PA_14);
#endif

#ifdef ENABLE_switchJ8
DigitalIn switchJ8(PA_13);
#endif


}