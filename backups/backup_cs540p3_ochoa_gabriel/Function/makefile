CXX = g++
FLAGS = -std=c++11 -g -Wall -Wextra -pedantic -Wno-unused-parameter

all:
	$(CXX) $(FLAGS) -c test.cpp Function.hpp
	$(CXX) $(FLAGS) -o prog test.o
	
clean:
	rm -rf *.o *~ prog

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz