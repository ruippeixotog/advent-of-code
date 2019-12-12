CC_FILES = $(wildcard */*.cpp)
LIB_CC_FILES = $(wildcard */lib/*.cpp)
HS_FILES = $(wildcard */*.hs)
BIN_FILES = $(CC_FILES:.cpp=)

CC = g++
CC_FLAGS = -std=c++0x -Wall -O2 -lm
HC = ghc
HC_FLAGS = -Wall -O2 -no-keep-hi-files -no-keep-o-files

all: $(BIN_FILES)

$(CC_FILES:.cpp=): %: %.cpp $(LIB_CC_FILES)
	$(CC) $(CC_FLAGS) -o $@ $<

$(HS_FILES:.hs=): %: %.hs
	$(HC) $(HC_FLAGS) -o $@ $<

clean:
	rm -f $(BIN_FILES)
