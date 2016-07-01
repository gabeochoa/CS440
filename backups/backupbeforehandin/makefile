PROJECT := cs540p2_ochoa_gabriel
EXECUTABLE := prog
SRC_FILES := \
	Map.hpp \
	test.cpp \
	minimal.cpp \
	moreseex.cpp\
	test-kec.cpp

OBJ_FILES := \
	test-scaling.o \
	test-kec.o \
	moreseex.o \
	minimal.o  \
	test.o \
	
CXX := g++
CXXFLAGS := -std=c++11 -g -Wall -Wextra -pedantic
SUBFLAGS := -std=c++11 -Wall -Wextra -pedantic -Ofast -g -Wno-unused-parameter

all: clean $(EXECUTABLE)

debug: clean exdeb

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o c$(EXECUTABLE) test-kec.o
	$(CXX) $(CXXFLAGS) -O -o scale test-scaling.o
	$(CXX) $(CXXFLAGS) -o a$(EXECUTABLE) minimal.o
	$(CXX) $(CXXFLAGS) -o b$(EXECUTABLE) moreseex.o	
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) test.o

%.o: %.cpp Map.hpp 
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -rf *.o *~ $(EXECUTABLE)

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

