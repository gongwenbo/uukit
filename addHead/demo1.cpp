#define IH_MAGIC	0x27051956	/* Image Magic Number		*/
#define IH_NMLEN		32	/* Image Name Length		*/
#define CRCPOLY_LE 0xedb88320
#define SOR "./"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

typedef unsigned int __be32 ;
typedef unsigned char uint8_t ;
typedef unsigned int u32 ;

typedef struct image_header {
	__be32		ih_magic;	/* Image Header Magic Number	*/
	__be32		ih_hcrc;	/* Image Header CRC Checksum	*/
	__be32		ih_time;	/* Image Creation Timestamp	*/
	__be32		ih_size;	/* Image Data Size		*/
	__be32		ih_load;	/* Data	 Load  Address		*/
	__be32		ih_ep;		/* Entry Point Address		*/
	__be32		ih_dcrc;	/* Image Data CRC Checksum	*/
	uint8_t		ih_os;		/* Operating System		*/
	uint8_t		ih_arch;	/* CPU architecture		*/
	uint8_t		ih_type;	/* Image Type			*/
	uint8_t		ih_comp;	/* Compression Type		*/
	uint8_t		ih_name[IH_NMLEN];	/* Image Name		*/
} image_header_t;

u32 crc32_le(u32 crc, unsigned char const *p, size_t len)
{
	int i;
	while (len--) {
		crc ^= *p++;
		for (i = 0; i < 8; i++)
			crc = (crc >> 1) ^ ((crc & 1) ? CRCPOLY_LE : 0);
	}
	return crc;
} 
 
int addHead(char* srcFile,char* decFile)
{
	int _fdRead=0,readCnt=0,pFileLen=0;
	int fdW=0;
	char _readBuf[1024]={0},fileBuf[7*1024*1024];
	_fdRead = open(srcFile, O_RDONLY );
	fdW = open(decFile, O_WRONLY|O_APPEND );
	if(-1 == _fdRead)
        {
            printf("fileOpen error \n");
            return -1;
        }
	
	if(-1 == fdW)
		{
			printf("fdW error\n");
			return -1;
		
		}
	//read
	while ((readCnt = read(_fdRead, (void *)_readBuf, sizeof(_readBuf)))  > 0)
        { 
			memcpy(fileBuf+pFileLen, _readBuf, readCnt);         
            pFileLen += readCnt;
            memset((void *)_readBuf, 0, sizeof(_readBuf));
        }
	//initial Head
	image_header_t* imageHead=(image_header_t*)(fileBuf+pFileLen);
	imageHead->ih_hcrc=crc32_le(0, (unsigned char const*)imageHead, sizeof(imageHead));
	imageHead->ih_magic = IH_MAGIC;
	imageHead->ih_arch = 5;
	imageHead->ih_type = 7;
	imageHead->ih_size=pFileLen;
	
	//combine***********
	//clean fdW
	ftruncate(fdW,0);
    lseek(fdW,0,SEEK_SET);
	
	if (write(fdW, fileBuf+pFileLen,sizeof(image_header_t))  > 0)	
		printf("success1 !!!\n");
	
	if (write(fdW, fileBuf,pFileLen)  > 0)
		printf("success2 !!!\n");
			
};


int main(int argc,char* argv[])
{
	char src_path[128]={0};
	char dec_pathC[128]={0};
	int fdRead=0,pFileLen=0,readCnt=0;
	char _readBuf[1024]={0};
	char *_fileBuf=(char*)malloc(7*1024*1024);
	snprintf(src_path,sizeof(src_path),"%s%s",SOR,argv[1]);
	snprintf(dec_pathC,sizeof(dec_pathC),"%s%s",SOR,argv[2]);
	
	addHead(src_path,dec_pathC);
	fdRead=open(dec_pathC,O_RDONLY);
	
	//test read decFile
	while ((readCnt = read(fdRead, (void *)_readBuf, sizeof(_readBuf)))  > 0)
        { 
			memcpy(_fileBuf+pFileLen, _readBuf, readCnt);         
            pFileLen += readCnt;
            memset((void *)_readBuf, 0, sizeof(_readBuf));
        }
	image_header_t* readTest=(image_header_t*)malloc(sizeof(_fileBuf));
    readTest=(image_header_t*)_fileBuf;
	printf("_fileBuf->ih_size:%d\n",readTest->ih_size);
		
}


