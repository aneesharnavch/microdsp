#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  dsp.setComputeLimit(80);

  Serial.print("Compute Limit: ");
  Serial.println(dsp.getComputeLimit());
}

void loop() {
}
