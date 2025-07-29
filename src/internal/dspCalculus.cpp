#include "dspCalculus.h"
#include <new>

namespace dspCalculus {

    float* nthDerivative(float* data, size_t len, float dt, int order, size_t& outLen) {
        if (order < 1 || len <= order) {
            outLen = 0;
            return nullptr;
        }

        float* temp = new (std::nothrow) float[len];
        if (!temp) {
            outLen = 0;
            return nullptr;
        }
        for(size_t i = 0; i < len; ++i) {
            temp[i] = data[i];
        }

        float* buffer = new (std::nothrow) float[len];
        if (!buffer) {
            delete[] temp;
            outLen = 0;
            return nullptr;
        }

        size_t currentLen = len;
        for (int k = 0; k < order; k++) {
            for (size_t i = 0; i < currentLen - 1; i++) {
                buffer[i] = (temp[i + 1] - temp[i]) / dt;
            }
            currentLen -= 1;
            float* swap = temp;
            temp = buffer;
            buffer = swap;
        }

        delete[] buffer;

        outLen = currentLen;
        float* result = new (std::nothrow) float[outLen];
        if (!result) {
            delete[] temp;
            outLen = 0;
            return nullptr;
        }

        for(size_t i = 0; i < outLen; ++i) {
            result[i] = temp[i];
        }

        delete[] temp;
        return result;
    }

    float definiteIntegral(float* data, size_t len, float dx) {
        float sum = 0.0;
        for (size_t i = 0; i < len; i++) {
            sum += data[i];
        }
        return sum * dx;
    }

    float tripleIntegral(float*** data, size_t xLen, size_t yLen, size_t zLen, float dx, float dy, float dz) {
        float total = 0.0;
        for (size_t i = 0; i < xLen; i++) {
            for (size_t j = 0; j < yLen; j++) {
                for (size_t k = 0; k < zLen; k++) {
                    total += data[i][j][k];
                }
            }
        }
        return total * dx * dy * dz;
    }

}
