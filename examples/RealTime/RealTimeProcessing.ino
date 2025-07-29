#include <microdsp.h>

MicroDSP dsp;

// Create a real-time moving average filter with a window size of 10
auto rtMovingAverage = dsp.realTimeMovingAverage(10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read a value from the analog pin
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);

  // Update the filter with the new value and get the filtered value
  float filteredVoltage = rtMovingAverage.update(voltage);

  // Print the filtered value
  Serial.println(filteredVoltage);

  delay(100);
}
