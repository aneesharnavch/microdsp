#ifndef DSP_TRANSFORMS_H
#define DSP_TRANSFORMS_H

#include <stddef.h>

namespace dspTransforms {

    void fft(float* real, float* imag, size_t n);
    void ifft(float* real, float* imag, size_t n);

    void laplaceTransform(float* input, float* outputReal, float* outputImag, size_t len, float sReal, float sImag);

}

#endif
