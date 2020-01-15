#pragma once
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include "TablePrinter.h"
#include "Process.h"
#include "Singleton.h"

class ProcessManager : public Singleton<ProcessManager>
{
	friend class Singleton<ProcessManager>;

	static int last_process_id_;
	std::vector<Process*> processes_;
	std::vector<Process*> ready_processes_;
	std::vector<Process*> waiting_processes_;
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
	
	void PrintProcesses() const;
	void PrintProcess(Process* process);
	void PrintProcess(int process_id);
	void PrintProcess(std::string process_name);

	std::vector<Process*> processes() const;
	std::vector<Process*> ready_processes() const;
	std::vector<Process*> waiting_processes() const;
	Process* running_process() const;
};
