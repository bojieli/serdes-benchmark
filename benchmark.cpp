#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include "benchmark.h"
#include "test_serdes.h"
#include "baseline_serdes.h"

using namespace std;
using namespace std::chrono;

std::string rand_str()
{
    const uint32_t max_strlen = 100;
    uint32_t length = rand() % max_strlen;
    std::string rand_str;
    for (uint32_t i = 0; i < length; ++i) {
        rand_str += '0' + rand() % 10;
    }
    return rand_str;
}

TreeNode *GenRandomTree(uint32_t size)
{
    TreeNode *curr = new TreeNode();
    curr->key = rand();
    curr->value = rand_str();

    uint32_t left_size = rand() % size;
    if (left_size > 0) {
        curr->left = GenRandomTree(left_size);
    } else {
        curr->left = NULL;
    }

    uint32_t right_size = size - left_size - 1;
    if (right_size > 0) {
        curr->right = GenRandomTree(right_size);
    } else {
        curr->right = NULL;
    }
    return curr;
}

bool ValidateSerdesResult(const TreeNode *root_a, const TreeNode *root_b)
{
    if (root_a == NULL && root_b == NULL) {
        return true;
    }
    if (root_a == NULL || root_b == NULL) {
        return false;
    }

    if (root_a->key != root_b->key || root_a->value != root_b->value) {
        return false;
    }

    return ValidateSerdesResult(root_a->left, root_b->left)
        && ValidateSerdesResult(root_a->right, root_b->right);
}

void FreeTree(TreeNode *root)
{
    if (root->left) {
        FreeTree(root->left);
    }
    if (root->right) {
        FreeTree(root->right);
    }
    delete root;
}

double RunBenchmark(const TreeNode *root, uint32_t network_throughput,
    void (*SerializeFunc)(uint32_t network_throughput, const TreeNode *root, void **buf, uint32_t *serialize_size),
    TreeNode *(*DeserializeFunc)(uint32_t network_throughput, const void *buf, uint32_t serialize_size),
    void (*FreeSerializeBufFunc)(void *buf, uint32_t serialize_size),
    const char *test_name)
{
    auto start = chrono::steady_clock::now();

    uint32_t serialize_size = 0;
    void *serialize_buf = NULL;
    SerializeFunc(network_throughput, root, &serialize_buf, &serialize_size);

    auto middle = chrono::steady_clock::now();

    TreeNode *new_root = DeserializeFunc(network_throughput, serialize_buf, serialize_size);

    auto end = chrono::steady_clock::now();

    auto serialize_time = chrono::duration_cast<chrono::microseconds>(middle - start).count();
    auto deserialize_time = chrono::duration_cast<chrono::microseconds>(end - middle).count();
    auto transmission_time = serialize_size / network_throughput;
    auto total_time = serialize_time + deserialize_time + transmission_time;

    if (ValidateSerdesResult(root, new_root) == false) {
        cerr << "Test failed: serialized data is not equivalent to deserialized data" << endl;
        exit(1);
    }
    FreeSerializeBufFunc(serialize_buf, serialize_size);
    FreeTree(new_root);

    cout << "Total " << test_name << " time is " << total_time << " us: "
         << "serialize " << serialize_time << " us, "
         << "deserialize time " << deserialize_time << " us, " 
         << "serialized data size is " << serialize_size << " bytes "
         << "(emulate " << network_throughput << " MB/s, " << transmission_time << " us)" << endl;
    return total_time;
}

double RunComparison(const TreeNode *root, uint32_t network_throughput)
{
    double baseline_time = RunBenchmark(root, network_throughput, BaselineSerialize, BaselineDeserialize, BaselineFreeSerializeBuf, "baseline");
    double test_time = RunBenchmark(root, network_throughput, TestSerialize, TestDeserialize, TestFreeSerializeBuf, "test");
    double speedup = test_time / baseline_time;
    cout << "Throughput " << network_throughput << " MB/s: speedup " << speedup << endl;
    return speedup;
}

int main(int argc, char **argv)
{
    const uint32_t size = 1000000;

    TreeNode *root = GenRandomTree(size);

    const uint32_t network_throughputs[] = {10, 100, 1000, 10000}; // MB/s
    const int num_cases = sizeof(network_throughputs) / sizeof(uint32_t);
    double total_speedup = 0;
    for (int i = 0; i < num_cases; ++i) {
        total_speedup += RunComparison(root, network_throughputs[i]);
    }
    cout << "ALL TEST CASES PASSED!" << endl;
    cout << "AVERAGE SPEEDUP: " << (total_speedup / num_cases) << endl;
    return 0;
}
