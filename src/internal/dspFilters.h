#ifndef DSP_FILTERS_H
#define DSP_FILTERS_H

#include <stddef.h>

namespace dspFilters {

    void movingAverage(float* data, size_t len, size_t windowSize);
    void medianFilter(float* data, size_t len, size_t windowSize);
    void gaussianFilter(float* data, size_t len, float sigma);
    void applyFIR(float* data, size_t len, float* coeffs, size_t coeffLen);
    void designKaiserFIR(float* coeffs, int numTaps, float beta);
    void frequencySamplingFIR(float* coeffs, size_t numTaps, float* desiredResponse);
    void adaptiveFilter(float* data, float* reference, size_t len, float mu);
    void wienerFilter(float* data, size_t len, float signalVar, float noiseVar);
    float bessi0(float x);

}

#endif
