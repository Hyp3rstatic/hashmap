CC = gcc
SRC = src
OBJ = build/obj
BIN = build/bin
OBJS = $(OBJ)/hashmap.o $(OBJ)/list.o

all: hashmap bin obj
	$(CC) $(OBJS) -o $(BIN)/hashmap

clean:
	rm -rf build

bin: build
	mkdir -p $(BIN)

obj: build
	mkdir -p $(OBJ)

build:
	mkdir -p build

list: $(SRC)/list.c
	$(CC) -g -O -c $(SRC)/list.c -o $(OBJ)/list.o

hashmap: $(SRC)/hashmap.c obj list
	$(CC) -g -O -c $(SRC)/hashmap.c -o $(OBJ)/hashmap.o
