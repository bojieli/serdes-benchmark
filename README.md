# Simple Serialization/Deserialization Benchmark

This is a simple benchmark of serialization and deserialization (serdes).

The benchmark uses a tree data structure for serdes, where each node in the tree contains four fields: an integer key, a string value, an optional left node, and an optional right node. The structure of the tree is randomly generated. The key and value of each node are also randomly generated with some contraints.

The famous serialization framework, Protocol Buffers, uses variable-length encoding for serializing integers to reduce the length of serialized string and TLV (type-length-value) to achieve backward/forward compatibility. These increases the CPU time required for serialization. However, under high-performance networks, transferring a larger amount of data is faster than compressing the data during serialization.

We compare serialization frameworks by emulating four representative network bandwidths:

* 10 MB/s: typical 5G cellular upload speed, 4G cellular download speed
* 100 MB/s: typical 5G cellular download speed, Wi-Fi 4 (802.11n) wireless local network speed
* 1000 MB/s: Wi-Fi 5/6 (802.11ac/n) wireless local network speed, typical datacenter network speed, Flash storage bandwidth
* 10000 MB/s: high-speed datacenter network speed (e.g., RDMA), non-volatile memory bandwidth

The benchmark is written in C++, where serialization transforms a tree to a buffer, and deserialization transforms a buffer to a tree. The resulting tree must be identical with the tree before serialization.

The baseline is Protocol Buffers. We also provide a reference implementation for testing, which utilizes Flat Buffers for serialization and LZ4 for compression under low network bandwidth. Flat Buffers trades off serialized data size for serialization CPU time. The reference implementation is only a hint to show the potential benefits of the trade-off. You are expected to replace the reference test implementation with your own serialization and deserialization algorithm.

## Build

Dependencies:

* Protocol Buffers (protobuf)
* Flat Buffers (flatbuf)
* lz4

You also need `make` and `g++` to build the project.

To install the dependencies on Ubuntu or Debian, please use:

```apt install build-essential protobuf-compiler libprotobuf-dev flatbuffers-compiler libflatbuffers-dev liblz4-dev```

If you find some of the packages are missing, you can download the source code Protocol Buffers, Flat Buffers, and LZ4 from their official repository and build them from scratch.

Note that Protocol Buffers and Flat Buffers include both a compiler and a library. The compiler generates C++ code from the IDL (schema). LZ4 is only a library.

After installing the dependencies, run `make` to build the project.

## Run the Benchmark

```./benchmark```

The output looks like the following:

```
Total baseline time is 15172172 us: serialize 305008 us, deserialize time 990354 us, serialized data size is 138768103 bytes (emulate 10 MB/s, 13876810 us)
Total test time is 15074178 us: serialize 503074 us, deserialize time 203468 us, serialized data size is 143676363 bytes (emulate 10 MB/s, 14367636 us)
Throughput 10 MB/s: speedup 1.0065
Total baseline time is 3146186 us: serialize 742963 us, deserialize time 1015542 us, serialized data size is 138768103 bytes (emulate 100 MB/s, 1387681 us)
Total test time is 2164461 us: serialize 550602 us, deserialize time 177096 us, serialized data size is 143676363 bytes (emulate 100 MB/s, 1436763 us)
Throughput 100 MB/s: speedup 1.45357
Total baseline time is 887901 us: serialize 410652 us, deserialize time 338481 us, serialized data size is 138768103 bytes (emulate 1000 MB/s, 138768 us)
Total test time is 489239 us: serialize 237797 us, deserialize time 95385 us, serialized data size is 156057472 bytes (emulate 1000 MB/s, 156057 us)
Throughput 1000 MB/s: speedup 1.81486
Total baseline time is 763153 us: serialize 410916 us, deserialize time 338361 us, serialized data size is 138768103 bytes (emulate 10000 MB/s, 13876 us)
Total test time is 348959 us: serialize 237551 us, deserialize time 95803 us, serialized data size is 156057472 bytes (emulate 10000 MB/s, 15605 us)
Throughput 10000 MB/s: speedup 2.18694
ALL TEST CASES PASSED!
AVERAGE SPEEDUP: 1.61547
```

The test time and speedup may vary on different testing platforms.

## Use Your Own Serialization

Modify `test_serdes.cpp` and replace the serialization and deserialization functions.

If you need to use other libraries, please update the Makefile accordingly.

Then build the project with `make` and run the benchmark with `./benchmark`.
