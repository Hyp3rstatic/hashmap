CC = gcc
SRC = src
OBJ = build/bin
BIN = build/bin
OBJS = $(OBJ)/hashmap.o

all: hashmap bin
	$(CC) $(OBJS) -o $(BIN)/hashmap

clean:
	rm -rf build

bin: build
	mkdir -p $(BIN)

obj: build
	mkdir -p $(OBJ)

build:
	mkdir -p build

hashmap: $(SRC)/hashmap.c obj
	$(CC) -g -O -c $(SRC)/hashmap.c -o $(OBJ)/hashmap.o
