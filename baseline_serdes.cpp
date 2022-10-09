#include "baseline_serdes.h"
#include "protobuf/protobuf_serdes.h"

std::string *global_serialized_string = NULL;

/**
 * This function performs serialization using Protocol Buffers.
 */
void BaselineSerialize(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size)
{
    std::string *output = new std::string();
    ProtoBufSerialize(root, output);

    *buf = (void *)output->c_str(); // discard constness
    *serialize_size = output->size();
    global_serialized_string = output;
}

/**
 * This function performs deserialization using Protocol Buffers.
 */
TreeNode *BaselineDeserialize(uint32_t network_throughput, const void *buf, uint32_t serialize_size)
{
    if (global_serialized_string != NULL && global_serialized_string->c_str() == buf
        && global_serialized_string->size() == serialize_size) {
        return ProtoBufDeserialize(*global_serialized_string);
    } else {
        std::string serialized_data(reinterpret_cast<const char *>(buf), serialize_size);
        return ProtoBufDeserialize(serialized_data);
    }
}

/**
 * This function frees serialized data after test.
 */
void BaselineFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
    if (global_serialized_string != NULL && global_serialized_string->c_str() == buf
        && global_serialized_string->size() == serialize_size) {
        delete global_serialized_string;
        global_serialized_string = NULL;
    }
}
