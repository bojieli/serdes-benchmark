#ifndef __FLATBUF_SERDES_H__
#define __FLATBUF_SERDES_H__

#include "benchmark.h"

void FlatBufSerialize(const TreeNode *root, const void **buf, uint32_t *serialize_size);
TreeNode *FlatBufDeserialize(const void *buf, uint32_t serialize_size);
void FlatBufFreeSerializeBuf(void *buf, uint32_t serialize_size);

#endif
