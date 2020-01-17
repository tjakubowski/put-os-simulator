#include "pch.h"
#include "Semaphore.h"
#include <string>


Semaphore::Semaphore(int k)
{
	value = k;
}
void Semaphore::Wait(std::string name)
{
	if (value > 0)
	{
		value--;
	}
	else
	{
		value--;
		queue.push(name);
		ProcessManager::GetInstance().SetProcessWaiting(name);
	}
}
void Semaphore::Signal()
{
	if (queue.empty() == false)
	{
		string name = queue.front();
		ProcessManager::GetInstance().SetProcessReady(name);
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

	TablePrinter table_printer;
	table_printer.AddColumn("Aktualny rozmiar kolejki", 2);
	table_printer.AddColumn("poczatek kolejki", 2);
	table_printer.AddColumn("koniec kolejki", 2);
	table_printer.PrintHeader();
	
		std::cout << queue.size()<<queue.front()<<queue.back() << std::endl;
	
	table_printer.PrintFooter();
}