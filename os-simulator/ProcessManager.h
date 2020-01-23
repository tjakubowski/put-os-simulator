#pragma once
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include "TablePrinter.h"
#include "Process.h"
#include "RAM.h"
#include "VirtualMemory.h"
#include "CPU.h"
#include "Singleton.h"

class ProcessManager : public Singleton<ProcessManager>
{
	friend class Singleton<ProcessManager>;

	static int last_process_id_;
	std::vector<Process*> processes_;
	std::vector<Process*> new_processes_;
	std::vector<Process*> waiting_processes_;
	std::vector<Process*> ready_processes_;
	Process* running_process_ = nullptr;
	Process* dummy_process_ = nullptr;
	TablePrinter process_printer_;
	void InitializeProcessPrinter();
	void RemoveFromVector(Process* process, std::vector<Process*>& vector) const;
	void SetProcessNew(Process* process);
	void CreateDummyProcess();

public:
	ProcessManager();
	~ProcessManager();
	Process* CreateProcess(std::string process_name, std::string process_file, int priority);

	void CloseProcessFiles(Process* process);
	void RemoveProcessFromMemory(Process* process);
	void TryAllocateNewProcesses();
	void ChangeProcessPriority(std::string process_name, int priority);
	void ChangeProcessPriority(Process* process, int priority);

	void KillProcess(Process* process);
	void KillProcess(int process_id);
	void KillProcess(std::string process_name);
	bool Exists(std::string process_name);

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
	
	void PrintProcesses(std::vector<Process*> processes);
	void PrintProcesses();
	void PrintProcessOpenedFiles(Process* process);
	void PrintProcessOpenedFiles(std::string process_name);
	void PrintProcess(Process* process);
	void PrintProcess(int process_id);
	void PrintProcess(std::string process_name);

	void OpenFile(Process* process, std::string file_name);
	void CloseFile(Process* process, std::string file_name);
	void WriteFile(Process* process, std::string file_name, std::string bytes, bool append = false);
	std::string ReadFile(Process* process, std::string file_name);
	char ReadFileByte(Process* process, std::string file_name);
	void ResetFilePointer(Process* process, std::string file_name);

	std::vector<Process*> processes() const;
	std::vector<Process*> new_processes() const;
	std::vector<Process*> waiting_processes() const;
	std::vector<Process*> ready_processes() const;
	Process* running_process() const;
};
