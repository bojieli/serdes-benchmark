#include "test_serdes.h"
#include "flatbuf/flatbuf_serdes.h"
#include "test_compression.h"

// for illustration purpose only: network throughput threshold to enable compression
const uint32_t throughput_threshold = 100;

/**
 * Please replace this function to the serialization function of yours.
 */
void TestSerialize(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size)
{
    FlatBufSerialize(root, buf, serialize_size);
    if (network_throughput <= throughput_threshold) {
        CompressData(buf, serialize_size);
    }
}

/**
 * Please replace this function to the deserialization function of yours.
 */
TreeNode *TestDeserialize(uint32_t network_throughput, const void *buf, uint32_t serialize_size)
{
    if (network_throughput <= throughput_threshold) {
        DecompressData(&buf, &serialize_size);
    }
    return FlatBufDeserialize(buf, serialize_size);
}

/**
 * Please replace this function to free your serialized data after test.
 */
void TestFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
    FlatBufFreeSerializeBuf(buf, serialize_size);
}
