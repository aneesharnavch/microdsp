#include "dspResources.h"

size_t dspResources::FREE_MEMORY_BYTES = 2048;
static uint8_t computeLimitPercent = 100;

namespace dspResources {

    void setAvailableMemory(size_t bytes) {
        FREE_MEMORY_BYTES = bytes;
    }

    bool hasSufficientMemory(size_t requiredBytes) {
        return requiredBytes <= FREE_MEMORY_BYTES;
    }

    void setComputeLimit(uint8_t percent) {
        if (percent > 100) percent = 100;
        computeLimitPercent = percent;
    }

    uint8_t getComputeLimit() {
        return computeLimitPercent;
    }
}
