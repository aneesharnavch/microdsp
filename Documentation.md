## Resource Management and Export

**CPU/Memory Hooks**

Functions to monitor memory consumption, CPU load, and provide user feedback or throttle.

**Serial Export**
```c++
dsp.exportToSerial(data, len, "Label");
```
Prints CSV data, optionally with label, to UART or USB for data logging. Can be run through the custom decoder to obtain it in CSV form. (Done via python script in main repository)

**Examples for Implementation**

For more detailed examples , check out the examples folder . 

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
# Full Feature Reference

## 1. Arithmetic Mean

**Mathematical Definition**

$$
\mu = \frac{1}{n} \sum_{i=1}^{n} x_i
$$

**Microcontroller Implementation**

Iterates through the array, sums all values, then divides by the length.
```c++
float sum = 0;
for (size_t i = 0; i < len; ++i)
sum += data[i];
float mean = sum / len;
```

## 2. Standard Deviation

**Mathematical Definition**

$$
\mu = \frac{1}{n} \sum_{i=1}^{n} x_i \qquad
\sigma = \sqrt{ \frac{1}{n} \sum_{i=1}^{n} (x_i - \mu)^2 }
$$

**Microcontroller Implementation**

First pass: Find the mean as above. Second pass: Subtract mean, square result, sum, divide, and take square root.

```c++
float sum_sq = 0.0;
for (size_t i = 0; i < len; ++i)
sum_sq += (data[i] - mean) * (data[i] - mean);
float stddev = sqrt(sum_sq / len);
```

## 3. Z-score Outlier Detection

**Mathematical Definition**

$$
z = \frac{x - \mu}{\sigma}
$$

**Microcontroller Implementation**

Compute mean and standard deviation using the algorithms above, then for each sample.

## 4. Modified Z-score Outlier Detection

**Mathematical Definition**

$$
M_z = 0.6745 \frac{x_i - \text{median}}{\mathrm{MAD}}
$$

where MAD is *Median Absolute Deviation*.

**Microcontroller Implementation**

- Sort the array to find the median.
- Compute MAD as the median of $$ |x_i - \text{median}| $$


## 5. IQR (Interquartile Range) Outlier Detection

**Mathematical Definition**

$$
\mathrm{IQR} = Q_3 - Q_1
$$

$$
x\ \text{is an outlier if}\ x < Q_1 - m\,\mathrm{IQR}\ \text{or}\ x > Q_3 + m\,\mathrm{IQR}
$$

where 'm' is a multiplier (typically 1.5).

**Microcontroller Implementation**

- Sort array, calculate quartiles (with linear interpolation if needed).
- For each 'x' check the outlier criterion above.

## 6. Numerical Derivatives (All Orders)

**Mathematical Definition**

- nth derivative:
  $$
  f^{(n)}(x) = \frac{d^n}{dx^n} f(x)
  $$

- First-order discrete approximation:
  $$
  f'(x) \approx \frac{f(x+h) - f(x)}{h}
  $$
  Where $$ h = dt $$ (sample interval).

- Higher orders (recursive):
  $$
  f^{(n)}(x) \approx \frac{f^{(n-1)}(x+h) - f^{(n-1)}(x)}{h}
  $$

**Microcontroller Implementation**

First order:
```c++
for (size_t i = 0; i < len - 1; ++i)
deriv[i] = (data[i + 1] - data[i]) / dt;
```
Higher order (nth):
```c++
float* nth_derivative = data;
for (int order = 1; order <= n; ++order) {
for (int i = 0; i < len - order; ++i)
next_derivative[i] = (nth_derivative[i + 1] - nth_derivative[i]) / dt;
nth_derivative = next_derivative;
}
```

*Note: Array length decreases by one for each derivative order.*

## 7. Numerical Integration (All Orders)

**Mathematical Definition**

- Single definite integral:
  $$
  \int_a^b f(x)\,dx \approx \sum_{i=1}^{n} f(x_i) \cdot \Delta x
  $$

- Multiple integrals: Integrate already-integrated values as needed.

**Microcontroller Implementation**
```c++
float area = 0;
for (size_t i = 0; i < len; ++i)
area += data[i] * dx;
```

Double integral (second order, for example):
```c++
// First integration
int1[0] = data[0] * dx;
for (i = 1; i < len; ++i)
    int1[i] = int1[i-1] + data[i] * dx;

// Second integration
int2[0] = int1[0] * dx;
for (i = 1; i < len; ++i)
    int2[i] = int2[i-1] + int1[i] * dx;
```

## 8. Moving Average Filter

**Mathematical Definition**

$$
y_i = \frac{1}{N} \sum_{j=0}^{N-1} x_{i-j}
$$

where 'N' is window size.

**Microcontroller Implementation**

For each output, sum the previous N samples, divide by N.

