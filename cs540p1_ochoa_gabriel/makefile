PROJECT := cs540p1_ochoa_gabriel
EXECUTABLE := prog
SRC_FILES := \
	Deque.hpp \
	test.cpp

OBJ_FILES := \
	test.o 

CXX := g++
CXXFLAGS := -std=c++11 -Wno-unused-variable -g -ldl
SUBFLAGS := -std=c++11 -Wall -Wextra -pedantic -g -ldl -O
LIBRARY := 
all: clean ex


ex: test.o Deque.hpp 
	$(CXX) $(SUBFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(SUBFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)

test.o: test.cpp Deque.hpp 
	$(CXX) $(SUBFLAGS) -c test.cpp
clean:
	rm -rf *.o *~ $(EXECUTABLE)

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

