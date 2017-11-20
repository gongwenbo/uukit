TARGET=out
CC=g++
CFLAGS=-Wall -g -std=c++11
INC=-I./
LIB=-L/usr/local/lib -luv 
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))
all:$(TARGET) cleanObj

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

.PHONY:clean
.PHONY:cleanObj

clean:
	rm -rf $(TARGET)

cleanObj:
	rm -rf $(OBJS)








