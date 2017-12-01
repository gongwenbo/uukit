#include "common.h"

uv_loop_t *loop = uv_default_loop();

void init(uv_loop_t *loop){
	
	RunLoop* run_loop=new RunLoop();
	run_loop->Runner(loop);
	delete run_loop;
}

int main(int argc,char* argv[]){

	
	init(loop);	

}


