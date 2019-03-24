#include <Encoder.h>

Encoder myEnc(D2, D3);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
}

void loop() {
  Serial.println(myEnc.read()/4);
}
