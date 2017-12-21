TAEGET=out
CFLAGS= -Wall -std=c++11 -g
INCLUDE=-I/usr/include/ -I/root/uukit/DoorBell/inc
CC=g++
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

LIBRARY_PATH=-L/root/uukit/DoorBell/lib
LIBRARY=-lhwsdkc

all:$(TAEGET) 

$(TAEGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBRARY_PATH) $(LIBRARY) 

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)


.PHONY:clean
clean:
	rm -rf $(TAEGET) $(OBJS)

