#ifndef _MEM_OPR_H
#define _MEM_OPR_H

void* mkmalloc(size_t size);
void* mkrealloc(void* ptr, size_t size);
void* mkcalloc(size_t count, size_t size);
void  mkfree(void* ptr);
#endif