TARGET=testJson
INCLUDE=-I/usr/local/include -I/usr/include
LIB_PATH=-L/usr/local/lib 
LIB=-lpthread -ljson_linux-gcc-4.8.5_libmt
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))
CC=g++
#CC=mips-linux-uclibc-gnu-c++
CFLAGS=-g -Wall -std=c++11 

all:$(TARGET) 

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(INCLUDE) 

.PHONY:clean
clean:
	rm -rf $(OBJS) $(TARGET)

