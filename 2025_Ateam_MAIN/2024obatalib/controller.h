#pragma once
#ifndef CONTROLLER_H_INCLUDE_GUARD
#define CONTROLLER_H_INCLUDE_GUARD

#include "motor.h"
#include <math.h>
#include <iostream>

class Controller : Origin{
public:
    // コンストラクタ
    Controller() {};
    // コピーコンストラクタ
    Controller(const Controller& other) : Origin(other) {}
    // コピー代入演算子
    Controller& operator=(const Controller& other) {
        Origin::operator=(other); 
        return *this;
    }
};

#endif // CONTROLLER_H_INCLUDE_GUARD