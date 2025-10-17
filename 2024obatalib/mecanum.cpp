#include "mecanum.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

// �ÓI�萔�̒�`
const int Mecanum::MAX_MOTOR = 4; // �ÓI�ȃ������m�ۂ݂̂ɂ��邽��
const int Mecanum::MOTOR_COUNT = 4; // 4�֌Œ�

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
    // ���J�i���z�C�[���p�̏o�͌v�Z�i4�֑O��j
    outputs[0] = y + x + rotation;  // ���O
    outputs[1] = y - x - rotation;  // �E�O
    outputs[2] = y - x + rotation;  // ����
    outputs[3] = y + x - rotation;  // �E��
}

void Mecanum::normalize_outputs(float* outputs) {
    // �o�͂̐��K��
    float max_power = 1.0f;
    for (int i = 0; i < MOTOR_COUNT; i++) {
        max_power = std::max(max_power, std::abs(outputs[i]));
    }

    // �o�͂�-0.95����0.95�͈̔͂ɐ��K��
    for (int i = 0; i < MOTOR_COUNT; i++) {
        outputs[i] = (outputs[i] / max_power) * motor_max_power;
    }
}

void Mecanum::move(float x, float y, float rotation) {
    // ���[�^�[�o�͂��i�[����z��
    float outputs[MAX_MOTOR];

    calculate_outputs(x, y, rotation, outputs);

    // �o�͂̐��K��
    normalize_outputs(outputs);

    // ���[�^�[�ɏo�͂�ݒ�
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