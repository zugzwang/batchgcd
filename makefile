CC      = g++
CFLAGS  = -Wall -O3 -std=c++17 -lgmp -lboost_filesystem -lboost_system -g
RM      = rm -f

default: batchgcd

batchgcd: batchgcd.cpp
	$(CC) batchgcd.cpp utils.cpp -o batchgcd.o $(CFLAGS)

memcheck:
	valgrind --leak-check=full ./batchgcd.o

clean:
	rm -rf *.o data/product_tree/*
