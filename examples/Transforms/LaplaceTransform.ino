#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  size_t len = 5;
  float input[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float* real = new float[len];
  float* imag = new float[len];

  dsp.laplaceTransform(input, real, imag, len, 1.0, 1.0);

  Serial.println("Laplace Transform:");
  for (size_t i = 0; i < len; i++) {
    Serial.print(real[i]);
    Serial.print(" + ");
    Serial.print(imag[i]);
    Serial.println("i");
  }

  delete[] real;
  delete[] imag;
}

void loop() {
}
