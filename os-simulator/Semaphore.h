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
	std::string file_name;
	queue<Process*> queue{};
public:

	bool Wait(Process* process);
	Process* Signal();
	bool is_opened();

	Semaphore( int k = 1);
	

	//krokowy
	void show_Semaphore();

};
