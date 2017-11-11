TARGET=main
INCLUDE=-I../include
LIB_PATH=-L../lib -L.
LIB=-ltest -lpthread -limp -lalog -lsysutils -lm -lrt -lfaac -lrtmp -lssl -lcrypto -lz
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

