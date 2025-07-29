#ifndef DSPDATAMANAGER_H
#define DSPDATAMANAGER_H

#include <stddef.h>

namespace dspDataManager {

    float* allocateBuffer(size_t len);
    void clearBuffer(float* buffer, size_t len);
    void fillBufferWithValue(float* buffer, size_t len, float value);
    bool isSafeToAllocate(size_t bytes);

}

#endif
