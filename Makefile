SRC_FILES = $(wildcard *.cpp)
BIN_FILES = $(patsubst %.cpp, %, $(SRC_FILES))

CC_FLAGS = -std=c++11 -Wall -O2 -lm
CC = g++

all: $(BIN_FILES)

$(BIN_FILES):%: %.cpp
	$(CC) $(CC_FLAGS) -o $@ $<

clean:
	rm -f $(BIN_FILES)
