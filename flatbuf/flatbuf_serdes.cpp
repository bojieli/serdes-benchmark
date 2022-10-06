#include "treenode_generated.h"

using namespace FlatBufTest;

flatbuffers::Offset<FBTreeNode> TestSerializeRecursive(FlatBufferBuilder* buffer, const TreeNode *root)
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

void TestSerialize(const TreeNode *root, void **buf, uint32_t *serialize_size)
{
    flatbuffers::FlatBufferBuilder builder;

    TestSerializeRecursive(&builder, root);
    builder->Finish();

    *buf = builder.GetBufferPointer();
    *serialize_size = builder.GetSize();
}

TreeNode *TestDeserializeRecursive(FBTreeNode *root)
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

TreeNode *TestDeserialize(void *buf, uint32_t serialize_size)
{
    FBTreeNode *root = GetFBTreeNode(buf);
    TreeNode *node = TestDeserializeRecursive(root);
    return node;
}

void TestFreeSerializeBuf(void *buf, uint32_t serialize_size)
{
}
