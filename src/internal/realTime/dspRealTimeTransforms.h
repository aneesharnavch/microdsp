#ifndef DSP_REALTIME_TRANSFORMS_H
#define DSP_REALTIME_TRANSFORMS_H

#include <stddef.h>
#include <vector>

namespace dspRealTime {

class RealTimeFFT {
public:
    RealTimeFFT(size_t windowSize);
    void update(float newValue);
    const std::vector<float>& getReal();
    const std::vector<float>& getImag();

private:
    void fft();

    std::vector<float> buffer;
    std::vector<float> real;
    std::vector<float> imag;
    size_t windowSize;
    bool bufferFull;
};

}

#endif
