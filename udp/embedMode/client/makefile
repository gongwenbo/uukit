TARGET=ecli
INCLUDE=-I./include
LIB_PATH=-L./socklib
LIB=-lpthread
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp ./socklib/*.cpp))
#CC=g++
CC=mips-linux-uclibc-gnu-c++
CFLAGS=-g -Wall 

all:$(TARGET) clean_obj

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE) 

.PHONY:clean
clean:
	rm -rf $(TARGET)
clean_obj:
	rm -rf $(OBJS)



