PROJECT := cs540p2_ochoa_gabriel
EXECUTABLE := prog
SRC_FILES := \
	Map.hpp \
	test.cpp \
	minimal.cpp \
	moreseex.cpp\
	test-kec.cpp

OBJ_FILES := \
	moreseex.o \
	minimal.o  \
	test-kec.o \
	test.o  

CXX := clang++
CXXFLAGS := -std=c++11 -g -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-variable
SUBFLAGS := -std=c++11 -Wall -Wextra -pedantic -Ofast -g -Wno-unused-parameter

all: clean $(EXECUTABLE)

debug: clean exdeb

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o c$(EXECUTABLE) test-kec.o
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) test.o
	$(CXX) $(CXXFLAGS) -o a$(EXECUTABLE) minimal.o
	$(CXX) $(CXXFLAGS) -o b$(EXECUTABLE) moreseex.o

%.o: %.cpp Map.hpp 
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -rf *.o *~ $(EXECUTABLE)

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

