PROJECT = cs540p3_ochoa_gabriel
CXX = g++
FLAGS = -std=c++11 -g -Wall -Wextra -pedantic

all:
	$(CXX) $(FLAGS) -c test.cpp Function.hpp
	$(CXX) $(FLAGS) -o Function_Test test.o	
	$(CXX) $(FLAGS) -c SharedPtr_test.cpp SharedPtr.hpp -pthread
	$(CXX) $(FLAGS) -o SharedPtr_Test SharedPtr_test.o -pthread

	
clean:
	rm -rf *.o *~ *.gch SharedPtr_Test Function_Test

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz


