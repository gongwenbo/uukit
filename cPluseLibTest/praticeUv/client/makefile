TARGET=cli
CC=g++
CFLAGS=-Wall -std=c++11 -g
INC=-I./
LIB=-luv
IBPTHT=/usr/local/lib
OBJ=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

all:$(TARGET) 

$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(LIBPTHT) $(LIB)
	
.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)
	
.PHONY:clean 

clean:
	rm -rf $(TARGET) $(OBJ)
	
	
