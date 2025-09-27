CXX = g++
CXXFLAGS = -O3 -Wall -Werror -pedantic -std=c++20 -Iinclude
LDFLAGS = -ltbb -pthread

main: main.o
	${CXX} $^ -o $@ ${LDFLAGS}

main.o: main.cpp 
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f main main.o