## 9. Median Filter

**Mathematical Definition**

$$
y_i = \text{median}(x_{i-k}, \ldots, x_i, ..., x_{i+k})
$$

where window size is $$ 2k+1 $$


## 10. Gaussian Filter

**Mathematical Definition**

$$
y_i = \sum_{j=-R}^{R} x_{i-j} \cdot G(j)
$$

$$
G(j) = \frac{1}{\sqrt{2\pi \sigma^2}} \exp\left( -\frac{j^2}{2\sigma^2} \right )
$$

**Microcontroller Implementation**

- Precompute kernel G(j) with j in [-R, R] 
- For each output, take a window, multiply by kernel, sum.
```c
// Precompute Gaussian kernel
float kernel[2*R+1];
float sigma = 1.0; // adjust as needed
for (int j = -R; j <= R; ++j) {
    kernel[j+R] = (1.0 / sqrt(2 * M_PI * sigma * sigma)) * 
                  exp(-(j * j) / (2 * sigma * sigma));
}

// Apply filter
for (int i = R; i < len - R; ++i) {
    float sum = 0;
    for (int j = -R; j <= R; ++j) {
        sum += data[i + j] * kernel[j + R];
    }
    output[i] = sum;
}
```

## 11. FIR Filter (Finite Impulse Response)

**Mathematical Definition**

$$
y_i = \sum_{j=0}^{M-1} x_{i-j} \cdot c_j
$$


**Microcontroller Implementation**

Multiply current and previous  M-1 ,data by coefficients and sum for each output.
```c++
// Assuming coefficients c[] are predefined
for (int i = M-1; i < len; ++i) {
    float sum = 0;
    for (int j = 0; j < M; ++j) {
        sum += data[i - j] * c[j];
    }
    output[i] = sum;
}
```
## 12. FFT — Fast Fourier Transform

**Mathematical Definition**

$$
X_k = \sum_{n=0}^{N-1} x_n \cdot e^{-i2\pi kn/N}
$$

**Microcontroller Implementation**

- Recursive function.
- Arrays for real and imaginary parts.
- Many additions and multiplications per output bin.
```c++
void fft(float real[], float imag[], int N) {
    // Bit-reverse permutation
    for (int i = 1, j = 0; i < N; i++) {
        int bit = N >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) {
            swap(real[i], real[j]);
            swap(imag[i], imag[j]);
        }
    }
    // Butterfly operations
    for (int len = 2; len <= N; len <<= 1) {
        float wlen_real = cos(2 * M_PI / len);
        float wlen_imag = -sin(2 * M_PI / len);
        for (int i = 0; i < N; i += len) {
            float w_real = 1, w_imag = 0;
            for (int j = 0; j < len / 2; ++j) {
                float u_real = real[i + j];
                float u_imag = imag[i + j];
                float v_real = real[i + j + len/2] * w_real - imag[i + j + len/2] * w_imag;
                float v_imag = real[i + j + len/2] * w_imag + imag[i + j + len/2] * w_real;
                real[i + j] = u_real + v_real;
                imag[i + j] = u_imag + v_imag;
                real[i + j + len/2] = u_real - v_real;
                imag[i + j + len/2] = u_imag - v_imag;

                float temp = w_real * wlen_real - w_imag * wlen_imag;
                w_imag = w_real * wlen_imag + w_imag * wlen_real;
                w_real = temp;
            }
        }
    }
}
```
## 13. IFFT — Inverse FFT

**Mathematical Definition**

$$
x_n = \frac{1}{N} \sum_{k=0}^{N-1} X_k \cdot e^{i2\pi kn/N}
$$

**Microcontroller Implementation**

- Structured similarly to FFT.
- Use conjugate exponent and normalize output by 1/N
```c++
// Inverse FFT (conjugate input, FFT, conjugate output, scale by 1/N)
void ifft(float real[], float imag[], int N) {
    // Conjugate input
    for (int i = 0; i < N; ++i) {
        imag[i] = -imag[i];
    }
  
    // Apply FFT
    fft(real, imag, N);

    // Conjugate output and scale by 1/N
    for (int i = 0; i < N; ++i) {
        real[i] /= N;
        imag[i] = -imag[i] / N;
    }
}
```
## 14. Laplace Transform (Numerical)

**Mathematical Definition**

$$
F(s) = \int_{0}^{\infty} f(t)\, e^{-st} \,dt \qquad s = \sigma + i\omega
$$

**Microcontroller Implementation**

Numerically approximate the integral by summing discrete samples:
```c
for (size_t i = 0; i < len; ++i) {
F_real += data[i] * exp(-s_real * t[i]) * cos(s_imag * t[i]) * dt;
F_imag += data[i] * exp(-s_real * t[i]) * sin(s_imag * t[i]) * dt;
}
```

