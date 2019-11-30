CXX        = g++
# CXXFLAGS   = -Wall -std=c++17 -O4 -lpthread -lboost_system -g -lgmp
# LDFLAGS    = -static -L./gmp-patched/lib -lgmp -lboost_system -lpthread
CXXFLAGS   = -Wall -std=c++17 -O4 -lboost_system -pthread -lboost_thread -g -I./gmp-patched/include/ -Dmpz_raw_64
LDFLAGS    = -lboost_system -pthread -lboost_thread -lgmp -static -L./gmp-patched/lib

default: batchgcd

batchgcd: src/batchgcd.cpp src/utils.cpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $@

memcheck:
	valgrind --leak-check=full ./batchgcd toy_moduli.csv

clean:
	rm -rf batchgcd *.o data/product_tree/*

