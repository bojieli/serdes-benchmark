#ifndef __TEST_SERDES_H__
#define __TEST_SERDES_H__

#include "benchmark.h"

void TestSerialize(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size);

TreeNode *TestDeserialize(uint32_t network_throughput, const void *buf, uint32_t serialize_size);

void TestFreeSerializeBuf(void *buf, uint32_t serialize_size);

#endif
