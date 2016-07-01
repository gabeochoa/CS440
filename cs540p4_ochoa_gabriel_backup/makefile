CXX = g++
FLAGS = -std=c++1z -g -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-sign-compare

all:
	$(CXX) $(FLAGS) -c test.cpp Array.hpp
	$(CXX) $(FLAGS) -o prog test.o
	$(CXX) $(FLAGS) -c itertest.cpp Interpolate.hpp
	$(CXX) $(FLAGS) -o qiter itertest.o
	
clean:
	rm -rf *.o *~ prog

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz


