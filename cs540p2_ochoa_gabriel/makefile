all:
	g++ -std=c++11 -g -Wall -Wextra -pedantic -c test-scaling.cpp Map.hpp
	g++ -std=c++11 -g -Wall -Wextra -pedantic -c test-kec.cpp Map.hpp
	g++ -std=c++11 -g -Wall -Wextra -pedantic -c moreseex.cpp Map.hpp
	g++ -std=c++11 -g -Wall -Wextra -pedantic -c minimal.cpp Map.hpp
	g++ -std=c++11 -g -Wall -Wextra -pedantic -c test.cpp Map.hpp
	g++ -std=c++11 -g -Wall -Wextra -pedantic -o cprog test-kec.o
	g++ -std=c++11 -g -Wall -Wextra -pedantic -O -o scale test-scaling.o
	g++ -std=c++11 -g -Wall -Wextra -pedantic -o aprog minimal.o
	g++ -std=c++11 -g -Wall -Wextra -pedantic -o bprog moreseex.o
	g++ -std=c++11 -g -Wall -Wextra -pedantic -o prog test.o

clean:
	rm -rf *.o *~ prog aprog bprog cprog scale

dist:
	tar cvvf $(PROJECT).tar ../$(PROJECT)
	gzip $(PROJECT).tar
	mv $(PROJECT).tar.gz $(PROJECT).tgz

