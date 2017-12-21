 
CROSS =   
CC = $(CROSS)gcc  
CXX = $(CROSS)g++  
DEBUG = -g -O2  
CFLAGS = $(DEBUG) -Wall -c  
RM = rm -rf  
  
SRCS = $(wildcard ./*.cpp)  
OBJS = $(patsubst %.cpp, %.o, $(SRCS))  
  
HEADER_PATH = -I./include/  
LIB_PATH = -L./lib/  
  
LIBS = -ldiv      
# LIBS = libdiv.a  
  
VERSION = 1.0.0.1  
TARGET = test.$(VERSION)  
  
$(TARGET) : $(OBJS)  
    $(CXX) $^ -o $@ $(LIB_PATH) $(LIBS)  
  
$(OBJS):%.o : %.cpp  
    $(CXX) $(CFLAGS) $< -o $@ $(HEADER_PATH)  
  
clean:  
    $(RM) $(TARGET) *.o   