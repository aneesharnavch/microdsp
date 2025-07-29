#ifndef DSPEXPORT_H
#define DSPEXPORT_H

#include <Arduino.h>

namespace dspExport {
    String floatArrayToCompactString(float* data, size_t len, const char* label = nullptr);
    void sendExportStringToSerial(float* data, size_t len, const char* label = nullptr);
}

#endif
