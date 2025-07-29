#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  size_t len = 8;
  float* real = new float[len]{4.0, 1.0, -2.414, 1.0, 0.0, 1.0, -0.414, 1.0};
  float* imag = new float[len]{0.0, -2.414, 0.0, -0.414, 0.0, 0.414, 0.0, 2.414};

  dsp.ifft(real, imag, len);

  Serial.println("IFFT:");
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
