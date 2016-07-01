FLAGS = -std=c++11 -g -Wall -Wextra -pedantic -Wno-format

all:
	$(CXX) $(FLAGS) -c simple.cpp SharedPtr.hpp -pthread
	$(CXX) $(FLAGS) -o prog simple.o -pthread

#$(CXX) $(FLAGS) -c SharedPtr_test.cpp SharedPtr.hpp -pthread

	
clean:
	rm -rf *.o *~ prog

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

