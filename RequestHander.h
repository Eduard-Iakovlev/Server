#pragma once
#include "PoolThread.h"
class RequestHander {
public:
	RequestHander();
	~RequestHander();
	void push_task(FuncType f, int arg, char* mess);
private:
	PoolThread m_pool;
};

