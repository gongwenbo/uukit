#include "./srcJson/srcJson.h"

#define width "width"
#define heigth "heigth"
#define outFrmRateNum "outFrmRateNum"
#define bitRate	"bitRate"
#define paramter "paramter"

char file_name[50]="test.json";

int main(int argc,char** agrv){
	
	char width_val[100];
	char heigth_val[100];
	char outFrmRateNum_val[100];
	char bitRate_val[100];
	readConf(file_name,paramter,width ,width_val);
	printf("width_val:%s\n",width_val);
	
	readConf(file_name,paramter,heigth ,heigth_val);
	printf("heigth_val:%s\n",heigth_val);
	
	readConf(file_name,paramter,outFrmRateNum ,outFrmRateNum_val);
	printf("outFrmRateNum_val:%s\n",outFrmRateNum_val);
	
	readConf(file_name,paramter,bitRate ,bitRate_val);
	printf("bitRate_val:%s\n",bitRate_val);
	
	return 0;
}



