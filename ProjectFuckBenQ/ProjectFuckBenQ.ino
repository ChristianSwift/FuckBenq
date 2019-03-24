#include <Encoder.h>

long oldPosition = 0;
long newPosition = 0;

Encoder myEnc(D2, D3);
const int FunctionStatePin = D1;
int ColorTemperature = 5;
int LightStrength = 5;

void setup() {
  pinMode(FunctionStatePin, INPUT);
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
}

void loop() {
  long newPosition = myEnc.read()/4;
  if (newPosition > oldPosition) {
    oldPosition = newPosition;
    if (digitalRead(FunctionStatePin) == HIGH) {
      ColorTemperature++;
    } else {
      LightStrength++;
    }
    Serial.print(ColorTemperature);
    Serial.print("|");
    Serial.println(LightStrength);
  }else if (newPosition < oldPosition) {
    oldPosition = newPosition;
    if (digitalRead(FunctionStatePin) == HIGH) {
      ColorTemperature--;
    } else {
      LightStrength--;
    }
    Serial.print(ColorTemperature);
    Serial.print("|");
    Serial.println(LightStrength);
  }
}
