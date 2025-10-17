#ifndef IM920_HPP_INCLUDE_GUARD
#define IM920_HPP_INCLUDE_GUARD

#include "mbed.h"

class IM920{

  private:
  Serial *const srlP;
  Callback<void(uint8_t*,uint16_t)> callbackFunc=NULL;
  static const size_t bufLen=1024;
  uint8_t buf[bufLen];
  uint16_t bufIndex;
  static const uint8_t escapeByte=0xF3;
  bool isNextReceiveEscaped=false;

  void whenReceiveByte();
  void whenReceiveMsg();

  public:
  IM920(Serial *srlParg);
  void setup();
  void attach(Callback<void(uint8_t*,uint16_t)>);
  void send(uint8_t[],uint16_t);
};

#endif