PROJECT := prog1_gochoa1
EXECUTABLE := prog
SRC_FILES := \
	Deque.cpp \
	Deque.hpp \
	test.cpp

OBJ_FILES := \
	Deque.o \
	test.o 

CXX := g++
CXXFLAGS := -std=c++11 -Wno-unused-variable -g
SUBFLAGS := -std=c++11 -Wall -Wextra -pedantic 
LIBRARY := 

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)

clean:
	rm -rf *.o *~ $(EXECUTABLE)

dist:
	tar cvvf $(PROJECT).tar ../prog1
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

depend:
	$(CXX) $(CXXFLAGS) -MM *.cpp

Deque.o: Deque.cpp Deque.hpp
test.o: test.cpp Deque.hpp 
