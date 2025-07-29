
# mirodsp 
microdsp (micro digital signal processing) is a lightweight signal processing library made for resource-constrained signal processing on microcontrollers. Refer to examples for detailed instructions on implementation, and refer to the documentation for further information.  
# Features Overview

**Statistics**

- Arithmetic Mean
- Standard Deviation
- Outlier Detection:
  - Z-score
  - Modified Z-score
  - Interquartile Range (IQR)
  - Median Absolute Deviation (MAD)

**Calculus**

- Numerical derivatives
- Definite integrals
- Multiple integrals

**Filtering**

- Moving Average filter
- Median filter
- Gaussian filter
- Finite Impulse Response (FIR) filter

**Transforms**

- Fast Fourier Transform (FFT)
- Inverse FFT (IFFT)
- Laplace Transform (numerical implementation)

**Resource Management**

- CPU throttle hooks
- Memory profiling

**Data Export**

- Serial output
- CSV output

**Real-Time Support**

All core math functions can operate on sliding-window data for streaming applications.

## Resource Management and Export

**CPU/Memory Hooks**

Functions to monitor memory consumption, CPU load, and provide user feedback or throttle.

**Serial Export**
```c++
dsp.exportToSerial(data, len, "Label");
```
Prints CSV data, optionally with label, to UART or USB for data logging. Can be run through the custom decoder to obtain it in CSV form. (Done via python script in main repository)

**Examples for Implementation**

For more detailed examples, check out the examples folder. 

*Implementations of resource control* 
```c++
#include <Arduino.h>
#include "microdsp.h"
#include "internal/dspResources/dspResources.h"

MicroDSP dsp;

void setup() {
    Serial.begin(9600);
    while (!Serial);  // Wait for serial monitor to open (optional on some boards)

    // === DSP Resource System Initialization ===
    dspResources::init();  // Must call before using any resource-tracked DSP features

    // Set Memory Threshold (in bytes)
    dspResources::setFreeMemoryThreshold(500);  // Only process if >500 bytes of RAM available

    // Set Compute Load Limit (as a fraction 0.0 to 1.0) in terms of %
    dspResources::setComputeLimit(0.6);  // Max 60% CPU load budget
}
```
*For dynamic computation load handling*
```c++
if (dspResources::getAvailableMemory() < 300) {
    Serial.println("Low memory: switching to low-res mode.");
    // Use reduced-size data or simplified algorithm
}
```
*For Compute Limitations (CPU)*
```c++
if (!dspResources::checkLoad(0.5)) { // Don't exceed 50% of set limit
    Serial.println("System too busy, skipping transform.");
}
```
*RAM utilization checks* 
```c++
if (dspResources::canProcess(sizeof(float) * dataLen)) {
    // Proceed with computation
} else {
    // Skip or reduce workload
}
```
## Real-Time Windowed Operations

All statistical, calculus, filter, and transform functions are available in streaming (sliding window) mode for live sensor/microphone data processing.

The real-time classes internally shift old values and compute outputs efficiently as new samples arrive.

## Data Types and Constraints

**Data arrays:** Input and output arrays must be floating point (unless specified otherwise).

**Lengths:** All transform/filter lengths must be powers of two where required; window/filter sizes must be smaller than input arrays.

**Memory:** Library uses stack-based arrays by default; memory use is proportional to array sizes and filter orders.

## Example Applications

- Smoothing and denoising sensor data for robotics
- Real-time frequency analysis of sampled audio or vibration
- Feature extraction for machine learning on embedded platforms
- Outlier and anomaly detection in physical systems
- Basic calculus operations (velocity/acceleration from position, etc.)


## License

microdsp is released under the MIT License.
