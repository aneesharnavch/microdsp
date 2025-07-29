#include "dspDataManager.h"
#include "dspResources.h"
#include <new>

namespace dspDataManager {

    float* allocateBuffer(size_t len) {
        size_t requiredBytes = len * sizeof(float);
        if (!dspResources::hasSufficientMemory(requiredBytes)) {
            return nullptr;
        }
        return new (std::nothrow) float[len];
    }

    void clearBuffer(float* buffer, size_t len) {
        if (!buffer) return;
        for (size_t i = 0; i < len; ++i) buffer[i] = 0.0;
    }

    void fillBufferWithValue(float* buffer, size_t len, float value) {
        if (!buffer) return;
        for (size_t i = 0; i < len; ++i) buffer[i] = value;
    }

    bool isSafeToAllocate(size_t bytes) {
        return dspResources::hasSufficientMemory(bytes);
    }
}
