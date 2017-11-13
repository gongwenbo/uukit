
CC= mips-linux-uclibc-gnu-gcc
LOCAL_INC :=-I./src -I./inc

CFLAGS = -O2 -Wall -fno-strict-aliasing
CFLAGS += -fpic -shared 
CFLAGS += $(LOCAL_INC)

PRG_NAME := ./libnmosal.so
AR_NAME := ./libnmosal.a
SRC  :=$(wildcard *.c)  $(wildcard src/*.c)
OBJ  := $(SRC:%.c=%.o)

all:$(OBJ)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(PRG_NAME)
	$(AR) -rv $(AR_NAME) ./src/*.o 
	rm $(OBJ) -rf *.o

.PHONY : clean
clean:
		rm $(PRG_NAME) $(AR_NAME) $(OBJ) -rf *.o

