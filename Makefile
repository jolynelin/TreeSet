CXXFLAGS = -std=c++17 -g -O2 -Wall -Wextra -pedantic
CXX = clang++
LIB = -ltestinglogger

TARGETS = treeset-test

all: $(TARGETS)

treeset-test: treeset-test.o 
	$(CXX) -o treeset-test treeset-test.o -lranduint32 $(LIB)

minispell: minispell.o 
	$(CXX) -o minispell minispell.o 

minispell.o: minispell.cpp treeset.hpp
	$(CXX) $(CXXFLAGS) -c minispell.cpp

treeset-test.o: treeset-test.cpp treeset.hpp treeset-private.hpp
	$(CXX) $(CXXFLAGS) -c treeset-test.cpp

# treeset.o: treeset.cpp treeset.hpp
# 	$(CXX) $(CXXFLAGS) -c treeset.cpp

clean:
	rm -rf *.o $(TARGETS)