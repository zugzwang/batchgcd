CC      = g++
CFLAGS  = -Wall -O3 -std=c++0x -lgmp -lboost_filesystem -lboost_system
RM      = rm -f

default: batchgcd

batchgcd: batchgcd.cpp
	$(CC) batchgcd.cpp utils.cpp -o batchgcd.o $(CFLAGS)

clean:
	rm -rf *.o data/product_tree/*
