all: Main

Main: BTree.o main.o
	g++ -std=c++11 BTree.o main.o -o run-tree

BTree.o: BTree.cpp BTree.h
	g++ -std=c++11 -c BTree.cpp

main.o: main.cpp BTree.h
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o Main