TARGET=out
INCLUDE=-I./include 
LIB_PATH= -L./lib 
#LIB=-lpthread -ljson_linux-gcc-4.8.5_libmt
LIB=-lpthread -lcjson
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp ))
#CC=g++
CC=mips-linux-uclibc-gnu-g++
CFLAGS=-g -Wall  

all:$(TARGET) clean_obj

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(INCLUDE) 

.PHONY:clean
.PHONY:clean_obj
clean:
	rm -rf  $(TARGET)
clean_obj:
	rm -rf $(OBJS)
