#include "pch.h"
#include "ProcessManager.h"
#include <ostream>
#include <iostream>

int ProcessManager::last_process_id_ = 0;

ProcessManager::ProcessManager()
{
	dummy_process_ = new Process("dummy", "", 0, ++last_process_id_);
	running_process_ = dummy_process_;
}

ProcessManager::~ProcessManager()
{
	delete dummy_process_;
	delete running_process_;
}

void ProcessManager::CreateProcess(std::string process_name, std::string process_file, const int priority)
{
	const auto process = new Process(process_name, process_file, priority, ++last_process_id_);
	processes_.push_back(process);
	SetProcessWaiting(process);
	// TODO: Consider moving it to new processes list
	// TODO: Add setting resources for process
}

void ProcessManager::KillProcess(Process* process)
{
	switch (process->process_state())
	{
	case Process::Waiting:
		waiting_processes_.remove(process); break;
	case Process::Ready:
		ready_processes_.remove(process); break;
	case Process::Running:
		running_process_ = dummy_process_; break;
	default: break;
	}

	processes_.remove(process);
		
	delete process;
}

void ProcessManager::KillProcess(int process_id)
{
	KillProcess(GetProcess(process_id));
}

void ProcessManager::KillProcess(std::string process_name)
{
	KillProcess(GetProcess(process_name));
}

Process* ProcessManager::GetProcess(int process_id)
{
	auto process = std::find_if(processes_.begin(), processes_.end(), [process_id](Process* process) { return process->id() == process_id; });

	if (process == processes_.end())
		throw std::exception("Process doesn't exist"); // TODO: Create own exception
	
	return *process;
}

Process* ProcessManager::GetProcess(std::string process_name)
{
	auto process = std::find_if(processes_.begin(), processes_.end(), [process_name](Process* process) { return process->name() == process_name; });

	if (process == processes_.end())
		throw std::exception("Process doesn't exist"); // TODO: Create own exception

	return *process;
}

void ProcessManager::SetProcessRunning(Process* process)
{
	switch(process->process_state())
	{
	case Process::Waiting:
		waiting_processes_.remove(process); break;
	case Process::Ready:
		ready_processes_.remove(process); break;
	case Process::Running:
		return;
	default: break;
	}

	SetProcessReady(running_process_);

	process->set_process_state(Process::Running);
	running_process_ = process;
}

void ProcessManager::SetProcessRunning(int process_id)
{
	SetProcessRunning(GetProcess(process_id));
}

void ProcessManager::SetProcessRunning(std::string process_name)
{
	SetProcessRunning(GetProcess(process_name));
}

void ProcessManager::SetProcessReady(Process* process)
{
	switch (process->process_state())
	{
	case Process::Waiting:
		waiting_processes_.remove(process); break;
	case Process::Ready:
		return;
	case Process::Running:
		SetProcessRunning(dummy_process_); break;
	default: break;
	}

	process->set_process_state(Process::Ready);
	ready_processes_.push_back(process);
}

void ProcessManager::SetProcessReady(int process_id)
{
	SetProcessReady(GetProcess(process_id));
}

void ProcessManager::SetProcessReady(std::string process_name)
{
	SetProcessReady(GetProcess(process_name));
}

void ProcessManager::SetProcessWaiting(Process* process)
{
	switch (process->process_state())
	{
	case Process::Waiting:
		return;
	case Process::Running:
		SetProcessRunning(dummy_process_); break;
	case Process::Ready:
		ready_processes_.remove(process); break;
	default: break;
	}

	process->set_process_state(Process::Waiting);
	waiting_processes_.push_back(process);
}

void ProcessManager::SetProcessWaiting(int process_id)
{
	SetProcessWaiting(GetProcess(process_id));
}

void ProcessManager::SetProcessWaiting(std::string process_name)
{
	SetProcessWaiting(GetProcess(process_name));
}
