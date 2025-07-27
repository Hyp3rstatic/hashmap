CC = gcc
SRC = src
OBJ = build/obj
BIN = build/bin
OBJS = $(OBJ)/hashmap.o $(OBJ)/list_sl.o $(OBJ)/kv_pair.o $(OBJ)/fnv_1a.o $(OBJ)/node_sl.o
TST = test
TBIN = test/build/bin
TOBJ = test/build/obj
TOBJS = $(TOBJ)/test.o

all: hashmap bin obj
	$(CC) $(OBJS) -o $(BIN)/hashmap

clean:
	rm -rf build
	rm -rf test/build

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

node_sl: $(SRC)/node_sl.c obj kv_pair
	$(CC) -g -O -c $(SRC)/node_sl.c -o $(OBJ)/node_sl.o

list_sl: $(SRC)/list_sl.c obj node_sl
	$(CC) -g -O -c $(SRC)/list_sl.c -o $(OBJ)/list_sl.o

hashmap: $(SRC)/hashmap.c obj list_sl fnv_1a
	$(CC) -g -O -c $(SRC)/hashmap.c -o $(OBJ)/hashmap.o

tbuild:
	mkdir -p test/build

tbin: build
	mkdir -p $(TBIN)

tobj: build
	mkdir -p $(TOBJ)

test: $(TST)/test.c tbin tobj bin obj hashmap
	$(CC) -g -O -c $(TST)/test.c -o $(TOBJ)/test.o
	$(CC) $(OBJS) $(TOBJS) -o $(TBIN)/test
