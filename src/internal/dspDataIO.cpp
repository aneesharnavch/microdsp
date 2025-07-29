#include "dspDataIO.h"

void dspDataIO::exportCSV(const float* data, size_t len, const char* label) {
    if (label) Serial.println(label);
    for (size_t i = 0; i < len; ++i) {
        Serial.println(data[i], 6);
    }
}

void dspDataIO::exportEncrypted(const float* data, size_t len, uint8_t key) {
    for (size_t i = 0; i < len; ++i) {
        uint8_t* bytePtr = (uint8_t*)&data[i];
        for (size_t j = 0; j < sizeof(float); ++j) {
            Serial.print(bytePtr[j] ^ key, HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
}

void dspDataIO::annotateAndExport(const float* data, size_t len, const char* description) {
    Serial.println(F("ANNOTATION:"));
    Serial.println(description);
    exportCSV(data, len);
}
