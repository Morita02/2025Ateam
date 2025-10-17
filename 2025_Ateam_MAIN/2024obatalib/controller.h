#pragma once
#ifndef CONTROLLER_H_INCLUDE_GUARD
#define CONTROLLER_H_INCLUDE_GUARD

#include "motor.h"
#include <math.h>
#include <iostream>

class Controller : Origin{
public:
    // �R���X�g���N�^
    Controller() {};
    // �R�s�[�R���X�g���N�^
    Controller(const Controller& other) : Origin(other) {}
    // �R�s�[������Z�q
    Controller& operator=(const Controller& other) {
        Origin::operator=(other); 
        return *this;
    }
};

#endif // CONTROLLER_H_INCLUDE_GUARD