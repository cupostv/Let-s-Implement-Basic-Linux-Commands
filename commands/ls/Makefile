include srcs.mk

OBJ := $(BINARIES_PATH)/ls/ls.o

all: srcs tests

srcs:
	gcc -c $(INC) $(LIB) $(SRC) -o $(BINARIES_PATH)/ls/ls.o
	gcc $(OBJ) -o $(BINARIES_PATH)/ls/ls
	rm $(OBJ)

tests:
