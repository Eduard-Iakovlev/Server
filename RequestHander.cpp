#include "RequestHander.h"
#include "PoolThread.h"

RequestHander::RequestHander(){
	m_pool.start();
}

RequestHander::~RequestHander(){
	m_pool.stop();
}

void RequestHander::push_task(FuncType f, int arg, char* mess){
	m_pool.push_task(f, arg, mess);
}
