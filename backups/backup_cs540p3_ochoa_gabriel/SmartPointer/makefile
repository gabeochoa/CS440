FLAGS = -std=c++11 -g -Wall -Wextra -pedantic

all:
	$(CXX) $(FLAGS) -c SharedPtr_test.cpp SharedPtr.hpp -pthread
	$(CXX) $(FLAGS) -o prog SharedPtr_test.o -pthread

	
clean:
	rm -rf *.o *~ prog

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

