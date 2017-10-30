#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <string.h>  
  
typedef struct _msg  
{  
    long mtype;  
    char mtext[50];  
}MSG;  
  
int main(int argc, char *argv[])  
{  
    key_t key;  
    int  msgqid;  
    MSG msg;  
      
    key = ftok("./", 2015); // key 值  
      
    // 创建消息队列  
    msgqid = msgget(key, IPC_CREAT|0666);  
    if(msgqid == -1)  
    {  
        perror("msgget");  
        exit(-1);  
    }  
      
    msg.mtype = 10; // 消息类型  
    strcpy(msg.mtext, "hello mike"); // 正文内容  
      
    /* 添加消息 
    msg_id:消息队列标识符 
    &msg：消息结构体地址 
    sizeof(msg)-sizeof(long)：消息正文大小 
    0：习惯用0 
    */  
    msgsnd(msgqid, &msg, sizeof(msg)-sizeof(long), 0);  
      
    return 0;  
}  