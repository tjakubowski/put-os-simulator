#pragma once
#include <queue>
#include <string>
#include "Singleton.h"
#include "ProcessManager.h"
#include "Process.h"

class ProcessManager;

class Semaphore
{
protected:
	int value;
	queue<Process*> queue{};
public:

	void Wait(Process* process);
	void Signal();

	Semaphore(int k = 1);
	
	void show_Semaphore();

};
