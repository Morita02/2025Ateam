#include "ak_robo_motor.h"
#include <iostream>

using namespace std;

Ak_robo_motor::Ak_robo_motor(PinName pin_r_arg, PinName pin_l_arg, bool is_reverse_arg = false)
    : pin_r(pin_r_arg), pin_l(pin_l_arg), is_reverse(is_reverse_arg) {
    cout << "Motor コンストラクタ: " << this << endl;
}

void Ak_robo_motor::set_power(float power) {
    if (power > max_power)power = max_power;
    if (power < min_power)power = min_power;

    if (is_reverse)power *= (-1.0f);

    now_power = power;

    if (power < 0.0) {
        pin_r = 0.0f;
        pin_l = std::abs(power);
    }
    else {
        pin_r = std::abs(power);
        pin_l = 0.0f;
    }
}

float Ak_robo_motor::get_max_power() {
    return max_power;
}

float Ak_robo_motor::operator=(const float power) {
    set_power(power);
    //pc.printf("%f\n\r",power);
    return power;
}

Ak_robo_motor::operator float() const {
    return now_power;
}

void Ak_robo_motor::setup() {
    cout << "Motor setup: " << pin_r << "," << pin_l << ":" << this << endl;
}

void Ak_robo_motor::set_limit_power(float min, float max) {
    min_power = min;
    max_power = max;
}

void Ak_robo_motor::loop() {}