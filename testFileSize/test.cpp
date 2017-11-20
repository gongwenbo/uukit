#include <sys/stat.h>  
#include <stdio.h>
#include <stdlib.h>
  
unsigned long get_file_size(const char *path)  
{  
    unsigned long filesize = -1;      
    struct stat statbuff;  
    if(stat(path, &statbuff) < 0){  
        return filesize;  
    }else{  
        filesize = statbuff.st_size;  
    }  
    return filesize;  
}

int main(int argc,char **argv){

	unsigned long file_size=get_file_size(argv[1]);
	if(file_size!=-1)
		printf("file size:%ul",file_size);
	else return 1;
	return 0;
	
}  
