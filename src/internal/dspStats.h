#ifndef DSP_STATS_H
#define DSP_STATS_H

#include <stddef.h>

namespace dspStats {

    float mean(float* data, size_t len);
    float stdDev(float* data, size_t len);

    // Outlier detection
    bool isZScoreOutlier(float val, float* data, size_t len, float threshold = 3.0);
    bool isModifiedZScoreOutlier(float val, float* data, size_t len, float threshold = 3.5);
    bool isIQROutlier(float val, float* data, size_t len, float multiplier = 1.5);
    bool isMADOutlier(float val, float* data, size_t len, float threshold = 3.5);

}

#endif
