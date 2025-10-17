#include "IM920.hpp"

IM920::IM920(Serial *srlParg):
  srlP(srlParg),
  bufIndex(0)
{}

void IM920::whenReceiveByte(){
  const uint8_t c=srlP->getc();
  if(c=='\r'){
    return;
  }else if(c=='\n'){
    //受信したときの処理
    whenReceiveMsg();
    bufIndex=0;
  }else if(c==escapeByte){
    isNextReceiveEscaped=true;
  }else{
    if((bufIndex<bufLen)){
      if(isNextReceiveEscaped){
        buf[bufIndex]=c^escapeByte;
        isNextReceiveEscaped=false;
      }else{
        buf[bufIndex]=c;
      }
      bufIndex++;
    }
  }
}
void IM920::whenReceiveMsg(){
  if(bufIndex==2){
    if(buf[0]=='O'&&buf[1]=='K'){
      return;
    }else if(buf[0]=='N'&&buf[1]=='G'){
      return;
    }
  }
  //データシートより抜粋
  //                 0123456789AB
  // 受信データは、「aa,bbbb,cc:…」の形式で出力され、内容は次の通りです。
  // aa ノード番号
  // bbbb 送信モジュールの固有 ID 番号
  // cc 受信データの RSSI 値
  if(callbackFunc){
    const int offset=11;
    callbackFunc(buf+offset,bufIndex-offset);
  }
}

void IM920::setup(){
  srlP->attach(callback(this,&IM920::whenReceiveByte),Serial::RxIrq);
}

void IM920::attach(Callback<void(uint8_t*,uint16_t)> cb){
  callbackFunc=cb;
}

void IM920::send(uint8_t array[],uint16_t arrayLen){
  srlP->printf("TXDA");
  for(size_t i=0;i<arrayLen;i++){
    const uint8_t c=array[i];
    if(c=='\r'||c=='\n'||c==escapeByte){
      srlP->putc(escapeByte);
      srlP->putc(escapeByte^c);
    }else{
      srlP->putc(c);
    }
  }
  srlP->putc('\r');
  srlP->putc('\n');
}