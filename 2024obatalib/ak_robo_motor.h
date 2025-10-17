#pragma once
#ifndef AK_ROBO_MOTOR_H_INCLUDE_GUARD
#define AK_ROBO_MOTOR_H_INCLUDE_GUARD

#include "motor.h"
#include "mbed.h"

class Ak_robo_motor : public Motor {
private:
    // コピーコンストラクタと代入演算子を禁止
    Ak_robo_motor(const Ak_robo_motor& other); // コピーコンストラクタ
    Ak_robo_motor& operator=(const Ak_robo_motor& other); // コピー代入演算子

    PwmOut pin_r; // 右回転用ピン
    PwmOut pin_l; // 左回転用ピン
    bool is_reverse; // 回転を反転するか

    float min_power = -0.95f; // minのpower
    float max_power = 0.95; // maxのpower
    float now_power = 0; // nowのpower
public:
    Ak_robo_motor(PinName pin_r_arg, PinName pin_l_arg, bool is_reverse_arg); // コンストラクタ

    float operator=(const float power); // power設定用演算子オーバーロード

    operator float() const; // power取得用ユーザー定義の型変換
    void set_power(float power); // powerの設定
    float get_max_power()override;
    void setup()override;
    void set_limit_power(float min, float max)override;
    void loop()override;
};

#endif // AK_ROBO_MOTOR_H_INCLUDE_GUARD