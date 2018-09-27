include srcs.mk

OBJ := $(BINARIES_PATH)/common.o

all: srcs tests

srcs:
	gcc -c $(INC) $(SRC) $(LIB) -o $(OBJ)
	ar rcs $(BINARIES_PATH)/libcommon.a $(OBJ)
	rm $(OBJ)

tests:
