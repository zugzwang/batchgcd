CC      = g++
CFLAGS  = -Wall -O3 -std=c++0x -lgmp
RM      = rm -f

default: batchgcd

batchgcd: batchgcd.cpp
	$(CC) batchgcd.cpp utils.cpp -o batchgcd.o $(CFLAGS)

clean:
	rm *.o data/product_tree/*
