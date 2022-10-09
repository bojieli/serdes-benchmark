#ifndef __BASELINE_SERDES_H__
#define __BASELINE_SERDES_H__

#include "benchmark.h"

void BaselineSerialize(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size);

TreeNode *BaselineDeserialize(uint32_t network_throughput, const void *buf, uint32_t serialize_size);

void BaselineFreeSerializeBuf(void *buf, uint32_t serialize_size);

#endif
