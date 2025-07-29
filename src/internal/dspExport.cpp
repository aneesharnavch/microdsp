#include "dspExport.h"

namespace dspExport {

    String floatArrayToCompactString(float* data, size_t len, const char* label) {
        String result = "";

        if (label != nullptr) {
            result += String("[") + label + "] ";
        }

        for (size_t i = 0; i < len; ++i) {
            result += String(data[i], 4);  // 4 decimal places
            if (i < len - 1) result += ",";
        }

        return result;
    }

    void sendExportStringToSerial(float* data, size_t len, const char* label) {
        String out = floatArrayToCompactString(data, len, label);
        Serial.println(out);
    }

}
