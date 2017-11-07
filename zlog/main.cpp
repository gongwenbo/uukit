//data:2017.11.7
#include <stdio.h>
#include <zlog.h>
int main (int argc,char**argv)
{
	int rc;
	zlog_category_t *c; //配置文件
	rc=zlog_init("test_hello.conf");
	if(rc){
		printf("init failed\n");
		return -1;
		
	}
	c=zlog_get_category("my_cat");  //分类
	if(!c){
		printf("get cat fail\n");
		zlog_fini();
		return -2;
		
	}
	//级别测试
	zlog_info(c,"info");
	zlog_error(c,"error");
	zlog_debug(c,"debug");
	zlog_warn(c,"ware");
	zlog_fini();
	return 0;

	/* //下面的例子也是可以测试的，等价于上面。
	int rc;
	char aa[120]="test ok!";
	rc = dzlog_init("test_hello.conf", "my_cat");
	if (rc) {
		printf("init failed\n");
		return -1;
	}
	dzlog_info("like:%s",aa);
	dzlog_debug("test:%s",aa);
	dzlog_warn("warn");
	dzlog_error("error");
	zlog_fini();
	return 0;
	*/
}





