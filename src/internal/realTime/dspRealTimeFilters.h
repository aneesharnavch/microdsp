#ifndef DSP_REALTIME_FILTERS_H
#define DSP_REALTIME_FILTERS_H

#include <stddef.h>
#include <vector>

namespace dspRealTime {

class RealTimeMovingAverage {
public:
    RealTimeMovingAverage(size_t windowSize);
    float update(float newValue);

private:
    std::vector<float> buffer;
    size_t windowSize;
    size_t currentIndex;
    float sum;
};

class RealTimeMedianFilter {
public:
    RealTimeMedianFilter(size_t windowSize);
    float update(float newValue);

private:
    std::vector<float> buffer;
    size_t windowSize;
};

class RealTimeGaussianFilter {
public:
    RealTimeGaussianFilter(size_t windowSize, float sigma);
    float update(float newValue);

private:
    std::vector<float> buffer;
    std::vector<float> kernel;
    size_t windowSize;
};

}

#endif
