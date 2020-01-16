#include "pch.h"
#include "ProcessManager.h"
#include "RAM.h"

int ProcessManager::last_process_id_ = 0;

ProcessManager::ProcessManager()
{
	dummy_process_ = CreateProcess("dummy", "dummy", 0);
	SetProcessRunning(dummy_process_);
}

ProcessManager::~ProcessManager()
{
	for (auto&& process : processes_)
		delete process;
	processes_.clear();
}

void ProcessManager::RemoveFromVector(Process* process, std::vector<Process*>& vector) const
{
	vector.erase(std::remove(vector.begin(), vector.end(), process), vector.end());
}

void ProcessManager::SetProcessNew(Process* process)
{
	process->set_process_state(Process::New);
	new_processes_.push_back(process);
}

Process* ProcessManager::CreateProcess(std::string process_name, std::string process_file, const int priority)
{
	const auto process = new Process(process_name, process_file, priority, ++last_process_id_);
	processes_.push_back(process);

	SetProcessNew(process);
	// TODO: Call adding process to virtual memory
	
	try
	{
		// TODO: Call adding process to RAM
		SetProcessReady(process);
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
	}

	// TODO: Call scheduler

	return process;
}

void ProcessManager::KillProcess(Process* process)
{
	if (process == dummy_process_)
		throw std::exception("Dummy process cannot be killed");
	
	switch (process->process_state())
	{
	case Process::New:
		RemoveFromVector(process, new_processes_); break;
	case Process::Waiting:
		RemoveFromVector(process, waiting_processes_); break;
	case Process::Ready:
		RemoveFromVector(process, ready_processes_); break;
	case Process::Running:
		running_process_ = dummy_process_; break;
	default: break;
	}

	RemoveFromVector(process, processes_);

	// TODO: Call deleting process memory
	// TODO: Iterate over new processes and try to allocate them in RAM
	// TODO: Call scheduler

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

void ProcessManager::SetProcessWaiting(Process* process)
{
	switch (process->process_state())
	{
	case Process::New:
		RemoveFromVector(process, new_processes_); break;
	case Process::Waiting:
		return;
	case Process::Ready:
		RemoveFromVector(process, ready_processes_); break;
	case Process::Running:
		SetProcessRunning(dummy_process_); break;
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

void ProcessManager::SetProcessReady(Process* process)
{
	switch (process->process_state())
	{
	case Process::New:
		RemoveFromVector(process, new_processes_); break;
	case Process::Waiting:
		RemoveFromVector(process, waiting_processes_); break;
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

void ProcessManager::SetProcessRunning(Process* process)
{
	switch(process->process_state())
	{
	case Process::New:
		RemoveFromVector(process, new_processes_); break;
	case Process::Waiting:
		RemoveFromVector(process, waiting_processes_); break;
	case Process::Ready:
		RemoveFromVector(process, ready_processes_); break;
	case Process::Running:
		return;
	default: break;
	}

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

void ProcessManager::PrintProcesses() const
{
	TablePrinter table_printer;
	table_printer.AddColumn("ID", 2);
	table_printer.AddColumn("Name", 10);
	table_printer.AddColumn("File", 10);
	table_printer.AddColumn("Priority", 2);
	table_printer.AddColumn("State", 7);

	table_printer.PrintHeader();
	for (auto process : processes_)
		table_printer << process->id() << process->name() << process->file_name() << process->priority() << process->process_state();
	table_printer.PrintFooter();
}

void ProcessManager::PrintProcess(Process* process) 
{
	TablePrinter table_printer;
	table_printer.AddColumn("ID", 2);
	table_printer.AddColumn("Name", 10);
	table_printer.AddColumn("File", 10);
	table_printer.AddColumn("Priority", 2);
	table_printer.AddColumn("State", 7);

	table_printer.PrintHeader();
	table_printer << process->id() << process->name() << process->file_name() << process->priority() << process->process_state();
	table_printer.PrintFooter();
}

void ProcessManager::PrintProcess(int process_id) 
{
	PrintProcess(GetProcess(process_id));
}

void ProcessManager::PrintProcess(std::string process_name) 
{
	PrintProcess(GetProcess(process_name));
}

std::vector<Process*> ProcessManager::processes() const
{
	return processes_;
}

std::vector<Process*> ProcessManager::new_processes() const
{
	return new_processes_;
}

std::vector<Process*> ProcessManager::waiting_processes() const
{
	return waiting_processes_;
}

std::vector<Process*> ProcessManager::ready_processes() const
{
	return ready_processes_;
}

Process* ProcessManager::running_process() const
{
	return running_process_;
}
