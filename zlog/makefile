TARGET=out
CC=g++
CFLAGS=-g -Wall -std=c++11
INCLUDE=-I/usr/local/include
LIBRARY_PATH=-L/usr/local/lib -L/root/zlog-1.2.7-ed0995d0/src/
LIBRARY=-luv -lzlog
OBJS=$(patsubst %.cpp, %.o, $(wildcard ./*.cpp))

all:$(TARGET) cleanObj

$(TARGET):$(OBJS)
		$(CC) -o $@  $^ $(LIBRARY_PATH) $(LIBRARY)

.cpp.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

.PHONY:cleanObj
.PHONY:clean 

cleanObj:
		rm -rf ./*.o
clean:
		rm -rf ./$(TARGET) 
