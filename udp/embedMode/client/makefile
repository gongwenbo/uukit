TARGET=ecli
INCLUDE=-I/usr/local/include
LIB_PATH=-L/usr/local/lib
LIB=-lpthread
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))
#CC=g++
CC=mips-linux-uclibc-gnu-c++
CFLAGS=-g -Wall 

all:$(TARGET) 

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(INCLUDE) 

.PHONY:clean
clean:
	rm -rf $(OBJS) $(TARGET)

