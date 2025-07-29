#ifndef MICRODSP_H
#define MICRODSP_H

#include "internal/dspStats.h"
#include "internal/dspCalculus.h"
#include "internal/dspFilters.h"
#include "internal/dspTransforms.h"
#include "internal/dspResources.h"
#include "internal/dspDataIO.h"
#include "internal/realTime/dspRealTimeStats.h"
#include "internal/realTime/dspRealTimeFilters.h"
#include "internal/realTime/dspRealTimeTransforms.h"

class MicroDSP {
public:
    MicroDSP();

    // ==== Stats ====
    float mean(float* data, size_t len);
    float stdDev(float* data, size_t len);

    // ==== Outliers ====
    bool isZScoreOutlier(float val, float* data, size_t len, float threshold = 3.0);
    bool isModifiedZScoreOutlier(float val, float* data, size_t len, float threshold = 3.5);
    bool isIQROutlier(float val, float* data, size_t len, float multiplier = 1.5);
    bool isMADOutlier(float val, float* data, size_t len, float threshold = 3.5);

    // ==== Calculus ====
    float* derivative(float* data, size_t len, float deltaT, int order, size_t& outLen);
    float integral(float* data, size_t len, float deltaT);

    // ==== Filters ====
    void movingAverageFilter(float* data, size_t len, size_t windowSize);
    void medianFilter(float* data, size_t len, size_t windowSize);
    void gaussianFilter(float* data, size_t len, float sigma);
    void applyFIR(float* data, size_t len, float* coeffs, size_t coeffLen);
    void designKaiserFIR(float* coeffs, int numTaps, float beta);
    void frequencySamplingFIR(float* coeffs, size_t numTaps, float* desiredResponse);
    void adaptiveFilter(float* data, float* reference, size_t len, float mu);
    void wienerFilter(float* data, size_t len, float signalVar, float noiseVar);

    // ==== Transforms ====
    void fft(float* dataReal, float* dataImag, size_t len);
    void ifft(float* dataReal, float* dataImag, size_t len);
    void laplaceTransform(float* input, float* outputReal, float* outputImag, size_t len, float sReal, float sImag);

    // ==== Resource Management ====
    void setComputeLimit(uint8_t percent);
    uint8_t getComputeLimit();
    void setAvailableMemory(size_t bytes);

    // ==== Exporting ====
    void exportToSerial(const float* data, size_t len, const char* label = "");

    // ==== Real-Time Processing ====
    dspRealTime::RealTimeStats realTimeStats(size_t windowSize);
    dspRealTime::RealTimeMovingAverage realTimeMovingAverage(size_t windowSize);
    dspRealTime::RealTimeMedianFilter realTimeMedianFilter(size_t windowSize);
    dspRealTime::RealTimeGaussianFilter realTimeGaussianFilter(size_t windowSize, float sigma);
    dspRealTime::RealTimeFFT realTimeFFT(size_t windowSize);
};

#endif
