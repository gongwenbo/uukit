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
      
      
    key = ftok("./", 2015); // key 值  
      
    // 创建消息队列  
    msgqid = msgget(key, IPC_CREAT|0666);  
    if(msgqid == -1)  
    {  
        perror("msgget");  
        exit(-1);  
    }  
      
    MSG msg;  
    memset(&msg, 0, sizeof(msg));  
      
    /* 取出类型为 10 的消息 
    msg_id:消息队列标识符 
    &msg：消息结构体地址 
    sizeof(msg)-sizeof(long)：消息正文大小 
    (long)10：消息的类型 
    0：习惯用0 
    */  
    msgrcv(msgqid, &msg, sizeof(msg)-sizeof(long), (long)10, 0);  
    printf("msg.mtext=%s\n", msg.mtext);   
      
    // 把消息队列删除  
    // IPC_RMID：删除标志位  
    msgctl(msgqid, IPC_RMID, NULL);  
      
    return 0;  
}