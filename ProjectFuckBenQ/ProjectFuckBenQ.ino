#include <Encoder.h>

long oldPosition = 0;
long newPosition = 0;

Encoder myEnc(D2, D3);
const int FunctionStatePin = D1;
int ColorTemperature = 5;
int LightStrength = 5;

void setup() {
  pinMode(FunctionStatePin, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
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
    Serial.print("亮度:");
    Serial.print(LightStrength);
    Serial.print(" | 混光:");
    Serial.println(ColorTemperature);
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
    Serial.print("亮度:");
    Serial.print(LightStrength);
    Serial.print(" | 混光:");
    Serial.println(ColorTemperature);
  }
}
