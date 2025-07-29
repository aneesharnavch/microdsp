#ifndef DSP_REALTIME_STATS_H
#define DSP_REALTIME_STATS_H

#include <stddef.h>
#include <vector>

namespace dspRealTime {

class RealTimeStats {
public:
    RealTimeStats(size_t windowSize);
    void update(float newValue);
    float getMean();
    float getStdDev();
    bool isZScoreOutlier(float threshold = 3.0);
    bool isModifiedZScoreOutlier(float threshold = 3.5);
    bool isIQROutlier(float multiplier = 1.5);

private:
    std::vector<float> buffer;
    size_t windowSize;
    size_t currentIndex;
    bool bufferFull;
    float sum;
    float sumSq;
};

}

#endif
