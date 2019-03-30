#include <Encoder.h>
#include <EasyButton.h>

long oldPosition = 0;
long newPosition = 0;

Encoder myEnc(D1, D2);
const int FunctionStatePin = D3;
const int BoostButtonPin = D5;
const int WarmLightStrip = D7;
const int ColdLightStrip = D6;
int ColorTemperature = 5;
int LightStrength = 5;

EasyButton ButtonBoost(BoostButtonPin);
bool BootState = true;
bool BoostState = false;

void LightDataOutput(int data1,int data2){
  int coldbrightness=data1*data2*10;
  int warmbrightness=data1*(10-data2)*10;
  Serial.print(coldbrightness);Serial.print("|");Serial.println(warmbrightness);
  analogWrite(ColdLightStrip, coldbrightness);
  analogWrite(WarmLightStrip, warmbrightness);
}

void ButtonEventSingle() {
  if (BootState==false){
    LightDataOutput(LightStrength,ColorTemperature);
    BootState=true;
  }else if (BootState==true) {
    LightDataOutput(0,5);
    BoostState=false;
    BootState=false;
  }
}

void ButtonEventLong() {
  if (BoostState==false){
    LightDataOutput(20,5);
    BootState=true;
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
  ButtonBoost.onPressedFor(800, ButtonEventLong);
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
    BootState=true;
    BoostState=false;
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
    BootState=true;
    BoostState=false;
  }
  ButtonBoost.read();
}      
