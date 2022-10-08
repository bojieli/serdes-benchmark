#include "test_serdes.h"
#include "flatbuf/flatbuf_serdes.h"

/**
 * Please replace this function to the serialization function of yours.
 */
void TestSerialize(uint32_t network_throughput, const TreeNode *root, const void **buf, uint32_t *serialize_size)
{
    FlatBufSerialize(root, buf, serialize_size);
}

/**
 * Please replace this function to the deserialization function of yours.
 */
TreeNode *TestDeserialize(uint32_t network_throughput, const void *buf, uint32_t serialize_size)
{
    return FlatBufDeserialize(buf, serialize_size);
}

/**
 * Please replace this function to free your serialized data after test.
 */
void TestFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
    FlatBufFreeSerializeBuf(buf, serialize_size);
}
