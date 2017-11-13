TARGET=out
CC=mips-linux-uclibc-gnu-g++
LIB=-L./lib -lcjson
INC=-I./
CFLAGS=-Wall -g

OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp ./srcJson/*.cpp))

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

.PHONY:clean
clean:
	rm -rf $(TARGET) $(OBJS) 


