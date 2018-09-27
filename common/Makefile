include srcs.mk

OBJ := $(BINARIES_PATH)/common.o $(BINARIES_PATH)/llist.o

all: srcs

srcs:
	gcc -c $(INC) common.c $(LIB) -o $(BINARIES_PATH)/common.o
	gcc -c $(INC) llist.c $(LIB) -o $(BINARIES_PATH)/llist.o
	ar rcs $(BINARIES_PATH)/libcommon.a $(OBJ)
	rm $(OBJ)
