#include "stick.h"
#include <iostream>

const float Stick_vals::DEADZONE = 3.0f;
const float Stick_vals::STICK_MIN_VALUE = 0.0f;
const float Stick_vals::STICK_MAX_VALUE = 255.0f;

Stick_vals::Stick_vals()
	: left_x(this, &Stick_vals::convert_stick_to_normalized)
	, left_y(this, &Stick_vals::convert_stick_to_normalized)
	, right_x(this, &Stick_vals::convert_stick_to_normalized)
	, right_y(this, &Stick_vals::convert_stick_to_normalized) {}

void Stick_vals::convert_stick_to_normalized(float& value) {
	value -= ((STICK_MAX_VALUE - STICK_MIN_VALUE) / 2.0f);
	// デッドゾーンの実装
	if (std::abs(value) < DEADZONE) value = 0.0f;
	std::cout << value << std::endl;
}

Stick::Stick(Stick_vals* stick_vals_arg) : stick_vals(stick_vals_arg) {}

Stick::Stick(const Stick& other) : Controller::Controller(other) {
	this->stick_vals = other.stick_vals;
}

Stick& Stick::operator=(const Stick& other) {
	Controller::operator=(other);
	this->stick_vals = other.stick_vals;
	return *this;
}

Stick_vals Stick::get_stick_val() {
	return *stick_vals;
}

void Stick::setup() {}

void Stick::loop() {}