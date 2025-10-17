#include "omuni.h"
#include <cstdlib>
#include <cmath>

// 静的定数の定義
const float Omuni::PI = 3.14159265358979323846f;
const int Omuni::MAX_MOTOR = 8; // 静的なメモリ確保のみにするため

Omuni::Omuni(Motor* motor_array[], int motor_num) : motor_count(motor_num) {
    for (int i = 1; i < motor_count; i++) {
        if (*motor_array[i] != *motor_array[0]) {
            std::exit(-1);
        }
    }

    motor_max_power = motor_array[0]->get_max_power();
    motors = motor_array;
}

void Omuni::calculate_outputs(float x, float y, float rotation, float* outputs) {
    // オムニホイール用の出力計算
    float motor_angles[MAX_MOTOR];

    int i;

    float interval_angle = 360 / motor_count;
    float start_angle = interval_angle / 2;

    for (i = 0; i < motor_count; i++) {
        motor_angles[i] = start_angle + i * interval_angle;
    }

    for (i = 0; i < motor_count; i++) {
        // ラジアンに変換
        float angle_rad = motor_angles[i] * PI / 180.0f;

        // 各モーターの出力計算
        outputs[i] =
            x * cos(angle_rad) +
            y * sin(angle_rad) +
            rotation; // マシン中心からWheelまでの距離が一定の場合（一定でない場合要改造）
    }
}

void Omuni::normalize_outputs(float* outputs) {
    // 出力の正規化
    float max_power = 1.0f;
    for (int i = 0; i < motor_count; i++) {
        max_power = std::max(max_power, std::fabs(outputs[i]));
    }

    // 出力を-0.95から0.95の範囲に正規化
    for (int i = 0; i < motor_count; i++) {
        outputs[i] = (outputs[i] / max_power) * motor_max_power;
    }
}

void Omuni::move(float x, float y, float rotation) {
    // モーター出力を格納する配列
    float outputs[MAX_MOTOR];

    calculate_outputs(x, y, rotation, outputs);

    // 出力の正規化
    normalize_outputs(outputs);

    // モーターに出力を設定
    set_motor_outputs(outputs);
}

void Omuni::move(float x, float y) {}

void Omuni::set_motor_outputs(const float* outputs) {
    for (int i = 0; i < motor_count; i++) {
        *motors[i] = outputs[i];
    }
}

void Omuni::set_limit_power(float min, float max) {
    for (int i = 0; i < motor_count; i++) {
        motors[i]->set_limit_power(min, max);
    }
    motor_max_power = max;
}

void Omuni::emergency_stop() {
    for (int i = 0; i < motor_count; i++) {
        *motors[i] = 0.0f;
    }
}

void Omuni::print_motor_outputs() {
    for (int i = 0; i < motor_count; i++) {
        std::cout << "Motor " << i << ": " << *motors[i] << std::endl;
    }
}

int Omuni::get_motor_count() const {
	return motor_count;
}

void Omuni::setup() {}

void Omuni::loop() {}