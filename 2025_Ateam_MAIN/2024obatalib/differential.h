#pragma once
#ifndef DIFFERENTIAL_H_INCLUDE_GUARD
#define DIFFERENTIAL_H_INCLUDE_GUARD

#include "chassis.h"

class Differential : Chassis {
private:
    // コピーコンストラクタと代入演算子を禁止
    Differential(const Differential& other);
    Differential& operator=(const Differential& other);

    // 配列でモーターを管理
    Motor** motors;
    float motor_max_power = 0.95f;
    static const int MAX_MOTOR;
    static const int MOTOR_COUNT;

    // 出力の計算
    void calculate_outputs(float left_y, float right_y, float* outputs);
    // 出力の正規化
    void normalize_outputs(float* outputs);
public:
    // コンストラクタ
    Differential(Motor* (&motor_array)[2]);

    // 移動制御メソッド
    void move(float x, float y, float rotation)override;
    void move(float left_x, float right_y)override;

    // モーター出力の直接設定
    void set_motor_outputs(const float* outputs)override;

    // モーターの出力リミットの一括設定
    void set_limit_power(float min, float max)override;

    // 緊急停止
    void emergency_stop()override;

    // デバッグ用出力
    void print_motor_outputs()override;

    // モーター数を取得
    int get_motor_count() const override;

    void setup()override;
    void loop()override;
};

#endif // DIFFERENTIAL_H_INCLUDE_GUARD