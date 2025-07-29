#include "dspRealTimeFilters.h"
#include <numeric>
#include <algorithm>
#include <cmath>

namespace dspRealTime {

//--- RealTimeMovingAverage ---
RealTimeMovingAverage::RealTimeMovingAverage(size_t windowSize) :
    windowSize(windowSize),
    currentIndex(0),
    sum(0.0) {
    buffer.reserve(windowSize);
}

float RealTimeMovingAverage::update(float newValue) {
    if (buffer.size() < windowSize) {
        buffer.push_back(newValue);
        sum += newValue;
    } else {
        sum -= buffer[currentIndex];
        buffer[currentIndex] = newValue;
        sum += newValue;
        currentIndex = (currentIndex + 1) % windowSize;
    }
    return sum / buffer.size();
}

//--- RealTimeMedianFilter ---
RealTimeMedianFilter::RealTimeMedianFilter(size_t windowSize) :
    windowSize(windowSize) {
    buffer.reserve(windowSize);
}

float RealTimeMedianFilter::update(float newValue) {
    if (buffer.size() < windowSize) {
        buffer.push_back(newValue);
    } else {
        buffer.erase(buffer.begin());
        buffer.push_back(newValue);
    }

    std::vector<float> sortedBuffer = buffer;
    std::sort(sortedBuffer.begin(), sortedBuffer.end());

    return (sortedBuffer.size() % 2 == 0) ?
        (sortedBuffer[sortedBuffer.size() / 2 - 1] + sortedBuffer[sortedBuffer.size() / 2]) / 2 :
        sortedBuffer[sortedBuffer.size() / 2];
}

//--- RealTimeGaussianFilter ---
RealTimeGaussianFilter::RealTimeGaussianFilter(size_t windowSize, float sigma) :
    windowSize(windowSize) {
    buffer.reserve(windowSize);

    int radius = windowSize / 2;
    kernel.resize(windowSize);
    float sum = 0.0;
    for (int i = -radius; i <= radius; ++i) {
        kernel[i + radius] = std::exp(-(i * i) / (2 * sigma * sigma));
        sum += kernel[i + radius];
    }
    for (auto& k : kernel) k /= sum;
}

float RealTimeGaussianFilter::update(float newValue) {
    if (buffer.size() < windowSize) {
        buffer.push_back(newValue);
    } else {
        buffer.erase(buffer.begin());
        buffer.push_back(newValue);
    }

    float filteredValue = 0.0;
    for (size_t i = 0; i < buffer.size(); ++i) {
        filteredValue += buffer[i] * kernel[i];
    }

    return filteredValue;
}

}
