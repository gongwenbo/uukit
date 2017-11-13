#include "./srcJson.h"
#include "../include/cJSON.h"
int readConf(const char* file_name,const char* obj,const char* child_obj ,char* back){
	
	FILE *fp=fopen(file_name,"r");
	fseek(fp,0,SEEK_END);
	long len=ftell(fp);
	fseek(fp,0,SEEK_SET);
	
	char* data=(char*)malloc(len+1);
	fread(data,1,len,fp);
	fclose(fp);
	//printf("file::%s",data);	
	//parse json
	cJSON *root_json = cJSON_Parse(data);
	if (NULL == root_json)
    {
        printf("error:%s\n", cJSON_GetErrorPtr());
        cJSON_Delete(root_json);
        return -1;
    }
	cJSON *data_json = cJSON_GetObjectItem(root_json, obj);
	//char* tem=cJSON_Print(cJSON_GetObjectItem(data_json, child_obj));
	strcpy(back,cJSON_GetObjectItem(data_json, child_obj)->valuestring);
	free(data);	
	return 0;
}