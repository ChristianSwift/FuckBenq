#include <Encoder.h>

long oldPosition = 0;
long newPosition = 0;

char hexdata[4]={0x00,0x00,0x00,0x00};

Encoder myEnc(D2, D3);
const int FunctionStatePin = D1;
int ColorTemperature = 5;
int LightStrength = 5;

void LightDataOutput(int data1,int data2){
  //Serial.print("冷光绝对亮度:");
  //Serial.print(data1*data2);
  //Serial.print(" | 暖光绝对亮度:");
  //Serial.println(data1*(10-data2));
  
  int coldbrightness=data1*data2;
  int warmbrightness=data1*(10-data2);

  Serial.write(31);Serial.write(01);Serial.write(coldbrightness);Serial.write(31+01+coldbrightness);
  Serial.write(31);Serial.write(02);Serial.write(warmbrightness);Serial.write(31+02+warmbrightness);
//  Serial.print("冷光:");
//  Serial.print(31,HEX);
//  Serial.print(" ");
//  Serial.print(01,HEX);
//  Serial.print(" ");
//  Serial.print(coldbrightness,HEX);
//  Serial.print(" ");
//  Serial.println(31+01+coldbrightness,HEX);
//  
//  Serial.print("暖光:");
//  Serial.print(31,HEX);
//  Serial.print(" ");
//  Serial.print(02,HEX);
//  Serial.print(" ");
//  Serial.print(warmbrightness,HEX);
//  Serial.print(" ");
//  Serial.println(31+01+warmbrightness,HEX);
}

void setup() {
  pinMode(FunctionStatePin, INPUT_PULLUP);
  Serial.begin(115200);
  LightDataOutput(LightStrength,ColorTemperature);
}

void loop() {
  long newPosition = myEnc.read()/4;
  if (newPosition > oldPosition) {
    oldPosition = newPosition;
    if (digitalRead(FunctionStatePin) == HIGH) {
      if (LightStrength < 10) {
        LightStrength++;
      }
    } else {
      if (ColorTemperature < 10) {
        ColorTemperature++;
      }
    }
    LightDataOutput(LightStrength,ColorTemperature);
  }else if (newPosition < oldPosition) {
    oldPosition = newPosition;
    if (digitalRead(FunctionStatePin) == HIGH) {
      if (LightStrength > 0) {
        LightStrength--;
      }
    } else {
      if (ColorTemperature > 0) {
        ColorTemperature--;
      }
    }
    LightDataOutput(LightStrength,ColorTemperature);
  }
}
