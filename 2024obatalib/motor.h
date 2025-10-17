#pragma once
#ifndef MOTOR_H_INCLUDE_GUARD
#define MOTOR_H_INCLUDE_GUARD

#include "origin.h"

class Motor : Origin {
public:
    Motor() {} // �R���X�g���N�^
    Motor(const Motor& other) : Origin(other) {} // �R�s�[�R���X�g���N�^
    Motor& operator=(const Motor& other) { 
        Origin::operator=(other); 
        return *this;
    }

    virtual float operator=(const float power) = 0; // power�ݒ�p���Z�q�I�[�o�[���[�h
    virtual operator float() const = 0; // power�擾�p���[�U�[��`�̌^�ϊ�

    virtual void set_power(float power) = 0; // power�̐ݒ�
    virtual float get_max_power() = 0;
    virtual void set_limit_power(float min, float max) = 0;
};

#endif // MOTOR_H_INCLUDE_GUARD