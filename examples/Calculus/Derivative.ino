#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  float data[] = {1.0, 2.0, 4.0, 7.0, 11.0};
  size_t len = sizeof(data) / sizeof(data[0]);
  size_t outLen;

  float* derivative = dsp.derivative(data, len, 1.0, 1, outLen);

  Serial.print("Derivative: ");
  for (size_t i = 0; i < outLen; i++) {
    Serial.print(derivative[i]);
    Serial.print(" ");
  }
  Serial.println();

  delete[] derivative;
}

void loop() {
}
