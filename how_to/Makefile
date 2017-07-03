CXX=g++
CXXFLAGS=-O0 -Wall -g -std=gnu++11
LDLIBS=
BIN=$(shell basename `pwd`)
all: $(BIN)

$(BIN):	$(BIN).cpp
	$(CXX) $(CXXFLAGS)  $^ -o $@ $(LDLIBS)

clean:
	$(RM) $(BIN)

