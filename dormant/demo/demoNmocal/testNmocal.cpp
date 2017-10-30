#include "./src/nmOsalPublicFun.h" 
#include "./src/nmOsalQueue.h"
#include "./inc/nmOsal.h"
#include "./inc/nmOsalType.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
typedef struct msg{
	int id;
	char _MSG[50];
	
}MSG;
int main()
{
	unsigned long maxMsgs=10;
	unsigned long ulRet = 0;
	unsigned long m_hQueue;
	unsigned long ulLen=0;
	unsigned long ulResp = 0;
	MSG _MSGsend,_MSGrecieve;
	_MSGsend.id=12;
	sprintf(_MSGsend._MSG,"test");

	
	ulRet = q_vcreate("msg",0,maxMsgs,sizeof(MSG),&m_hQueue);
	if(ulRet!=0)
		cout<<"q_vcreate error"<<endl;
	
	if(0 != q_vsend(m_hQueue,&_MSGsend,sizeof(MSG)) )
		cout<<"q_vsend error!"<<endl;
		
	ulResp = q_vreceive(m_hQueue,1,0,&_MSGrecieve,sizeof(_MSGrecieve),&ulLen);
	if(ulResp!=0)
		cout<<"q_vreceiveERROR!!"<<endl;
	cout<<"q_vreceive data"<<_MSGrecieve._MSG<<endl;
	
	//unsigned long q_vdelete(m_hQueue);		

}
