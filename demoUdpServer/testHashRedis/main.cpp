#include "common.h"
int main(int agrc,char* argv[])
{
	string key="like";
	string feild="one";
	string values="one";
	string retu;
	
	redisOperator *PredisOperator=new redisOperator();
	retu=PredisOperator->hashHset(key,feild,values);
	cout<<"retu:"<<retu<<endl;
	return 0;
	
	
}