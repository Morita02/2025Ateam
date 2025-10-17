#ifndef M2021ROBOSEPARATEBOARDLIB_INCLUDE_GUARD
#define M2021ROBOSEPARATEBOARDLIB_INCLUDE_GUARD

//このファイルだけshift-jisな点について注意

#include "2021roboSeparateBoardLib/lib.hpp"

//////////////////////////
// ここで各種値を設定する
//////////////////////////

// 設定ここから
///////////////////////////

//ENABLE_何とか
//使用していないものはコメントアウトするとよい

// #define ENABLE_motor1_AS_KMD
// #define ENABLE_motor2_AS_KMD
// #define ENABLE_motor3_AS_KMD
// #define ENABLE_motor4_AS_KMD
// #define ENABLE_motor5_AS_KMD
//#define ENABLE_motor1_AS_ROHMMD
// #define ENABLE_motor2_AS_ROHMMD
// #define ENABLE_motor3_AS_ROHMMD
// #define ENABLE_motor4_AS_ROHMMD
// #define ENABLE_motor5_AS_ROHMMD
#define ENABLE_rotaryEncoder1
#define ENABLE_rotaryEncoder2
// #define ENABLE_imu03a
//#define ENABLE_xbeeCore
// #define ENABLE_switchJ8
// #define ENABLE_switchJ7


//VAL_何とか
//適切な値を設定すること

//シリアルの通信速度を設定
//xbee側の設定と合わせてください
//一番早い115200を推奨します
#define VAL_xbeeCore_serialSpeed 115200

//xbeeCoreにぶら下げるnodeの数を指定します
//ここでnodeとはxbeeCommのことです
//実装を見てもらえばわかりますが他のノードを自作することもできます
#define VAL_xbeeCore_nodeNum 3


///////////////////////////
// 設定ここまで


//以下は基本的にはいじる必要はありません


namespace rob{
#ifdef ENABLE_motor1_AS_KMD
	#ifdef ENABLE_motor1_AS_ROHMMD
		#error ("同時にKMDとROHMMDを同一のポート1に対して使用することはできません 2021roboSeparateBoardLib_setting.hppを確認してください")
	#endif
	extern aKMD motor1;
#elif defined(ENABLE_motor1_AS_ROHMMD)
	extern aRohmMD motor1;
#endif

#ifdef ENABLE_motor2_AS_KMD
	#ifdef ENABLE_motor2_AS_ROHMMD
		#error ("同時にKMDとROHMMDを同一のポート2に対して使用することはできません 2021roboSeparateBoardLib_setting.hppを確認してください")
	#endif
	extern aKMD motor2;
#elif defined(ENABLE_motor2_AS_ROHMMD)
	extern aRohmMD motor2;
#endif

#ifdef ENABLE_motor3_AS_KMD
	#ifdef ENABLE_motor3_AS_ROHMMD
		#error ("同時にKMDとROHMMDを同一のポート3に対して使用することはできません 2021roboSeparateBoardLib_setting.hppを確認してください")
	#endif
	extern aKMD motor3;
#elif defined(ENABLE_motor3_AS_ROHMMD)
	extern aRohmMD motor3;
#endif

#ifdef ENABLE_motor4_AS_KMD
	#ifdef ENABLE_motor4_AS_ROHMMD
		#error ("同時にKMDとROHMMDを同一のポート4に対して使用することはできません 2021roboSeparateBoardLib_setting.hppを確認してください")
	#endif
	extern aKMD motor4;
#elif defined(ENABLE_motor4_AS_ROHMMD)
	extern aRohmMD motor4;
#endif

#ifdef ENABLE_motor5_AS_KMD
	#ifdef ENABLE_motor5_AS_ROHMMD
		#error ("同時にKMDとROHMMDを同一のポート5に対して使用することはできません 2021roboSeparateBoardLib_setting.hppを確認してください")
	#endif
	extern aKMD motor5;
#elif defined(ENABLE_motor5_AS_ROHMMD)
	extern aRohmMD motor5;
#endif

#ifdef ENABLE_rotaryEncoder1
extern aRotaryEncoder rotaryEncoder1;
#endif

#ifdef ENABLE_rotaryEncoder2
extern aRotaryEncoder rotaryEncoder2;
#endif

#ifdef ENABLE_imu03a
//mosi miso slck csPin
extern a_imu03a imu03a;
#endif

#ifdef ENABLE_xbeeCore
//tx rx 
extern aXbeeCoreCallback<VAL_xbeeCore_nodeNum> xbeeCore;
#endif

#ifdef ENABLE_switchJ7
extern DigitalIn switchJ7;
#endif

#ifdef ENABLE_switchJ8
extern DigitalIn switchJ8;
#endif

}

#endif
