TARGET=out
CC=g++
CFLAGS=-g -Wall -std=c++11
INC=-I./
LIB=-L./
OBJ=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(LIB)
	
.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	
.PHONY:clean

clean:
	rm -rf $(OBJ) $(TARGET)


