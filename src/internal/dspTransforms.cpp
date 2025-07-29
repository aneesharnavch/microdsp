#include "dspTransforms.h"
#include <math.h>

namespace dspTransforms {

    void fft(float* real, float* imag, size_t n) {
        if (n <= 1) return;

        float* evenReal = new float[n / 2];
        float* evenImag = new float[n / 2];
        float* oddReal = new float[n / 2];
        float* oddImag = new float[n / 2];

        for (size_t i = 0; i < n / 2; i++) {
            evenReal[i] = real[2 * i];
            evenImag[i] = imag[2 * i];
            oddReal[i] = real[2 * i + 1];
            oddImag[i] = imag[2 * i + 1];
        }

        fft(evenReal, evenImag, n / 2);
        fft(oddReal, oddImag, n / 2);

        for (size_t k = 0; k < n / 2; k++) {
            float tReal = cos(-2 * M_PI * k / n) * oddReal[k] - sin(-2 * M_PI * k / n) * oddImag[k];
            float tImag = sin(-2 * M_PI * k / n) * oddReal[k] + cos(-2 * M_PI * k / n) * oddImag[k];

            real[k] = evenReal[k] + tReal;
            imag[k] = evenImag[k] + tImag;
            real[k + n / 2] = evenReal[k] - tReal;
            imag[k + n / 2] = evenImag[k] - tImag;
        }

        delete[] evenReal;
        delete[] evenImag;
        delete[] oddReal;
        delete[] oddImag;
    }

    void ifft(float* real, float* imag, size_t n) {
        for (size_t i = 0; i < n; i++) {
            imag[i] = -imag[i];
        }

        fft(real, imag, n);

        for (size_t i = 0; i < n; i++) {
            real[i] /= n;
            imag[i] = -imag[i] / n;
        }
    }

    void laplaceTransform(float* input, float* outputReal, float* outputImag, size_t len, float sReal, float sImag) {
        for (size_t t = 0; t < len; t++) {
            float e = expf(-sReal * t);
            outputReal[t] = input[t] * e * cosf(-sImag * t);
            outputImag[t] = input[t] * e * sinf(-sImag * t);
        }
    }

}
