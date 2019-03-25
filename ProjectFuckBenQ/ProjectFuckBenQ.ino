#include <Encoder.h>

long oldPosition = 0;
long newPosition = 0;

unsighed char hexdata[4]={0x1F,0x01,0x00,0x20};

Encoder myEnc(D2, D3);
const int FunctionStatePin = D1;
int ColorTemperature = 5;
int LightStrength = 5;

void LightDataOutput(int data1,int data2){
  Serial.print("冷光绝对亮度:");
  Serial.print(data1*data2);
  Serial.print(" | 暖光绝对亮度:");
  Serial.println(data1*(10-data2));
}

void setup() {
  pinMode(FunctionStatePin, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
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
