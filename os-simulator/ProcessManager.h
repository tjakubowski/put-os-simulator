#pragma once
#include <list>
#include "PCB.h"
#include <string>

class ProcessManager
{
	std::list<PCB*> processes_;
	std::list<PCB*> ready_processes_;
	std::list<PCB*> waiting_processes_;
	PCB* running_process_ = nullptr;
	PCB* dummy_process_ = nullptr;
public:
	void CreateProcess(std::string process_name, std::string process_file);
	void KillProcess(PCB process);
	void KillProcess(std::string process_name);
	void KillProcess(int process_id);
	PCB GetProcess(std::string process_name);
	PCB GetProcess(int process_id);
};
