
#include "mu3.h"
#include "Arduino.h"
#include <stdlib.h>
#include <stdint.h>


mu3::mu3(){
  
}

void mu3::set(int ch,int group,int mynumber,int sendnumber){
  //Serial1.begin(19200, SERIAL_8N1,rspin,txpin);//rx.tx　serial2のデフォルトピンなんか調子悪いため。
  //while(!Serial1);
  //pinMode(4,INPUT);//rts
  //pinMode(5,OUTPUT);//cts
  //digitalWrite(5,LOW);
  ets_delay_us(300000);//これ入れると通信安定する。
  Serial.print("setup start\n");
  Serial1.print("@ch");
  sprintf(setnum,"%02x",ch);
  Serial1.print(setnum);
  Serial1.print("\r\n");
  ets_delay_us(100000);
  Serial1.print("@gi");
  sprintf(setnum,"%02x",group);
  Serial1.print(setnum);
  Serial1.print("\r\n");
  ets_delay_us(100000);
  Serial1.print("@ei");
  sprintf(setnum,"%02x",mynumber);
  Serial1.print(setnum);
  Serial1.print("\r\n");
  ets_delay_us(100000);
  Serial1.print("@di");
  sprintf(setnum,"%02x",sendnumber);
  Serial1.print(setnum);
  Serial1.print("\r\n");
  Serial.print("setup finished\n");
}

void mu3::check(){
  if (Serial1.available() > 0) {
    bufIndex=Serial1.available();
    String str0 = Serial1.readStringUntil('\n');
    Serial.println(str0);
    String str1 = str0.substring(6, bufIndex-2);
    num=str1.c_str();
    ifReceive(num);
  }
}
void mu3::send(char* data, size_t len){
  sprintf(sendSize,"%02x", (unsigned)len);
  Serial1.print("@dt");
  Serial1.print(sendSize);
  Serial1.write(data, len);     //送るデータをバイナリにしたいためwriteにした
  Serial1.print("\r\n");
  //Serial.print(strlen(data));
  Serial.print("@dt");
  Serial.print(sendSize);
  Serial.write(data, len);
  Serial.print("\r\n");
 
}

void mu3::attach(void (*p)(const char*)){
  ifReceive=p;
}
