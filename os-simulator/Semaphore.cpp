#include "pch.h"
#include "Semaphore.h"


Semaphore::Semaphore(int k)
{
	value = k;
}
void Semaphore::Wait(std::string name)
{
	if (value > 0)
	{
		value--;
	}

	else
	{
		value--;
		queue.push(name);
		ProcessManager::GetInstance().SetProcessWaiting(name);
	}
}
void Semaphore::Signal()
{
	if (queue.empty() == false)
	{
		string name = queue.front();
		ProcessManager::GetInstance().SetProcessReady(name);
		queue.pop();
		value++;
	}
	else
	{
		value++;
	}
}



//interfejs pracy krokowej 
