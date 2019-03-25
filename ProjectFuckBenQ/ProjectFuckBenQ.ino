#include <Encoder.h>
#include <EasyButton.h>
#include <oled.h>

OLED display=OLED(4,5,16);

const int FunctionStatePin = D7;
const int BoostButtonPin = D6;

EasyButton ButtonBoost(BoostButtonPin);
bool BootState = true;
bool BoostState = false;

long oldPosition = 0;
long newPosition = 0;

Encoder myEnc(D2, D3);
int ColorTemperature = 5;
int LightStrength = 5;
char displayLightStrength[10];
char displayColorTemperature[10];

void LightDataOutput(int data1,int data2) {
  display.clear();
  int coldbrightness=data1*data2;
  int warmbrightness=data1*(10-data2);
  Serial.write(31);Serial.write(01);Serial.write(coldbrightness);Serial.write(31+01+coldbrightness);
  Serial.write(31);Serial.write(02);Serial.write(warmbrightness);Serial.write(31+02+warmbrightness);
  if(data1==0){
    itoa(data1*10,displayLightStrength,10);
    display.draw_string_P(0, 0,"Brht:    %",OLED::DOUBLE_SIZE);
    display.draw_string_P(96, 0,displayLightStrength,OLED::DOUBLE_SIZE);
  }else if(data1==10||data1==20){
    itoa(data1*10,displayLightStrength,10);
    display.draw_string_P(0, 0,"Brht:    %",OLED::DOUBLE_SIZE);
    display.draw_string_P(72, 0,displayLightStrength,OLED::DOUBLE_SIZE);
  }else{
    itoa(data1*10,displayLightStrength,10);
    display.draw_string_P(0, 0,"Brht:    %",OLED::DOUBLE_SIZE);
    display.draw_string_P(84, 0,displayLightStrength,OLED::DOUBLE_SIZE);
  }
  itoa(data2*380+2700,displayColorTemperature,10);
  display.draw_string_P(0,16,"Temp:    K",OLED::DOUBLE_SIZE);
  display.draw_string_P(60,16,displayColorTemperature,OLED::DOUBLE_SIZE);
  display.display();
}

void ButtonEventSingle() {
  if (BootState==false){
    LightDataOutput(LightStrength,ColorTemperature);
    BootState=true;
  }else if (BootState==true) {
    LightDataOutput(0,5);
    BootState=false;
  }
}

void ButtonEventLong() {
  if (BoostState==false){
    LightDataOutput(20,5);
    BoostState=true;
  }else if (BoostState==true) {
    LightDataOutput(LightStrength,ColorTemperature);
    BoostState=false;
  }
}

void setup() {
  pinMode(FunctionStatePin, INPUT_PULLUP);
  Serial.begin(115200);
  ButtonBoost.begin();
  ButtonBoost.onPressed(ButtonEventSingle);
  ButtonBoost.onPressedFor(1500, ButtonEventLong);
  display.begin(); 
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
  ButtonBoost.read();
}
