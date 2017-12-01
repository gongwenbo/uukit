#ifndef LOG_H
#define LOG_H
#include "common.h"

class Log{

	public:
		static int debug(const char* f,const int l,const char *format,...);

};
#endif


