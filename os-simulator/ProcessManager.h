﻿#pragma once
#include <list>
#include <string>
#include <algorithm>
#include "Process.h"

class ProcessManager
{
	static int last_process_id_;
	std::list<Process*> processes_;
	std::list<Process*> ready_processes_;
	std::list<Process*> waiting_processes_;
	Process* running_process_ = nullptr;
	Process* dummy_process_ = nullptr;
public:
	ProcessManager();
	~ProcessManager();
	void CreateProcess(std::string process_name, std::string process_file, int priority);

	void KillProcess(Process* process);
	void KillProcess(int process_id);
	void KillProcess(std::string process_name);
	
	Process* GetProcess(int process_id);
	Process* GetProcess(std::string process_name);

	void SetProcessRunning(Process* process);
	void SetProcessRunning(int process_id);
	void SetProcessRunning(std::string process_name);
	
	void SetProcessReady(Process* process);
	void SetProcessReady(int process_id);
	void SetProcessReady(std::string process_name);
	
	void SetProcessWaiting(Process* process);
	void SetProcessWaiting(int process_id);
	void SetProcessWaiting(std::string process_name);
	
	void PrintAllProcesses() const;
	void PrintWaitingProcesses() const;
	void PrintReadyProcesses() const;
	void PrintRunningProcess() const;
	void PrintProcesses() const;
	void PrintProcess(Process* process);
	void PrintProcess(int process_id);
	void PrintProcess(std::string process_name);

	std::list<Process*> processes() const;
	std::list<Process*> ready_processes() const;
	std::list<Process*> waiting_processes() const;
	Process* running_process() const;
};
