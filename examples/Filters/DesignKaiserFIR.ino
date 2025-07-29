#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  int numTaps = 5;
  float beta = 0.5;
  float* coeffs = new float[numTaps];

  dsp.designKaiserFIR(coeffs, numTaps, beta);

  Serial.print("Kaiser FIR Coefficients: ");
  for (int i = 0; i < numTaps; i++) {
    Serial.print(coeffs[i]);
    Serial.print(" ");
  }
  Serial.println();

  delete[] coeffs;
}

void loop() {
}
