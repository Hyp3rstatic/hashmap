CC = gcc
SRC = src
OBJ = build/obj
BIN = build/bin
OBJS = $(OBJ)/hashmap.o $(OBJ)/list_sl.o $(OBJ)/kv_pair.o $(OBJ)/fnv_1a.o

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

fnv_1a: $(SRC)/fnv_1a.c obj
	$(CC) -g -O -c $(SRC)/fnv_1a.c -o $(OBJ)/fnv_1a.o

kv_pair: $(SRC)/kv_pair.c obj
	$(CC) -g -O -c $(SRC)/kv_pair.c -o $(OBJ)/kv_pair.o

list_sl: $(SRC)/list_sl.c obj kv_pair
	$(CC) -g -O -c $(SRC)/list_sl.c -o $(OBJ)/list_sl.o

hashmap: $(SRC)/hashmap.c obj list_sl fnv_1a
	$(CC) -g -O -c $(SRC)/hashmap.c -o $(OBJ)/hashmap.o
