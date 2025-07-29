#include <microdsp.h>

MicroDSP dsp;
auto rtFFT = dsp.realTimeFFT(16);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);

  rtFFT.update(voltage);

  const auto& real = rtFFT.getReal();
  const auto& imag = rtFFT.getImag();

  for (size_t i = 0; i < real.size(); i++) {
    float mag = sqrt(real[i] * real[i] + imag[i] * imag[i]);
    Serial.print(mag);
    Serial.print(" ");
  }
  Serial.println();

  delay(100);
}
