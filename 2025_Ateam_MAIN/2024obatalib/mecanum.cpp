#include "mecanum.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

// 静的定数の定義
const int Mecanum::MAX_MOTOR = 4; // 静的なメモリ確保のみにするため
const int Mecanum::MOTOR_COUNT = 4; // 4輪固定

Mecanum::Mecanum(Motor* (&motor_array)[4]) {
    for (int i = 1; i < MOTOR_COUNT; i++) {
        if (*motor_array[i] != *motor_array[0]) {
            std::exit(-1);
        }
    }

    motor_max_power = motor_array[0]->get_max_power();
    motors = motor_array;
}

void Mecanum::calculate_outputs(float x, float y, float rotation, float* outputs) {
    // メカナムホイール用の出力計算（4輪前提）
    outputs[0] = y + x + rotation;  // 左前
    outputs[1] = y - x - rotation;  // 右前
    outputs[2] = y - x + rotation;  // 左後
    outputs[3] = y + x - rotation;  // 右後
}

void Mecanum::normalize_outputs(float* outputs) {
    // 出力の正規化
    float max_power = 1.0f;
    for (int i = 0; i < MOTOR_COUNT; i++) {
        max_power = std::max(max_power, std::abs(outputs[i]));
    }

    // 出力を-0.95から0.95の範囲に正規化
    for (int i = 0; i < MOTOR_COUNT; i++) {
        outputs[i] = (outputs[i] / max_power) * motor_max_power;
    }
}

void Mecanum::move(float x, float y, float rotation) {
    // モーター出力を格納する配列
    float outputs[MAX_MOTOR];

    calculate_outputs(x, y, rotation, outputs);

    // 出力の正規化
    normalize_outputs(outputs);

    // モーターに出力を設定
    set_motor_outputs(outputs);
}

void Mecanum::move(float x, float y) {}

void Mecanum::set_motor_outputs(const float* outputs) {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        *motors[i] = outputs[i];
    }
}

void Mecanum::set_limit_power(float min, float max) {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        motors[i]->set_limit_power(min, max);
    }
    motor_max_power = max;
}

void Mecanum::emergency_stop() {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        *motors[i] = 0.0f;
    }
}

void Mecanum::print_motor_outputs() {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        std::cout << "Motor " << i << ": " << *motors[i] << std::endl;
    }
}

int Mecanum::get_motor_count() const {
    return MOTOR_COUNT;
}

void Mecanum::setup() {}

void Mecanum::loop() {}