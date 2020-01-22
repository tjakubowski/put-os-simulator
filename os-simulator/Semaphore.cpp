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

//interfejs pracy krokowej 

void Semaphore::show_Semaphore() 
{
	TablePrinter table_printer;
	table_printer.AddColumn("Aktualny stan Semaphora", 3);
	table_printer.AddColumn("Aktualny rozmiar kolejki", 2);


	if (queue.size() == 0)
	{
		std::cout << "\t" << value << "\nKolejka jest pusta\n" << std::endl;
		
	}
	else
	{
		
		table_printer.AddColumn("poczatek kolejki", 2);
		table_printer.PrintHeader();

		std::cout << "\t" << value << queue.size() << queue.front()->file_name() << std::endl;

		table_printer.PrintFooter();
	}
	table_printer.PrintFooter();
}
