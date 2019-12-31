#pragma once
#include <queue>
#include <string>
using namespace std;
class ProcessManager;

class Semaphore
{
public:
	int value;
	queue<string> queue;
	ProcessManager *ProcessM;
	bool Wait();
	void Signal();
	Semaphore(int k, ProcessManager *process);
	Semaphore()
	{
		value = 1;
		ProcessM = nullptr;
	}
};
