#include "microdsp.h"

MicroDSP::MicroDSP() {
    // Initialization if needed
}

// ==== Stats ====
float MicroDSP::mean(float* data, size_t len) {
    return dspStats::mean(data, len);
}

float MicroDSP::stdDev(float* data, size_t len) {
    return dspStats::stdDev(data, len);
}

// ==== Outliers ====
bool MicroDSP::isZScoreOutlier(float val, float* data, size_t len, float threshold) {
    return dspStats::isZScoreOutlier(val, data, len, threshold);
}

bool MicroDSP::isModifiedZScoreOutlier(float val, float* data, size_t len, float threshold) {
    return dspStats::isModifiedZScoreOutlier(val, data, len, threshold);
}

bool MicroDSP::isIQROutlier(float val, float* data, size_t len, float multiplier) {
    return dspStats::isIQROutlier(val, data, len, multiplier);
}

bool MicroDSP::isMADOutlier(float val, float* data, size_t len, float threshold) {
    return dspStats::isMADOutlier(val, data, len, threshold);
}

// ==== Calculus ====
float* MicroDSP::derivative(float* data, size_t len, float deltaT, int order, size_t& outLen) {
    return dspCalculus::nthDerivative(data, len, deltaT, order, outLen);
}

float MicroDSP::integral(float* data, size_t len, float deltaT) {
    return dspCalculus::definiteIntegral(data, len, deltaT);
}

// ==== Filters ====
void MicroDSP::movingAverageFilter(float* data, size_t len, size_t windowSize) {
    dspFilters::movingAverage(data, len, windowSize);
}

void MicroDSP::medianFilter(float* data, size_t len, size_t windowSize) {
    dspFilters::medianFilter(data, len, windowSize);
}

void MicroDSP::gaussianFilter(float* data, size_t len, float sigma) {
    dspFilters::gaussianFilter(data, len, sigma);
}

void MicroDSP::applyFIR(float* data, size_t len, float* coeffs, size_t coeffLen) {
    dspFilters::applyFIR(data, len, coeffs, coeffLen);
}

void MicroDSP::designKaiserFIR(float* coeffs, int numTaps, float beta) {
    dspFilters::designKaiserFIR(coeffs, numTaps, beta);
}

void MicroDSP::frequencySamplingFIR(float* coeffs, size_t numTaps, float* desiredResponse) {
    dspFilters::frequencySamplingFIR(coeffs, numTaps, desiredResponse);
}

void MicroDSP::adaptiveFilter(float* data, float* reference, size_t len, float mu) {
    dspFilters::adaptiveFilter(data, reference, len, mu);
}

void MicroDSP::wienerFilter(float* data, size_t len, float signalVar, float noiseVar) {
    dspFilters::wienerFilter(data, len, signalVar, noiseVar);
}

// ==== Transforms ====
void MicroDSP::fft(float* dataReal, float* dataImag, size_t len) {
    dspTransforms::fft(dataReal, dataImag, len);
}

void MicroDSP::ifft(float* dataReal, float* dataImag, size_t len) {
    dspTransforms::ifft(dataReal, dataImag, len);
}

void MicroDSP::laplaceTransform(float* input, float* outputReal, float* outputImag, size_t len, float sReal, float sImag) {
    dspTransforms::laplaceTransform(input, outputReal, outputImag, len, sReal, sImag);
}

// ==== Resource Management ====
void MicroDSP::setComputeLimit(uint8_t percent) {
    dspResources::setComputeLimit(percent);
}

uint8_t MicroDSP::getComputeLimit() {
    return dspResources::getComputeLimit();
}

void MicroDSP::setAvailableMemory(size_t bytes) {
    dspResources::setAvailableMemory(bytes);
}

// ==== Export ====
void MicroDSP::exportToSerial(const float* data, size_t len, const char* label) {
    dspDataIO::exportCSV(data, len, label);
}

// ==== Real-Time Processing ====
dspRealTime::RealTimeStats MicroDSP::realTimeStats(size_t windowSize) {
    return dspRealTime::RealTimeStats(windowSize);
}

dspRealTime::RealTimeMovingAverage MicroDSP::realTimeMovingAverage(size_t windowSize) {
    return dspRealTime::RealTimeMovingAverage(windowSize);
}

dspRealTime::RealTimeMedianFilter MicroDSP::realTimeMedianFilter(size_t windowSize) {
    return dspRealTime::RealTimeMedianFilter(windowSize);
}

dspRealTime::RealTimeGaussianFilter MicroDSP::realTimeGaussianFilter(size_t windowSize, float sigma) {
    return dspRealTime::RealTimeGaussianFilter(windowSize, sigma);
}

dspRealTime::RealTimeFFT MicroDSP::realTimeFFT(size_t windowSize) {
    return dspRealTime::RealTimeFFT(windowSize);
}
