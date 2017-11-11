#!/bin/sh
##################################################
# author : áo???-
# date   : 2012-01-30
##################################################

#local dir
INC_PATH	:=  -I$(COMMON_PATH) -I$(PUBLIC_PATH) -I$(NORFLASH_PATH) -I$(BHDCP_PATH)
CPPFLAGS	:=	$(CPPFLAGS_V) $(INC_PATH)
SRCS		:=	$(wildcard *.cpp)
OBJS		:=	$(SRCS:%.cpp=%.o)

LOCAL_TARGET := $(notdir $(SUB_PATH)).a
$(LOCAL_TARGET): $(OBJS) $(PARAM_INCS)
	$(AR) $(ARFLAGS) $(LOCAL_TARGET) $(OBJS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $< 
	
.PHONY: clean dep

clean:
	rm -f $(OBJS) $(LOCAL_TARGET) *.dep
	
dep:
	(for i in *.cpp;do echo -n "    ";$(CPP) -MM $(INC_PATH) $$i;done) > Makefile.dep
	
### Dependencies:
ifeq (Makefile.dep, $(wildcard Makefile.dep))
include Makefile.dep
endif
