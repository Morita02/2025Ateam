#pragma once
#ifndef CHASSIS_H_INCLUDE_GUARD
#define CHASSIS_H_INCLUDE_GUARD

#include "motor.h"

class Chassis : Origin {
public:
	Chassis() {} // コンストラクタ
	Chassis(const Chassis& other) : Origin(other) {} // コピーコンストラクタ
	Chassis& operator=(const Chassis& other) { 
        Origin::operator=(other); 
        return *this;
    } // コピー代入演算子

	// Wheelごとに必要なパラメータが異なるためオーバーロード
	virtual void move(float x, float y, float rotation) = 0;
	virtual void move(float val_1, float val_2) = 0;

    // モーター出力の直接設定
    virtual void set_motor_outputs(const float* outputs) = 0;

    // モーターの出力リミットの一括設定
    virtual void set_limit_power(float min, float max) = 0;

    // 緊急停止
    virtual void emergency_stop() = 0;

    // デバッグ用出力
    virtual void print_motor_outputs() = 0;

    // モーター数を取得
    virtual int get_motor_count() const = 0;
};

#endif // CHASSIS_H_INCLUDE_GUARD