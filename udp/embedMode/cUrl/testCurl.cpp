//data 11.15 by gong
#include <curl/curl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
#include<sys/types.h>

#define POSTURL "http://121.201.63.127:8080/upload" 
using namespace std;
int ifExePro(pid_t status){
	
	if(status==-1){
		
		cout<<"system error!"<<endl;
		return -1;
	}else{
		
		cout<<"exit status values:"<<status<<endl;
		if(WIFEXITED(status)){
			if(!WEXITSTATUS(status)){
				cout<<"program success!"<<endl;
				return 0;
				
			}else{
				
				cout<<"program return fail"<<endl;
				return -1;
			}
			
		}else{
			
			cout<<"exit status="<<WIFEXITED(status)<<endl;
			return -1;
		}
		
	}	
	
	
}


bool postUrl(char *saveReturn,char* filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(saveReturn, "w")) == NULL)
        return false;
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
        /*curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "-F 'file=@3185164.html' -F 'time=20171002'");    // 指定post内容
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, "http://121.201.63.127:8080/upload");   // 指定url
		*/
		struct curl_httppost *formpost = 0;
		struct curl_httppost *lastptr  = 0;
		
		curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "file", CURLFORM_FILE, filename, CURLFORM_END);
		curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, "time", CURLFORM_PTRCONTENTS, "20171002", CURLFORM_END);	
		
		curl_easy_setopt(curl, CURLOPT_URL, POSTURL);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
						
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //将返回的http头输出到fp指向的文件
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp); //将返回的html主体数据输出到fp指向的文件
		
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return true;
}


int main(int argc,char** argv){
	
	postUrl("./get.html",argv[1]);  //push file
	
	//remove sorce file
	pid_t status;
	char rm_file[200];
	snprintf(rm_file,sizeof(rm_file),"%s %s","rm -rf",argv[1]);
	cout<<rm_file<<endl;
	status=system(rm_file);
	if(ifExePro(status)!=0)
		cout<<"fail!!!"<<endl;
	return 0;
		
}
