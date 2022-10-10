#include "treenode.pb.h"
#include "protobuf_serdes.h"

using namespace std;

static void TreeToProtoBuf(baseline::TreeNode* protobuf, const TreeNode *root)
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

void ProtoBufSerialize(const TreeNode *root, std::string* output)
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    baseline::TreeNode protobuf;

    TreeToProtoBuf(&protobuf, root);

    if (!protobuf.SerializeToString(output)) {
        cerr << "Failed to serialize protobuf to string" << endl;
        exit(1);
    }
}

static TreeNode *ProtoBufToTree(const baseline::TreeNode& protobuf)
{
    TreeNode *root = new TreeNode();
    if (root == NULL) {
        cerr << "Failed to allocate TreeNode" << endl;
        exit(1);
    }

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

TreeNode *ProtoBufDeserialize(const std::string& serialized_data)
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    baseline::TreeNode root;

    if (!root.ParseFromString(serialized_data)) {
        cerr << "Failed to deserialize string to protobuf" << endl;
        exit(1);
    }

    return ProtoBufToTree(root);
}
