#ifdef __TEST_SERDES_H__
#define __TEST_SERDES_H__

#include "benchmark.h"

/**
 * TestSerialize: the serialization function to be tested
 *
 * @network_throughput [input]: simulated network throughput (MB/s)
 * @root [input]: root of tree to be serialized
 * @buf [output]: pointer to the serialized data
 * @serialize_size [output]: size of the serialized data (bytes)
 */
void TestSerialize(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size);

/**
 * TestDeserialize: the deserialization function to be tested
 *
 * @network_throughput [input]: simulated network throughput (MB/s)
 * @buf [input]: pointer to the serialized data
 * @serialize_data [input]: size of the serialized data (bytes)
 *
 * Return value: root of the tree after deserialization
 */
TreeNode *TestDeserialize(uint32_t network_throughput, void *buf, uint32_t serialize_size);

/**
 * TestFreeSerializeBuf: free serialization buffer after test
 *
 * @buf [input]: pointer to the serialized data
 * @serialize_size [input]: size of the serialized data (bytes)
 */
void TestFreeSerializeBuf(void *buf, uint32_t serialize_size);

#endif
