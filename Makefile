CXX=g++
CFLAGS=-g -O2 -I.
PROTOC=protoc
FLATC=flatc
PROTOBUF_LIB=-lprotobuf

benchmark: benchmark.o test_serdes.o baseline_serdes.o protobuf.o protobuf_serdes.o flatbuf_serdes.o
	$(CXX) $(CFLAGS) -o $@ $* $(PROTOBUF_LIB)

benchmark.o: benchmark.cpp

test_serdes.o: test_serdes.cpp

baseline_serdes.o: baseline_serdes.cpp

protobuf.o: protobuf
	$(CXX) $(CFLAGS) -c -o $@ protobuf/treenode.pb.cc

protobuf_serdes.o: protobuf protobuf/protobuf_serdes.cc
	$(CXX) $(CFLAGS) -c -o $@ protobuf/protobuf_serdes.cc 

protobuf: protobuf/treenode.proto
	cd protobuf && $(PROTOC) --cpp_out=. treenode.proto

flatbuf_serdes.o: flatbuf flatbuf/flatbuf_serdes.cpp
	$(CXX) $(CFLAGS) -c -o $@ flatbuf/flatbuf_serdes.cpp

flatbuf: flatbuf/treenode.fbs
	cd flatbuf && $(FLATC) -c treenode.fbs

.PHONY: clean

clean:
	rm -rf benchmark *.o */*.o
