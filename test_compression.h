#ifndef __TEST_COMPRESSION_H__
#define __TEST_COMPRESSION_H__

#include <cstdint>

void CompressData(void **buf, uint32_t *size);
void DecompressData(const void **buf, uint32_t *size);

#endif
