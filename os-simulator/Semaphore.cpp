#include "pch.h"
#include "Semaphore.h"
#include <string>

Semaphore::Semaphore(std::string file_name, int k) : value(k), file_name(file_name)
{
}


void Semaphore::Wait(Process* process)
{
	if (value > 0)
	{
		value--;
	}
	else
	{
		value--;
		queue.push(process);
		ProcessManager::GetInstance().SetProcessWaiting(process);
		process->add_opened_file(file_name);
	}
}
void Semaphore::Signal()
{
	if (queue.empty() == false)
	{
		const auto process = queue.front();
		ProcessManager::GetInstance().SetProcessReady(process);
		process->remove_opened_file(file_name);
		queue.pop();
		value++;
	}
	else
	{
		value++;
	}
}



//interfejs pracy krokowej 

void Semaphore::show_Semaphore() 
{


	TablePrinter table_printer;
	table_printer.AddColumn("Aktualny stan Semaphora", 3);
	
	table_printer.PrintHeader();
	table_printer << value;
	table_printer.PrintFooter();

	table_printer.ClearColumns();

	
	if (queue.size() == 0)
	{
		std::cout << "\nKolejka jest pusta\n" << std::endl;
	}
	else
	{
		table_printer.AddColumn("Aktualny rozmiar kolejki", 2);
		table_printer.AddColumn("poczatek kolejki", 2);
		table_printer.AddColumn("koniec kolejki", 2);
		table_printer.PrintHeader();

		std::cout << queue.size() << queue.front() << queue.back() << std::endl;

		table_printer.PrintFooter();
	}
	

}
