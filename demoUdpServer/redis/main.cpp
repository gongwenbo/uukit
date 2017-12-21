#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <hiredis/hiredis.h>

void updateTtl(char *key) 
{
    redisContext *context = redisConnect("127.0.0.1", 6379);//默认端口，本机redis-server服务开启
    if(context->err) {
        redisFree(context); 
        printf("connect redisServer err:%s\n", context->errstr);
        return ;
    } 

    printf("connect redisServer success\n"); 

	char *cmd ;
	sprintf(cmd,"expire %s 10",key);

    redisReply *reply = (redisReply *)redisCommand(context, cmd);

    if(NULL == reply) {
        printf("command execute failure\n");
        redisFree(context);
        return ;
    }
 
    freeReplyObject(reply);
    printf("%s execute success\n", cmd);

}

int main(void)
{
    char key[50]="like";
	while(1){
		sleep(5);
		updateTtl(key);
	}
    return 0;
}