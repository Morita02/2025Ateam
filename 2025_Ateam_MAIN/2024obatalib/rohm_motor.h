#pragma once
#ifndef ROHM_MOTOR_H_INCLUDE_GUARD
#define ROHM_MOTOR_H_INCLUDE_GUARD

#include "motor.h"

class Rohm_motor : public Motor {
private:
    // コピーコンストラクタと代入演算子を禁止
    Rohm_motor(const Rohm_motor& other); // コピーコンストラクタ
    Rohm_motor& operator=(const Rohm_motor& other); // コピー代入演算子

    int pin_r; // 右回転用ピン
    int pin_l; // 左回転用ピン
    float pin_power; // 回転出力用ピン
    bool is_reverse; // 回転を反転するか
    bool is_brake_when_zero; // 出力0のときにブレーキするか

    float min_power = -0.95f; // minのpower
    float max_power = 0.95; // maxのpower
    float now_power = 0; // nowのpower

    //pwmのチャンネルをまたいでいるので勝手に変更した場合の動作を保証できないためprivate
    //uint32_t freq(const uint32_t f);
public:
    Rohm_motor(int pin_r_arg, int pin_l_arg, float pin_power_arg, bool is_reverse_arg, bool is_brake_when_zero_arg = true)
        : pin_r(pin_r_arg), pin_l(pin_l_arg), pin_power(pin_power_arg), is_reverse(is_reverse_arg), is_brake_when_zero(is_brake_when_zero_arg) {
    }

    float operator=(const float power); // power設定用演算子オーバーロード

    operator float() const; // power取得用ユーザー定義の型変換
    void set_power(float power); // powerの設定
    float get_max_power()override;
    void setup()override;
    void set_limit_power(float min, float max)override;
    void loop()override;
};

#endif // ROHM_MOTOR_H_INCLUDE_GUARD