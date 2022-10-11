#include "test_serdes.h"
#include "flatbuf/flatbuf_serdes.h"
#include "test_compression.h"

// for illustration purpose only: network throughput threshold to enable compression
const uint32_t throughput_threshold = 100;

/**
 * TestSerialize: the serialization function to be tested
 *
 * @network_throughput [input]: simulated network throughput (MB/s)
 * @root [input]: root of tree to be serialized
 * @buf [output]: pointer to the serialized data
 * @serialize_size [output]: size of the serialized data (bytes)
 *
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
 * TestDeserialize: the deserialization function to be tested
 *
 * @network_throughput [input]: simulated network throughput (MB/s)
 * @buf [input]: pointer to the serialized data
 * @serialize_data [input]: size of the serialized data (bytes)
 *
 * Return value: root of the tree after deserialization
 *
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
 * TestFreeSerializeBuf: free serialization buffer after test
 *
 * @buf [input]: pointer to the serialized data
 * @serialize_size [input]: size of the serialized data (bytes)
 *
 * Please replace this function to free your serialized data after test.
 */
void TestFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
    FlatBufFreeSerializeBuf(buf, serialize_size);
}
