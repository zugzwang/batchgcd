CXX      = g++
CXXFLAGS   = -Wall -std=c++17 -O3 -lpthread -lrt -lboost_system -g -I./gmp-patched/include/ -Dmpz_raw_64
LDFLAGS  =-static -L./gmp-patched/lib -lgmp

default: batchgcd

batchgcd:
	$(CXX) src/batchgcd.cpp src/utils.cpp -o batchgcd $(CXXFLAGS) $(LDFLAGS)

memcheck:
	valgrind --leak-check=full ./batchgcd toy_moduli.csv

clean:
	rm -rf batchgcd *.o data/product_tree/*

