CXX=g++
CFLAGS=-g -O2
PROTOC=protoc
FLATC=flatc
FLATBUF_LIB=-lflatbuf
PROTOBUF_LIB=-lprotobuf

benchmark: test_serdes.o baseline_serdes.o protobuf.o flatbuf.o
	$(CXX) $(CFLAGS) -o $@ $*

test_serdes.o: test_serdes.cpp

baseline_serdes.o: baseline_serdes.cpp

protobuf.o: protobuf/treenode.proto protobuf/protobuf_serdes.cc
	cd protobuf && $(PROTOC) --cpp_out=. treenode.proto
	$(CXX) $(CFLAGS) -o $@ protobuf/protobuf_serdes.cc protobuf/treenode.pb.cc $(PROTOBUF_LIB)

flatbuf: flatbuf/treenode.fbs flatbuf/flatbuf_serdes.cpp
	cd flatbuf && $(FLATC) -c treenode.fbs
	$(CXX) $(CFLAGS) -o $@ flatbuf/flatbuf_serdes.cpp $(FLATBUF_LIB)
