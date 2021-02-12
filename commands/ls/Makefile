include srcs.mk

OBJ := $(BINARIES_PATH)/ls/ls.o $(BINARIES_PATH)/ls/ls_utils.o

all: srcs

srcs:
	gcc -Wall -Wextra -c $(INC) main.c $(LIB) -o $(BINARIES_PATH)/ls/ls.o
	gcc -Wall -Wextra -c $(INC) ls_utils.c $(LIB) -o $(BINARIES_PATH)/ls/ls_utils.o
	gcc $(OBJ) $(LIB) -o $(BINARIES_PATH)/ls/ls
	rm $(OBJ)
