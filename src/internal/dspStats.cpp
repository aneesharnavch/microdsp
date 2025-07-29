#include "dspStats.h"
#include <math.h>
#include <algorithm>

namespace dspStats {

    float mean(float* data, size_t len) {
        float sum = 0.0;
        for (size_t i = 0; i < len; i++) {
            sum += data[i];
        }
        return sum / len;
    }

    float stdDev(float* data, size_t len) {
        float m = mean(data, len);
        float sumSq = 0.0;
        for (size_t i = 0; i < len; i++) {
            float diff = data[i] - m;
            sumSq += diff * diff;
        }
        return sqrt(sumSq / len);
    }

    bool isZScoreOutlier(float val, float* data, size_t len, float threshold) {
        float m = mean(data, len);
        float sd = stdDev(data, len);
        float z = fabs((val - m) / sd);
        return z > threshold;
    }

    bool isModifiedZScoreOutlier(float val, float* data, size_t len, float threshold) {
        float median = 0.0;
        float* sorted = new float[len];
        std::copy(data, data + len, sorted);
        std::sort(sorted, sorted + len);
        median = (len % 2 == 0) ?
            (sorted[len / 2 - 1] + sorted[len / 2]) / 2 :
            sorted[len / 2];

        float* deviations = new float[len];
        for (size_t i = 0; i < len; i++) {
            deviations[i] = fabs(data[i] - median);
        }

        std::sort(deviations, deviations + len);
        float mad = (len % 2 == 0) ?
            (deviations[len / 2 - 1] + deviations[len / 2]) / 2 :
            deviations[len / 2];

        float mz = 0.6745 * (val - median) / mad;

        delete[] sorted;
        delete[] deviations;

        return fabs(mz) > threshold;
    }

    bool isIQROutlier(float val, float* data, size_t len, float multiplier) {
        float* sorted = new float[len];
        std::copy(data, data + len, sorted);
        std::sort(sorted, sorted + len);

        float Q1 = sorted[len / 4];
        float Q3 = sorted[3 * len / 4];
        float IQR = Q3 - Q1;

        float lower = Q1 - multiplier * IQR;
        float upper = Q3 + multiplier * IQR;

        delete[] sorted;

        return val < lower || val > upper;
    }

    bool isMADOutlier(float val, float* data, size_t len, float threshold) {
        return isModifiedZScoreOutlier(val, data, len, threshold);
    }

}
