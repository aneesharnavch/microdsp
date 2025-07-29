#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  float data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  size_t len = sizeof(data) / sizeof(data[0]);
  float coeffs[] = {0.2, 0.2, 0.2, 0.2, 0.2};
  size_t coeffLen = sizeof(coeffs) / sizeof(coeffs[0]);

  dsp.applyFIR(data, len, coeffs, coeffLen);

  Serial.print("FIR Filter: ");
  for (size_t i = 0; i < len; i++) {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
}
