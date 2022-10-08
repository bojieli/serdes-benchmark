#include "treenode_generated.h"
#include "flatbuf_serdes.h"

using namespace FlatBufTest;

static flatbuffers::Offset<FBTreeNode> SerializeRecursive(FlatBufferBuilder* buffer, const TreeNode *root)
{
    FBTreeNodeBuilder builder(buffer);
    if (root->left) {
        builder.add_left(TestSerializeRecursive(buffer root->left));
    }
    if (root->right) {
        builder.add_right(TestSerializeRecursive(buffer, root->right));
    }
    builder.add_key(root->key);
    builder.add_value(builder.CreateString(root->value));
    return builder.Finish();
}

void FlatBufSerialize(const TreeNode *root, const void **buf, uint32_t *serialize_size)
{
    flatbuffers::FlatBufferBuilder builder;

    SerializeRecursive(&builder, root);
    builder->Finish();

    *buf = builder.GetBufferPointer();
    *serialize_size = builder.GetSize();
}

static TreeNode *DeserializeRecursive(FBTreeNode *root)
{
    TreeNode *node = new TreeNode();
    node->key = root->key();
    node->value = root->value()->str();

    if (root->left()) {
        node->left = TestDeserializeRecursive(root->left());
    } else {
        node->left = NULL;
    }
    if (root->right()) {
        node->right = TestDeserializeRecursive(root->right());
    } else {
        node->right = NULL;
    }
    return node;
}

TreeNode *FlatBufDeserialize(const void *buf, uint32_t serialize_size)
{
    FBTreeNode *root = GetFBTreeNode(buf);
    TreeNode *node = TestDeserializeRecursive(root);
    return node;
}

void FlatBufFreeSerializeBuf(const void *buf, uint32_t serialize_size)
{
}
