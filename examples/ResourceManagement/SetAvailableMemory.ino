#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  dsp.setAvailableMemory(1024);

  Serial.println("Available memory set to 1024 bytes.");
}

void loop() {
}
