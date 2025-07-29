#ifndef DSP_DATA_IO_H
#define DSP_DATA_IO_H

#include <Arduino.h>

namespace dspDataIO {

	// Export array to Serial or file
	void exportCSV(const float* data, size_t len, const char* label = nullptr);

	// Encrypted export with basic XOR (for demonstration)
	void exportEncrypted(const float* data, size_t len, uint8_t key);

	// Let user define what data is (for annotation)
	void annotateAndExport(const float* data, size_t len, const char* description);

}

#endif
