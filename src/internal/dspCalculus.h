#ifndef DSP_CALCULUS_H
#define DSP_CALCULUS_H

#include <stddef.h>

namespace dspCalculus {

    float* nthDerivative(float* data, size_t len, float dt, int order, size_t& outLen);
    float definiteIntegral(float* data, size_t len, float dx);

    float tripleIntegral(float*** data, size_t xLen, size_t yLen, size_t zLen, float dx, float dy, float dz);

}

#endif
