#include "dspRealTimeTransforms.h"
#include <cmath>
#include <algorithm>

namespace dspRealTime {

RealTimeFFT::RealTimeFFT(size_t windowSize) :
    windowSize(windowSize),
    bufferFull(false) {
    buffer.reserve(windowSize);
    real.resize(windowSize);
    imag.resize(windowSize);
}

void RealTimeFFT::update(float newValue) {
    if (buffer.size() < windowSize) {
        buffer.push_back(newValue);
    } else {
        bufferFull = true;
        buffer.erase(buffer.begin());
        buffer.push_back(newValue);
    }

    if (bufferFull) {
        fft();
    }
}

const std::vector<float>& RealTimeFFT::getReal() {
    return real;
}

const std::vector<float>& RealTimeFFT::getImag() {
    return imag;
}

void RealTimeFFT::fft() {
    for (size_t i = 0; i < windowSize; ++i) {
        real[i] = buffer[i];
        imag[i] = 0.0;
    }

    if (windowSize <= 1) return;

    // Bit-reversal permutation
    for (size_t i = 1, j = 0; i < windowSize; i++) {
        size_t bit = windowSize >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            std::swap(real[i], real[j]);
            std::swap(imag[i], imag[j]);
        }
    }

    // Cooley-Tukey FFT
    for (size_t len = 2; len <= windowSize; len <<= 1) {
        double angle = -2.0 * M_PI / len;
        float wlen_real = cos(angle);
        float wlen_imag = sin(angle);
        for (size_t i = 0; i < windowSize; i += len) {
            float w_real = 1.0;
            float w_imag = 0.0;
            for (size_t j = 0; j < len / 2; j++) {
                float u_real = real[i + j];
                float u_imag = imag[i + j];
                float v_real = real[i + j + len / 2] * w_real - imag[i + j + len / 2] * w_imag;
                float v_imag = real[i + j + len / 2] * w_imag + imag[i + j + len / 2] * w_real;
                real[i + j] = u_real + v_real;
                imag[i + j] = u_imag + v_imag;
                real[i + j + len / 2] = u_real - v_real;
                imag[i + j + len / 2] = u_imag - v_imag;
                float next_w_real = w_real * wlen_real - w_imag * wlen_imag;
                w_imag = w_real * wlen_imag + w_imag * wlen_real;
                w_real = next_w_real;
            }
        }
    }
}

}
