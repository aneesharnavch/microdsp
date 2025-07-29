#include "dspRealTimeStats.h"
#include <numeric>
#include <algorithm>
#include <cmath>

namespace dspRealTime {

RealTimeStats::RealTimeStats(size_t windowSize) :
    windowSize(windowSize),
    currentIndex(0),
    bufferFull(false),
    sum(0.0),
    sumSq(0.0) {
    buffer.reserve(windowSize);
}

void RealTimeStats::update(float newValue) {
    if (buffer.size() < windowSize) {
        buffer.push_back(newValue);
    } else {
        bufferFull = true;
        sum -= buffer[currentIndex];
        sumSq -= buffer[currentIndex] * buffer[currentIndex];
        buffer[currentIndex] = newValue;
    }

    sum += newValue;
    sumSq += newValue * newValue;

    if (bufferFull) {
        currentIndex = (currentIndex + 1) % windowSize;
    }
}

float RealTimeStats::getMean() {
    if (buffer.empty()) return 0.0;
    return sum / buffer.size();
}

float RealTimeStats::getStdDev() {
    if (buffer.size() < 2) return 0.0;
    float mean = getMean();
    return std::sqrt(sumSq / buffer.size() - mean * mean);
}

bool RealTimeStats::isZScoreOutlier(float threshold) {
    if (buffer.size() < 2) return false;
    float mean = getMean();
    float stdDev = getStdDev();
    float latestValue = bufferFull ? buffer[(currentIndex == 0) ? windowSize - 1 : currentIndex - 1] : buffer.back();
    return std::abs((latestValue - mean) / stdDev) > threshold;
}

bool RealTimeStats::isModifiedZScoreOutlier(float threshold) {
    if (buffer.size() < 2) return false;

    std::vector<float> sortedBuffer = buffer;
    std::sort(sortedBuffer.begin(), sortedBuffer.end());

    float median = (sortedBuffer.size() % 2 == 0) ?
        (sortedBuffer[sortedBuffer.size() / 2 - 1] + sortedBuffer[sortedBuffer.size() / 2]) / 2 :
        sortedBuffer[sortedBuffer.size() / 2];

    std::vector<float> deviations;
    for (float val : sortedBuffer) {
        deviations.push_back(std::abs(val - median));
    }
    std::sort(deviations.begin(), deviations.end());

    float mad = (deviations.size() % 2 == 0) ?
        (deviations[deviations.size() / 2 - 1] + deviations[deviations.size() / 2]) / 2 :
        deviations[deviations.size() / 2];

    float latestValue = bufferFull ? buffer[(currentIndex == 0) ? windowSize - 1 : currentIndex - 1] : buffer.back();
    float mz = 0.6745 * (latestValue - median) / mad;
    return std::abs(mz) > threshold;
}

bool RealTimeStats::isIQROutlier(float multiplier) {
    if (buffer.size() < 4) return false;

    std::vector<float> sortedBuffer = buffer;
    std::sort(sortedBuffer.begin(), sortedBuffer.end());

    float q1 = sortedBuffer[sortedBuffer.size() / 4];
    float q3 = sortedBuffer[3 * sortedBuffer.size() / 4];
    float iqr = q3 - q1;

    float lowerBound = q1 - multiplier * iqr;
    float upperBound = q3 + multiplier * iqr;

    return buffer.back() < lowerBound || buffer.back() > upperBound;
}

}
