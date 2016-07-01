CXX=clang++
CXX_FLAGS=-std=c++14 -Wfatal-errors -Wall -Wextra -pedantic -g -O0

all: counter calln

counter: counter.cpp
	${CXX} ${CXX_FLAGS} counter.cpp -o counter

calln: calln.cpp
	${CXX} ${CXX_FLAGS} calln.cpp -o calln

.PHONY: clean

clean:
	rm -f counter calln
