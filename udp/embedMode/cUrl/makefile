TARGET=out
INCLUDE=-I./include
LIB_PATH=-L./lib
LIB=-lcurl
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

#CC=g++
CC=mips-linux-uclibc-gnu-g++
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



