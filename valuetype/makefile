FLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic

all:
	clang++ $(FLAGS) -c simpletest.cpp Map.hpp
	clang++ $(FLAGS) -o prog simpletest.o

clean:
	rm -rf *.o *.gch *~ prog
	