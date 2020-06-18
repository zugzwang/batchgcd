CXX        = g++ -g
CXXFLAGS   = -Wall -std=c++17 -O4 -lboost_system -pthread -lboost_thread -g -I./gmp/patched/include/ -Dmpz_raw_64
LDFLAGS    = -lboost_system -pthread -lboost_thread -lgmp -static -L./gmp/patched/lib

default: batchgcd

install:
	mkdir -p data data/product_tree && sh scripts/patch_gmp.sh

batchgcd: src/batchgcd.cpp src/utils.cpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@

testpatch: src/test/testpatch.cpp src/utils.cpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@

test:
	scripts/test_run.sh

memcheck:
	valgrind --leak-check=full ./batchgcd toy.moduli

clean:
	rm -rf batchgcd *.o data/product_tree/* compromised.csv duplicates.csv testpatch

lint:
	cpplint --verbose=2 --recursive --extensions=hpp,cpp *
