#pragma once
#ifndef STICK_H_INCLUDE_GUARD
#define STICK_H_INCLUDE_GUARD

#include "controller.h"

class Stick_vals;

template<typename T>
class Observable {
private:
	T value;
	Stick_vals* owner;
	void (Stick_vals::* callback)(T&);

public:
	Observable(Stick_vals* owner_, void (Stick_vals::* cb)(T&))
		: value(T()), owner(owner_), callback(cb) {
	}

	T& operator=(const T& newValue) {
		value = newValue;
		if (owner && callback) {
			(owner->*callback)(value);
		}
		return value;
	}

	operator T() const { return value; }
	T get() const { return value; }
};

class Stick_vals {
	friend class Observable<float>;
private:
	static const float DEADZONE;
	static const float STICK_MIN_VALUE;
	static const float STICK_MAX_VALUE;

	void convert_stick_to_normalized(float& value);
public:
	Stick_vals();

	Observable<float> left_x;
	Observable<float> left_y;
	Observable<float> right_x;
	Observable<float> right_y;
};

class Stick : Controller {
private:
	Stick_vals* stick_vals;
public:
	Stick(Stick_vals* stick_vals_arg); // コンストラクタ	
	Stick(const Stick& other); // コピーコンストラクタ
	Stick& operator=(const Stick& other);
	Stick_vals get_stick_val();
	void setup()override;
	void loop()override;
};

#endif // STICK_H_INCLUDE_GUARD