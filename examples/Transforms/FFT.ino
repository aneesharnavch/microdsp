#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  size_t len = 8;
  float* real = new float[len]{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  float* imag = new float[len]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  dsp.fft(real, imag, len);

  Serial.println("FFT:");
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
