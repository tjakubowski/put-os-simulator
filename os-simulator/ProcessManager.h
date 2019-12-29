#pragma once
#include <list>
#include <string>
#include <algorithm>
#include "PCB.h"

class ProcessManager
{
	static int last_process_id_;
	std::list<PCB*> processes_;
	std::list<PCB*> ready_processes_;
	std::list<PCB*> waiting_processes_;
	PCB* running_process_ = nullptr;
	PCB* dummy_process_ = nullptr;
public:
	ProcessManager();
	void CreateProcess(std::string process_name, std::string process_file, int priority);

	void KillProcess(PCB* process);
	void KillProcess(int process_id);
	void KillProcess(std::string process_name);
	
	PCB* GetProcess(int process_id);
	PCB* GetProcess(std::string process_name);

	void SetProcessRunning(PCB* process);
	void SetProcessRunning(int process_id);
	void SetProcessRunning(std::string process_name);
	
	void SetProcessReady(PCB* process);
	void SetProcessReady(int process_id);
	void SetProcessReady(std::string process_name);
	
	void SetProcessWaiting(PCB* process);
	void SetProcessWaiting(int process_id);
	void SetProcessWaiting(std::string process_name);
};
