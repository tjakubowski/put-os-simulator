#include "pch.h"
#include "Semaphore.h"
#include <string>

Semaphore::Semaphore( int k) : value(k)
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
	}
}
void Semaphore::Signal()
{
	if (queue.empty() == false)
	{
		const auto process = queue.front();
		ProcessManager::GetInstance().SetProcessReady(process);
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
