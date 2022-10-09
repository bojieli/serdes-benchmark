#include "treenode_generated.h"
#include "flatbuf_serdes.h"

using namespace FlatBufTest;
using namespace flatbuffers;

static flatbuffers::Offset<FBTreeNode> SerializeRecursive(FlatBufferBuilder& buffer, const TreeNode *root)
{
    FBTreeNodeBuilder builder(buffer);
    if (root->left) {
        builder.add_left(SerializeRecursive(buffer, root->left));
    }
    if (root->right) {
        builder.add_right(SerializeRecursive(buffer, root->right));
    }
    builder.add_key(root->key);
    builder.add_value(buffer.CreateString(root->value));
    return builder.Finish();
}

void FlatBufSerialize(const TreeNode *root, void **buf, uint32_t *serialize_size)
{
    flatbuffers::FlatBufferBuilder builder;

    SerializeRecursive(builder, root);

    *buf = builder.GetBufferPointer();
    *serialize_size = builder.GetSize();
}

static TreeNode *DeserializeRecursive(const FBTreeNode *root)
{
    TreeNode *node = new TreeNode();
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
