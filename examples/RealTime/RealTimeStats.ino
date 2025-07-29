#include <microdsp.h>

MicroDSP dsp;
auto rtStats = dsp.realTimeStats(10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);

  rtStats.update(voltage);

  Serial.print("Mean: ");
  Serial.print(rtStats.getMean());
  Serial.print(" StdDev: ");
  Serial.println(rtStats.getStdDev());

  delay(100);
}
