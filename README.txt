# MicroDSP

A lightweight and efficient digital signal processing (DSP) library for microcontrollers.

## Features

- **Statistics:** Mean, standard deviation, and outlier detection (Z-score, modified Z-score, IQR, MAD).
- **Calculus:** Numerical differentiation and integration.
- **Filtering:** Moving average, median, Gaussian, FIR, and adaptive filters.
- **Transforms:** Fast Fourier Transform (FFT), Inverse FFT, and Laplace transform.
- **Resource Management:** Control CPU usage and monitor memory consumption.
- **Exporting:** Export data to the serial port in CSV format.

## Usage

To use the MicroDSP library, include the `microdsp.h` header file in your sketch and create a `MicroDSP` object.

```cpp
#include "microdsp.h"

MicroDSP dsp;

void setup() {
  // ...
}

void loop() {
  // ...
  float data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  size_t len = sizeof(data) / sizeof(data[0]);

  // Calculate the mean of the data
  float mean = dsp.mean(data, len);

  // Apply a moving average filter
  dsp.movingAverageFilter(data, len, 2);

  // Export the filtered data to the serial port
  dsp.exportToSerial(data, len, "Filtered Data");
  // ...
}
```

## API

For a complete list of available functions, please refer to the `microdsp.h` header file.
