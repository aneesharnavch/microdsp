#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  float data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  size_t len = sizeof(data) / sizeof(data[0]);

  dsp.exportToSerial(data, len, "My Data");
}

void loop() {
}
