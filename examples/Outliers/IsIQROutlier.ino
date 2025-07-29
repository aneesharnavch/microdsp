#include <microdsp.h>

MicroDSP dsp;

void setup() {
  Serial.begin(9600);

  float data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 100.0};
  size_t len = sizeof(data) / sizeof(data[0]);

  bool isOutlier = dsp.isIQROutlier(100.0, data, len);

  Serial.print("Is 100.0 an IQR outlier? ");
  Serial.println(isOutlier ? "Yes" : "No");
}

void loop() {
}
