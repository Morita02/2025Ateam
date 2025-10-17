#pragma once
#ifndef ROHM_MOTOR_H_INCLUDE_GUARD
#define ROHM_MOTOR_H_INCLUDE_GUARD

#include "motor.h"

class Rohm_motor : public Motor {
private:
    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q���֎~
    Rohm_motor(const Rohm_motor& other); // �R�s�[�R���X�g���N�^
    Rohm_motor& operator=(const Rohm_motor& other); // �R�s�[������Z�q

    int pin_r; // �E��]�p�s��
    int pin_l; // ����]�p�s��
    float pin_power; // ��]�o�͗p�s��
    bool is_reverse; // ��]�𔽓]���邩
    bool is_brake_when_zero; // �o��0�̂Ƃ��Ƀu���[�L���邩

    float min_power = -0.95f; // min��power
    float max_power = 0.95; // max��power
    float now_power = 0; // now��power

    //pwm�̃`�����l�����܂����ł���̂ŏ���ɕύX�����ꍇ�̓����ۏ؂ł��Ȃ�����private
    //uint32_t freq(const uint32_t f);
public:
    Rohm_motor(int pin_r_arg, int pin_l_arg, float pin_power_arg, bool is_reverse_arg, bool is_brake_when_zero_arg = true)
        : pin_r(pin_r_arg), pin_l(pin_l_arg), pin_power(pin_power_arg), is_reverse(is_reverse_arg), is_brake_when_zero(is_brake_when_zero_arg) {
    }

    float operator=(const float power); // power�ݒ�p���Z�q�I�[�o�[���[�h

    operator float() const; // power�擾�p���[�U�[��`�̌^�ϊ�
    void set_power(float power); // power�̐ݒ�
    float get_max_power()override;
    void setup()override;
    void set_limit_power(float min, float max)override;
    void loop()override;
};

#endif // ROHM_MOTOR_H_INCLUDE_GUARD