CC      = g++
CFLAGS  = -Wall -O3 -std=c++11 -lgmp -lboost_filesystem -lboost_system -g -lpthread
RM      = rm -f

default: batchgcd

batchgcd: src/batchgcd.cpp
	$(CC) src/batchgcd.cpp src/utils.cpp -o batchgcd $(CFLAGS)

memcheck:
	valgrind --leak-check=full ./batchgcd toy_moduli.csv

clean:
	rm -rf *.o data/product_tree/*

