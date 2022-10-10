#include "treenode_generated.h"
#include "flatbuf_serdes.h"
#include <iostream>

using namespace FlatBufTest;
using namespace flatbuffers;

static Offset<FBTreeNode> SerializeRecursive(FlatBufferBuilder& buffer, const TreeNode *root)
{
    Offset<FBTreeNode> left, right;
    if (root->left) {
        left = SerializeRecursive(buffer, root->left);
    }
    if (root->right) {
        right = SerializeRecursive(buffer, root->right);
    }
    Offset<String> value = buffer.CreateString(root->value);

    // all FlatBuffer objects must be created before the root object
    FBTreeNodeBuilder builder(buffer);
    if (root->left) {
        builder.add_left(left);
    }
    if (root->right) {
        builder.add_right(right);
    }
    builder.add_key(root->key);
    builder.add_value(value);
    return builder.Finish();
}

void FlatBufSerialize(const TreeNode *root, void **buf, uint32_t *serialize_size)
{
    FlatBufferBuilder builder;

    Offset<FBTreeNode> serialized_root = SerializeRecursive(builder, root);
    builder.Finish(serialized_root);

    *buf = builder.GetBufferPointer();
    *serialize_size = builder.GetSize();
}

static TreeNode *DeserializeRecursive(const FBTreeNode *root)
{
    TreeNode *node = new TreeNode();
    if (node == NULL) {
        std::cerr << "Failed to allocate TreeNode" << std::endl;
        exit(1);
    }

    node->key = root->key();
    node->value = root->value()->str();

    if (root->left()) {
        node->left = DeserializeRecursive(root->left());
    } else {
        node->left = NULL;
    }
    if (root->right()) {
        node->right = DeserializeRecursive(root->right());
    } else {
        node->right = NULL;
    }
    return node;
}

TreeNode *FlatBufDeserialize(const void *buf, uint32_t serialize_size)
{
    const FBTreeNode *root = GetFBTreeNode(buf);
    TreeNode *node = DeserializeRecursive(root);
    return node;
}

void FlatBufFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
}
