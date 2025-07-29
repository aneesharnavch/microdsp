#include "dspFilters.h"
#include <math.h>
#include <algorithm>
#include <vector>
#include <cmath>

namespace dspFilters {

    void movingAverage(float* data, size_t len, size_t windowSize) {
        std::vector<float> buffer(len);
        for (size_t i = 0; i < len; ++i) {
            size_t start = (i < windowSize) ? 0 : i - windowSize + 1;
            float sum = 0;
            size_t count = 0;
            for (size_t j = start; j <= i && j < len; ++j) {
                sum += data[j];
                ++count;
            }
            buffer[i] = sum / count;
        }
        for (size_t i = 0; i < len; ++i) {
            data[i] = buffer[i];
        }
    }

    void medianFilter(float* data, size_t len, size_t windowSize) {
        std::vector<float> buffer(len);
        std::vector<float> window;

        for (size_t i = 0; i < len; ++i) {
            window.clear();
            size_t start = (i < windowSize) ? 0 : i - windowSize / 2;
            size_t end = std::min(len, i + windowSize / 2 + 1);
            for (size_t j = start; j < end; ++j) {
                window.push_back(data[j]);
            }
            std::sort(window.begin(), window.end());
            buffer[i] = window[window.size() / 2];
        }

        for (size_t i = 0; i < len; ++i) {
            data[i] = buffer[i];
        }
    }

    void gaussianFilter(float* data, size_t len, float sigma) {
        int radius = std::ceil(3 * sigma);
        std::vector<float> kernel(2 * radius + 1);
        float sum = 0.0;
        for (int i = -radius; i <= radius; ++i) {
            kernel[i + radius] = std::exp(-(i * i) / (2 * sigma * sigma));
            sum += kernel[i + radius];
        }
        for (auto& k : kernel) k /= sum;

        std::vector<float> buffer(len, 0);
        for (size_t i = 0; i < len; ++i) {
            float filtered = 0;
            for (int j = -radius; j <= radius; ++j) {
                int idx = i + j;
                if (idx >= 0 && idx < len) {
                    filtered += data[idx] * kernel[j + radius];
                }
            }
            buffer[i] = filtered;
        }
        for (size_t i = 0; i < len; ++i) {
            data[i] = buffer[i];
        }
    }

    void applyFIR(float* data, size_t len, float* coeffs, size_t coeffLen) {
        std::vector<float> output(len);
        for (size_t i = 0; i < len; i++) {
            float sum = 0.0;
            for (size_t j = 0; j < coeffLen; j++) {
                if (i >= j) sum += coeffs[j] * data[i - j];
            }
            output[i] = sum;
        }
        for (size_t i = 0; i < len; ++i) {
            data[i] = output[i];
        }
    }

    void designKaiserFIR(float* coeffs, int numTaps, float beta) {
        for (int n = 0; n < numTaps; n++) {
            float ratio = 2.0f * n / (numTaps - 1) - 1.0f;
            float window = bessi0(beta * sqrtf(1 - ratio * ratio)) / bessi0(beta);
            coeffs[n] = window; // Placeholder: integrate with ideal sinc or freq kernel
        }
    }

    void frequencySamplingFIR(float* coeffs, size_t numTaps, float* desiredResponse) {
        // Basic inverse DFT FIR from desired mag response
        for (size_t n = 0; n < numTaps; n++) {
            coeffs[n] = 0.0;
            for (size_t k = 0; k < numTaps; k++) {
                coeffs[n] += desiredResponse[k] * cosf(2 * M_PI * k * n / numTaps);
            }
            coeffs[n] /= numTaps;
        }
    }

    void adaptiveFilter(float* data, float* reference, size_t len, float mu) {
        float w = 0.0f;
        for (size_t i = 0; i < len; ++i) {
            float y = w * reference[i];
            float e = data[i] - y;
            w += mu * e * reference[i];
            data[i] = y;
        }
    }

    void wienerFilter(float* data, size_t len, float signalVar, float noiseVar) {
        float gain = signalVar / (signalVar + noiseVar);
        for (size_t i = 0; i < len; ++i) {
            data[i] *= gain;
        }
    }

    float bessi0(float x) {
        float ax = fabsf(x);
        float y = 0.0;

        if (ax < 3.75f) {
            y = x / 3.75f;
            y *= y;
            return 1.0f + y * (3.5156229f + y * (3.0899424f + y * (1.2067492f + y * (0.2659732f + y * (0.0360768f + y * 0.0045813f)))));
        }
        else {
            y = 3.75f / ax;
            return (expf(ax) / sqrtf(ax)) * (0.39894228f + y * (0.01328592f + y * (0.00225319f + y * (-0.00157565f + y * (0.00916281f + y * (-0.02057706f + y * (0.02635537f + y * (-0.01647633f + y * 0.00392377f))))))));
        }
    }
}
