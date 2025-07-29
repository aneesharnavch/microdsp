#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  size_t numTaps = 5;
  float desiredResponse[] = {1.0, 0.5, 0.2, 0.1, 0.05};
  float* coeffs = new float[numTaps];

  dsp.frequencySamplingFIR(coeffs, numTaps, desiredResponse);

  Serial.print("Frequency Sampling FIR Coefficients: ");
  for (size_t i = 0; i < numTaps; i++) {
    Serial.print(coeffs[i]);
    Serial.print(" ");
  }
  Serial.println();

  delete[] coeffs;
}

void loop() {
}
