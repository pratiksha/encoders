source = shannon-fano.cc huffman.cc main.cc
objects = shannon-fano.o huffman.o
executables = main
CXX = g++
LANGFLAGS = -std=c++14
CXXFLAGS = -g -O0 -pthread -pedantic -Wall -Wextra -Weffc++

all: $(executables)

main: main.o $(objects)
	$(CXX) $(LANGFLAGS) $(CXXFLAGS) -o $@ $+ $(LIBS)

%.o: %.cc
	$(CXX) $(LANGFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	-rm -f $(executables) *.o *~