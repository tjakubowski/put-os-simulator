#include "ProcessManager.h"

int ProcessManager::last_process_id_ = 0;

ProcessManager::ProcessManager()
{
	dummy_process_ = new PCB("dummy", "", 0, ++last_process_id_);
	SetProcessRunning(dummy_process_);
}

void ProcessManager::CreateProcess(std::string process_name, std::string process_file, const int priority)
{
	const auto process = new PCB(process_name, process_file, priority, ++last_process_id_);
	processes_.push_back(process);
	SetProcessWaiting(process);
	// TODO: Consider moving it to new processes list
	// TODO: Add setting resources for process
}

void ProcessManager::KillProcess(PCB* process)
{
	switch (process->process_state())
	{
	case PCB::Waiting:
		waiting_processes_.remove(process); break;
	case PCB::Ready:
		ready_processes_.remove(process); break;
	case PCB::Running:
		SetProcessRunning(dummy_process_); break;
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

PCB* ProcessManager::GetProcess(int process_id)
{
	return *std::find_if(processes_.begin(), processes_.end(), [process_id](const PCB& process) { return process.id() == process_id; });
}

PCB* ProcessManager::GetProcess(std::string process_name)
{
	return *std::find_if(processes_.begin(), processes_.end(), [process_name](const PCB& process) { return process.name() == process_name; });
}

void ProcessManager::SetProcessRunning(PCB* process)
{
	switch(process->process_state())
	{
	case PCB::Waiting:
		waiting_processes_.remove(process); break;
	case PCB::Ready:
		ready_processes_.remove(process); break;
	case PCB::Running:
		return;
	default: break;
	}

	SetProcessReady(running_process_);

	process->set_process_state(PCB::Running);
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

void ProcessManager::SetProcessReady(PCB* process)
{
	switch (process->process_state())
	{
	case PCB::Waiting:
		waiting_processes_.remove(process); break;
	case PCB::Ready:
		return;
	case PCB::Running:
		SetProcessRunning(dummy_process_); break;
	default: break;
	}

	process->set_process_state(PCB::Ready);
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

void ProcessManager::SetProcessWaiting(PCB* process)
{
	switch (process->process_state())
	{
	case PCB::Waiting:
		return;
	case PCB::Running:
		SetProcessRunning(dummy_process_); break;
	case PCB::Ready:
		ready_processes_.remove(process); break;
	default: break;
	}

	process->set_process_state(PCB::Waiting);
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
