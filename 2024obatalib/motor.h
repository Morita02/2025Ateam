#pragma once
#ifndef MOTOR_H_INCLUDE_GUARD
#define MOTOR_H_INCLUDE_GUARD

#include "origin.h"

class Motor : Origin {
public:
    Motor() {} // コンストラクタ
    Motor(const Motor& other) : Origin(other) {} // コピーコンストラクタ
    Motor& operator=(const Motor& other) { 
        Origin::operator=(other); 
        return *this;
    }

    virtual float operator=(const float power) = 0; // power設定用演算子オーバーロード
    virtual operator float() const = 0; // power取得用ユーザー定義の型変換

    virtual void set_power(float power) = 0; // powerの設定
    virtual float get_max_power() = 0;
    virtual void set_limit_power(float min, float max) = 0;
};

#endif // MOTOR_H_INCLUDE_GUARD