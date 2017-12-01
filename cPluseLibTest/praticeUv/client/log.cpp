#include "common.h"

int Log::debug(const char* f,const int l,const char *format,...){

	va_list arg;
	va_start(arg,format);
	fprintf(stderr,"debug:func:%s line:%d:",f,l);
	vfprintf(stderr,format,arg);  /* 注意这里用的是vfprintf ,而不是printf */
	fprintf(stderr,"\n");

	va_end(arg);
	return 0;

}







