TARGET=ser
CC=g++
INC=-I./
LIB=-luv
LIBPATH=-L/usr/local/lib
CFLAGS=-Wall -g -std=c++11
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBPATH) $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

.PHONY:clean
clean:
	rm -rf $(TARGET) $(OBJS)
















