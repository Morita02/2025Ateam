#pragma once
#ifndef AK_ROBO_MOTOR_H_INCLUDE_GUARD
#define AK_ROBO_MOTOR_H_INCLUDE_GUARD

#include "motor.h"
#include "mbed.h"

class Ak_robo_motor : public Motor {
private:
    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q���֎~
    Ak_robo_motor(const Ak_robo_motor& other); // �R�s�[�R���X�g���N�^
    Ak_robo_motor& operator=(const Ak_robo_motor& other); // �R�s�[������Z�q

    PwmOut pin_r; // �E��]�p�s��
    PwmOut pin_l; // ����]�p�s��
    bool is_reverse; // ��]�𔽓]���邩

    float min_power = -0.95f; // min��power
    float max_power = 0.95; // max��power
    float now_power = 0; // now��power
public:
    Ak_robo_motor(PinName pin_r_arg, PinName pin_l_arg, bool is_reverse_arg); // �R���X�g���N�^

    float operator=(const float power); // power�ݒ�p���Z�q�I�[�o�[���[�h

    operator float() const; // power�擾�p���[�U�[��`�̌^�ϊ�
    void set_power(float power); // power�̐ݒ�
    float get_max_power()override;
    void setup()override;
    void set_limit_power(float min, float max)override;
    void loop()override;
};

#endif // AK_ROBO_MOTOR_H_INCLUDE_GUARD