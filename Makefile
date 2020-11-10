CC = g++
CC_FLAGS = -std=c++0x -Wall -O2 -lm
CC_FILES = $(wildcard */*.cpp)
LIB_CC_FILES = $(wildcard */lib/*.cpp)
BIN_CC_FILES = $(CC_FILES:.cpp=)

HC = ghc
HC_FLAGS = -Wall -O2 -no-keep-hi-files -no-keep-o-files
HS_FILES = $(wildcard */*.hs)
LIB_HS_FILES = $(wildcard */lib/*.hs)
BIN_HS_FILES = $(HS_FILES:.hs=_hs)

all: $(BIN_CC_FILES) $(BIN_HS_FILES)

$(BIN_CC_FILES): %: %.cpp $(LIB_CC_FILES)
	$(CC) $(CC_FLAGS) -o $@ $<

$(BIN_HS_FILES): %_hs: %.hs $(LIB_HS_FILES)
	$(HC) $(HC_FLAGS) -i$(dir $<) -o $@ $<

clean:
	rm -f $(BIN_CC_FILES) $(BIN_HS_FILES)
