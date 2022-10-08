#ifndef __PROTOBUF_SERDES_H__
#define __PROTOBUF_SERDES_H__

#include "../benchmark.h"

void ProtoBufSerialize(const TreeNode *root, std::string* output);
TreeNode *ProtoBufDeserialize(const std::string& serialized_data);

#endif
