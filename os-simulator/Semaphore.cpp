#include "pch.h"
#include "Semaphore.h"
#include <string>

Semaphore::Semaphore(int k) : value(k)
{
}


bool Semaphore::Wait(Process* process)
{
	if (value > 0)
	{
		value--;
		return true;
	}
	else
	{
		value--;
		ProcessManager::GetInstance().SetProcessWaiting(process);
		queue.push(process);
		return false;
	}
}

Process* Semaphore::Signal()
{
	if (!queue.empty())
	{
		const auto process = queue.front();
		ProcessManager::GetInstance().SetProcessReady(process);
		queue.pop();
		value++;
		return process;
	}
	else
	{
		value++;
		return nullptr;
	}
}

bool Semaphore::is_opened()
{
	return value != 1;
}

//interfejs pracy krokowej 

void Semaphore::show_Semaphore() 
{
	TablePrinter table_printer;
	table_printer.AddColumn("Aktualny stan Semaphora", 3);
	table_printer.AddColumn("Aktualny rozmiar kolejki", 2);


	if (queue.empty())
	{
		table_printer.PrintHeader();
		table_printer << value << "Kolejka jest pusta";
	}
	else
	{
		table_printer.AddColumn("Poczatek kolejki", 2);
		table_printer.PrintHeader();
		table_printer << value << queue.size() << queue.front()->name();
	}
	table_printer.PrintFooter();
}
