
//#define Cache_size	1024
#define Cache_Num	800


typedef struct _Cache  
{  
	unsigned int  	size;
	unsigned int	pos;
	unsigned char*	data; 
}Cache;


int cache_push(unsigned char *ptr, int size);

int cache_poll(unsigned char *ptr, int size);

int cache_free();
