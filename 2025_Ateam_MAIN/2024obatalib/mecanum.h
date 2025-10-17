#pragma once
#ifndef MECANUM_H_INCLUDE_GUARD
#define MECANUM_H_INCLUDE_GUARD

#include "chassis.h"

class Mecanum : Chassis {
private:
    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q���֎~
    Mecanum(const Mecanum& other);
    Mecanum& operator=(const Mecanum& other);

    // �z��Ń��[�^�[���Ǘ�
    Motor** motors;
    float motor_max_power = 0.95f;
    static const int MAX_MOTOR;
    static const int MOTOR_COUNT;

    // �o�͂̌v�Z
    void calculate_outputs(float x, float y, float rotation, float* outputs);
    // �o�͂̐��K��
    void normalize_outputs(float* outputs);
public:
    // �R���X�g���N�^
    Mecanum(Motor* (&motor_array)[4]);

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

#endif // MECANUM_H_INCLUDE_GUARD