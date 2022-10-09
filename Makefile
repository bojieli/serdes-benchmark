CXX=g++
CXXFLAGS=-g -O2 -I.
PROTOC=protoc
FLATC=flatc
PROTOBUF_LIB=-lprotobuf

.PHONY: clean protobuf_schema flatbuf_schema

objects = benchmark.o test_serdes.o baseline_serdes.o protobuf.o protobuf_serdes.o flatbuf_serdes.o

benchmark: $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $(objects) $(PROTOBUF_LIB)

benchmark.o: benchmark.cpp

test_serdes.o: test_serdes.cpp

baseline_serdes.o: baseline_serdes.cpp

protobuf.o: protobuf_schema
	$(CXX) $(CXXFLAGS) -c -o $@ protobuf/treenode.pb.cc

protobuf_serdes.o: protobuf_schema protobuf/protobuf_serdes.cc
	$(CXX) $(CXXFLAGS) -c -o $@ protobuf/protobuf_serdes.cc 

protobuf_schema: protobuf/treenode.proto
	cd protobuf && $(PROTOC) --cpp_out=. treenode.proto

flatbuf_serdes.o: flatbuf_schema flatbuf/flatbuf_serdes.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ flatbuf/flatbuf_serdes.cpp

flatbuf_schema: flatbuf/treenode.fbs
	cd flatbuf && $(FLATC) -c treenode.fbs

clean:
	rm -rf benchmark *.o */*.o
