TAEGET=out
CFLAGS= -Wall -std=c++11
INCLUDE=-I/usr/include/
CC=g++
OBJS=$(patsubst %.c,%.o,$(wildcard ./*.c))
OBJS=$(patsubst %.cpp,%.o,$(wildcard ./*.cpp))

LIBRARY=-lboost_system -lboost_thread 

all:$(TAEGET) clean_object

$(TAEGET):$(OBJS)
	$(CC) -o $@ $^ $(LIBRARY) 

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

.cc.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

.PHONY:clean_object
.PHONY:clean
clean:
	rm -rf ./$(TAEGET)
	rm -rf ./*.o
clean_object:
	rm -rf ./*.o

