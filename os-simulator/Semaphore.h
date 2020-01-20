#pragma once
#include <queue>
#include <string>
#include "Singleton.h"
#include "ProcessManager.h"

using namespace std;
class ProcessManager;

class Semaphore
{
protected:
	int value;
	queue<string> queue;
public:

	void Wait(std::string name);
	void Signal();

	Semaphore(int k)
	{
		this->value = k;
	}
	

	//krokowy
	void show_Semaphore();

};
