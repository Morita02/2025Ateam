#pragma once
#ifndef OMUNI_H_INCLUDE_GUARD
#define OMUNI_H_INCLUDE_GUARD

#include "chassis.h"
#include <iostream>

class Omuni : Chassis {
private:
    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q���֎~
    Omuni(const Omuni& other);
    Omuni& operator=(const Omuni& other);

    // �z��Ń��[�^�[���Ǘ�
    Motor** motors;
    int motor_count;
    float motor_max_power = 0.95f;
    static const float PI;
    static const int MAX_MOTOR;

    // �o�͂̌v�Z
    void calculate_outputs(float x, float y, float rotation, float* outputs);
    // �o�͂̐��K��
    void normalize_outputs(float* outputs);

public:
    // �R���X�g���N�^
    Omuni(Motor* motor_array[], int motor_num);

    // �ړ����䃁�\�b�h
    void move(float x, float y, float rotation)override;
    void move(float x, float y)override;

    // ���[�^�[�o�͂̒��ڐݒ�
    void set_motor_outputs(const float* outputs)override;

    // ���[�^�[�̏o�̓��~�b�g�̈ꊇ�ݒ�
    void set_limit_power(float min, float max)override;

    // �ً}��~
    void emergency_stop()override;

    // �f�o�b�O�p�o��
    void print_motor_outputs()override;

    // ���[�^�[�����擾
    int get_motor_count() const override;

    void setup()override;
    void loop()override;
};

#endif // OMUNI_H_INCLUDE_GUARD