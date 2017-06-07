source = encoding-tree.cc sample-utils.cc counter.cc random.cc main.cc
objects = encoding-tree.o sample-utils.o counter.o random.o
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