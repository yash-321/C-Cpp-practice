all: test-suite

test-suite: test-suite.o library.o catch.o
	g++ test-suite.o library.o catch.o -o test-suite

test-suite.o: test-suite.cpp
	g++ -c test-suite.cpp -o test-suite.o

library.o: library.cpp
	g++ -c library.cpp -o library.o

catch.o: catch.cpp
	g++ -c catch.cpp -o catch.o

clean:
	rm -rf *.o test-suite
