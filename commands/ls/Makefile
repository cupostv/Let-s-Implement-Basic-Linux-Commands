include srcs.mk

OBJ := $(BINARIES_PATH)/common.o $(BINARIES_PATH)/ls/ls.o

all: srcs tests

srcs:
	gcc -c $(INC) $(SRC) $(LIB) -o $(BINARIES_PATH)/ls/ls.o
	gcc $(OBJ) -o $(BINARIES_PATH)/ls/ls

tests:
