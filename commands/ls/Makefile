include srcs.mk

OBJ := $(BINARIES_PATH)/ls/ls.o

all: srcs

srcs:
	gcc -c $(INC) $(LIB) $(SRC) -o $(BINARIES_PATH)/ls/ls.o
	gcc $(OBJ) $(LIB) -o $(BINARIES_PATH)/ls/ls
	rm $(OBJ)
