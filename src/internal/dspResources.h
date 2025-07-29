#ifndef DSP_RESOURCES_H
#define DSP_RESOURCES_H

#include <stddef.h>
#include <stdint.h>

namespace dspResources {

    extern size_t FREE_MEMORY_BYTES;

    void setAvailableMemory(size_t bytes);

    bool hasSufficientMemory(size_t requiredBytes);

    void setComputeLimit(uint8_t percent);

    uint8_t getComputeLimit();
}

#endif
