#include <FreqCount.h>

void setup() {
  Serial.begin(57600);
  FreqCount.begin(1000);
}

void loop() {
  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    Serial.println(count);
  }
}
