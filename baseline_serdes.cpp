#include "baseline_serdes.h"

/**
 * This function performs serialization using Protocol Buffers.
 */
void BaselineSerialize(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size)
{
}

/**
 * This function performs deserialization using Protocol Buffers.
 */
TreeNode *BaselineDeserialize(uint32_t network_throughput, void *buf, uint32_t serialize_size)
{
}

/**
 * This function frees serialized data after test.
 */
void BaselineFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
}
