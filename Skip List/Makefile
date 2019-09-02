all: Main

Main: Main.o
	g++ -std=c++11 Main.o -o run-skip

Main.o: Main.cpp SkipList.h
	g++ -std=c++11 -c Main.cpp

clean:
	rm *.o Main