TARGET=serBoast
INCLUDE=-I/usr/local/include
LIB_PATH=-L/usr/local/lib
LIB=-luv
CC=g++
CFLAGS=-Wall -g -std=c++11
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

all:$(TARGET) clean_obj

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(INCLUDE)

.PHONY:clean
.PHONY:clean_obj

clean:
	rm -rf $(TARGET)

clean_obj:
	rm -rf $(OBJS)
