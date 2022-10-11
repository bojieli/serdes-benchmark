#include "test_compression.h"
#include "lz4.h"
#include <iostream>

void CompressData(void **buf, uint32_t *size)
{
    uint32_t compressed_max_size = LZ4_compressBound(*size);
    void *compressed_buf = malloc(compressed_max_size);
    if (compressed_buf == NULL) {
        std::cerr << "Failed to allocate compression buffer: " << compressed_max_size << " bytes" << std::endl;
        exit(1);
    }
    uint32_t compressed_size = LZ4_compress_default((const char *)*buf, (char *)compressed_buf, *size, compressed_max_size);
    *buf = compressed_buf;
    *size = compressed_size;
}

void DecompressData(const void **buf, uint32_t *size)
{
    uint32_t max_compression_ratio = 5; // assume that the compression ratio will not exceed it
    uint32_t decompressed_max_size = *size * max_compression_ratio;
    void *decompressed_buf = malloc(decompressed_max_size);
    if (decompressed_buf == NULL) {
        std::cerr << "Failed to allocate decompression buffer: " << decompressed_max_size << " bytes" << std::endl;
        exit(1);
    }
    uint32_t decompressed_size = LZ4_decompress_safe((const char *)*buf, (char *)decompressed_buf, *size, decompressed_max_size);
    if (decompressed_size == 0 || decompressed_size > decompressed_max_size) {
        std::cerr << "Failed to decompress buffer: " << size << " bytes" << std::endl;
        exit(1);
    }
    *buf = decompressed_buf;
    *size = decompressed_size;
}
