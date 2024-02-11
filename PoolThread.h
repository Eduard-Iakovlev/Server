#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

using namespace std;

typedef function<void()> task_type;
typedef void (*FuncType)(int, char*);

class PoolThread {
public:
	void start();
	void stop();
	void push_task(FuncType f, int arg, char* mess);
	void threadFunc();
private:
	vector<thread> m_threads;
	queue<task_type> m_task_queue;
	mutex m_locker;
	condition_variable m_event_holder;
	volatile bool m_work;
};
