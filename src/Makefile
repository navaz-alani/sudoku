CXX=g++
CXXFLAGS=-std=c++14 -Wall -g
SOURCES=$(wildcard *.cc)
OBJECTS=${SOURCES:.cc=.o}
EXEC=sudoku

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXEC)
