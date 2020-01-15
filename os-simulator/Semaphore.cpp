
#include "pch.h"
#include <iostream>
#include "Semaphore.h"
#include "ProcessManager.h"
Semaphore::Semaphore(int k, ProcessManager *process)
{
	value = k;
	ProcessM = process;
}
bool Semaphore::Wait()
{
	if (value > 0)
	{
		value = value - 1;
		return true;								//wykonujê siê 
	}

	else
	{
		string active_processes = Semaphore::ProcessM->GetProcess->name();
		queue.push(active_processes);
		Semaphore::ProcessM->PrintWaitingProcesses();
		
		
		return false;								//nie 
	}
}
void Semaphore::Signal()
{ 
	if (queue.empty() == false)
	{
		string procesName = queue.front();
		Semaphore::ProcessM->PrintReadyProcesses();
		queue.pop();
		value++;
	}
	else
	{
		value++;
	}
}



//interfejs pracy krokowej 