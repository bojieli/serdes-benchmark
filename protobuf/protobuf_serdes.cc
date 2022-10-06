#include <string>
#include "treenode.pb.h"
using namespace std;

void TreeToProtoBuf(baseline::treenode* protobuf, const TreeNode *root)
{
    protobuf->set_key(root->key);
    protobuf->set_value(root->value);

    if (root->left) {
        TreeToProtoBuf(protobuf->mutable_left(), root->left);
    }
    if (root->right) {
        TreeToProtoBuf(protobuf->mutable_right(), root->right);
    }
}

void TreeNodeSerialize(const TreeNode *root, std::string* output)
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    baseline::treenode protobuf;

    TreeToProtoBuf(&protobuf, root);

    protobuf.SerializeToString(output);
}

TreeNode *ProtoBufToTree(const baseline::treenode& protobuf)
{
    TreeNode *root = new TreeNode();
    root->key = protobuf.key();
    root->value = protobuf.value();

    if (protobuf.has_left()) {
        root->left = ProtoBufToTree(protobuf.left());
    } else {
        root->left = NULL;
    }

    if (protobuf.has_right()) {
        root->right = ProtoBufToTree(protobuf.right());
    } else {
        root->right = NULL;
    }
    return root;
}

TreeNode *BaselineDeserialize(void *buf, uint32_t serialize_size)
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    baseline::treenode root;
    std::string serialized_data(buf, serialize_size);

    root.ParseFromString(serialized_data);

    return ProtoBufToTree(root);
}
