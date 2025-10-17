#include "differential.h"
#include <iostream>
#include <cmath>
#include <cstdlib>


// 静的定数の定義
const int Differential::MAX_MOTOR = 2; // 静的なメモリ確保のみにするため
const int Differential::MOTOR_COUNT = 2; // 2輪固定

Differential::Differential(Motor* (&motor_array)[2]) {
    for (int i = 1; i < MOTOR_COUNT; i++) {
        if (*motor_array[i] != *motor_array[0]) {
            std::exit(-1);
        }
    }

    motor_max_power = motor_array[0]->get_max_power();
    motors = motor_array;
}

void Differential::calculate_outputs(float left_y, float right_y, float* outputs) {
    // 差動二輪用の出力計算（2輪前提）
    outputs[0] = left_y;
    outputs[1] = right_y;
}

void Differential::normalize_outputs(float* outputs) {
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

void Differential::move(float x, float y, float rotation) {}

void Differential::move(float left_y, float right_y) {
    // モーター出力を格納する配列
    float outputs[MAX_MOTOR];

    calculate_outputs(left_y, right_y, outputs);

    // 出力の正規化
    normalize_outputs(outputs);

    // モーターに出力を設定
    set_motor_outputs(outputs);
}

void Differential::set_motor_outputs(const float* outputs) {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        *motors[i] = outputs[i];
    }
}

void Differential::set_limit_power(float min, float max) {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        motors[i]->set_limit_power(min, max);
    }
    motor_max_power = max;
}

void Differential::emergency_stop() {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        *motors[i] = 0.0f;
    }
}

void Differential::print_motor_outputs() {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        std::cout << "Motor " << i << ": " << *motors[i] << std::endl;
    }
}

int Differential::get_motor_count() const {
    return MOTOR_COUNT;
}

void Differential::setup() {}

void Differential::loop() {}