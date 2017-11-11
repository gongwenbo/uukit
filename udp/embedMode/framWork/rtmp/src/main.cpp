#include <stdio.h>
#include "play.h"

int main()
{
	printf("start...\n");
	char *url = "rtmp://192.168.99.203:1935/hls";
	
	while(1)
	{
		char c = getchar();
		getchar();
		if(c == 's')
			rtmp_start(url);
		else if(c == 'q')
			rtmp_pause();
		else if(c == 'e')
			break;
		else
			printf("Input:\ns 开启推流\nq  结束推流\ne  程序推出\n");
	}
	
	printf("end...\n");
	return 0;
}