#include "stdafx.h"
#include "memopr.h"
void* mkmalloc(size_t size)
{
	void *ptr = ( void * )malloc( size );
	return ptr;
}
void* mkrealloc(void* ptr, size_t size)
{
	ptr = ( void * )realloc( ptr, size );
		
	return ptr;
}
void* mkcalloc(size_t count, size_t size)
{
	void *ptr = ( void * )calloc( count, size );
		
	return ptr;
}
void  mkfree(void* ptr)
{
	if ( ptr != NULL ) free( ptr );
}
