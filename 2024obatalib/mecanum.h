#pragma once
#ifndef MECANUM_H_INCLUDE_GUARD
#define MECANUM_H_INCLUDE_GUARD

#include "chassis.h"

class Mecanum : Chassis {
private:
    // コピーコンストラクタと代入演算子を禁止
    Mecanum(const Mecanum& other);
    Mecanum& operator=(const Mecanum& other);

    // 配列でモーターを管理
    Motor** motors;
    float motor_max_power = 0.95f;
    static const int MAX_MOTOR;
    static const int MOTOR_COUNT;

    // 出力の計算
    void calculate_outputs(float x, float y, float rotation, float* outputs);
    // 出力の正規化
    void normalize_outputs(float* outputs);
public:
    // コンストラクタ
    Mecanum(Motor* (&motor_array)[4]);

    // 移動制御メソッド
    void move(float x, float y, float rotation)override;
    void move(float x, float y)override;

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

#endif // MECANUM_H_INCLUDE_GUARD