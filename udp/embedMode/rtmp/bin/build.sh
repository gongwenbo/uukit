#!/bin/bash

mips-linux-uclibc-gnu-g++ -std=c++11 -o main \
main.cpp cache.cpp play.cpp rtmp264.cpp common.o \
-I../include -L../lib \
-lpthread -limp -lalog -lsysutils -lm -lrt \
-lfaac -lrtmp -lssl -lcrypto -lz

#mips-linux-uclibc-gnu-gcc common.c -c -I../include
