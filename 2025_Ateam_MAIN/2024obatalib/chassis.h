#pragma once
#ifndef CHASSIS_H_INCLUDE_GUARD
#define CHASSIS_H_INCLUDE_GUARD

#include "motor.h"

class Chassis : Origin {
public:
	Chassis() {} // �R���X�g���N�^
	Chassis(const Chassis& other) : Origin(other) {} // �R�s�[�R���X�g���N�^
	Chassis& operator=(const Chassis& other) { 
        Origin::operator=(other); 
        return *this;
    } // �R�s�[������Z�q

	// Wheel���ƂɕK�v�ȃp�����[�^���قȂ邽�߃I�[�o�[���[�h
	virtual void move(float x, float y, float rotation) = 0;
	virtual void move(float val_1, float val_2) = 0;

    // ���[�^�[�o�͂̒��ڐݒ�
    virtual void set_motor_outputs(const float* outputs) = 0;

    // ���[�^�[�̏o�̓��~�b�g�̈ꊇ�ݒ�
    virtual void set_limit_power(float min, float max) = 0;

    // �ً}��~
    virtual void emergency_stop() = 0;

    // �f�o�b�O�p�o��
    virtual void print_motor_outputs() = 0;

    // ���[�^�[�����擾
    virtual int get_motor_count() const = 0;
};

#endif // CHASSIS_H_INCLUDE_GUARD