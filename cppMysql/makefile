TARGET=out
CC=g++
CFLAGS=-Wall -std=c++11 -g
LIB=-L/usr/local -lmysqlcppconn
INC=-I./
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))
all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(INC)

.PHONY:clean

clean:
	rm -rf $(OBJS) $(TARGET)



