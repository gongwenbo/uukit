TARGET=ser
INCLUDE=-I/usr/local/include
LIBRARY_PATH=-L/usr/local/lib
LIB=-luv
CFLAGS=-g -Wall -std=c++11
OJBS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))
CC=g++
all:$(TARGET) clean_obj

$(TARGET):$(OJBS)
	$(CC) -o $@ $^ $(LIBRARY_PATH) $(LIB)

.cpp.o:
	$(CC) -o $@ -c $< $(INCLUDE)

.PHONY:clean
.PHONY:clean_obj

clean:
	rm -rf $(TARGET)

clean_obj:
	rm -rf $(OJBS)
