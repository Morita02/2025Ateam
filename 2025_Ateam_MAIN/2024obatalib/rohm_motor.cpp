#include "rohm_motor.h"
#include <iostream>
#include <cmath>

/*
uint32_t Rohm_motor::freq(const uint32_t f) {
    const int t = 1000000 / f;
    pwm1.period_us(t);
    return f;
}
*/

void Rohm_motor::set_power(float power) {
    if (power > max_power)power = max_power;
    if (power < min_power)power = min_power;

    if (is_reverse)power *= (-1.0f);

    now_power = power;

    if (power == 0.0f && is_brake_when_zero) {
        pin_r = 1;
        pin_l = 1;
        pin_power = 0.0f;
    }
    else if (power < 0.0) {
        pin_r = 1;
        pin_l = 0;
        pin_power = std::abs(power);
    }
    else {
        pin_r = 0;
        pin_l = 1;
        pin_power = std::abs(power);
    }
}

float Rohm_motor::get_max_power() {
	return max_power;
}

float Rohm_motor::operator=(const float power) {
	set_power(power);
	return power;
}

Rohm_motor::operator float() const {
	return now_power;
}

void Rohm_motor::set_limit_power(float min, float max) {
	min_power = min;
	max_power = max;
}

void Rohm_motor::setup() {}
void Rohm_motor::loop() {}