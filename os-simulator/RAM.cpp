#include "pch.h"
#include "RAM.h"


#include<fstream>

using namespace std;

bool compare(const Free_blocks& a, const Free_blocks& b) {
	return a.begining < b.begining;
}


int RAM::add_to_RAM(Process* process) {
	fstream file;
	string commands, help, help1, line[256];
	int max_size = 0;
	int list_index = 0;
	int id = process->id();


	int length = 0, counter = 0;
	auto segment_tab = process->segment_tab();

	if (segment_tab[0]->data != "") {
		help = segment_tab[0]->data;
		commands += help;
	}

	if (segment_tab[1]->data != "") {
		help1 += segment_tab[1]->data;
		length += help.size() + help1.size();
		commands += help1;
		
	}

	bool empty = true;
	for (int i = 0; i < commands.length(); i++)
	{
		if (commands[i] != ' ' && commands[i] != '\n')
		{
			empty = false;
			break;
		}
	}

	if (empty)
		throw std::exception("ten plik jest pusty");

	bool find_space = false;

	if (free_space < length || free_space < 2)
		throw std::exception("nie ma wystarczjaco duzo miejsca, aby dodac do pamieci");

	if (Free_blocks_list.empty() == false) {
		for (auto e : Free_blocks_list)
		{
			if (e.size >= length)
				find_space = true;
			else {
				throw exception("nie ma wystarczajco duzej dziury aby dodac do pamieci");
			}
		}
	}
	else {
		find_space = true;
	}
	if (find_space) {
		Free_blocks F_b;

		if (last == 0) {
			Free_blocks_list.pop_back();
			F_b.begining = length+1; 
			last = length+1;
			F_b.end = 256;
			F_b.size = F_b.end - F_b.begining;
			Free_blocks_list.push_back(F_b);
		}
		else {
			list<Free_blocks>::iterator fbi;

			for (fbi = Free_blocks_list.begin(); fbi != Free_blocks_list.end(); fbi++) {


				if (max_size < fbi->size) {
					max_size = fbi->size;
					list_index = distance(Free_blocks_list.begin(), fbi);
				}

			}

			fbi = Free_blocks_list.begin();
			advance(fbi, list_index);
			fbi->biggest = true;

			for (fbi = Free_blocks_list.begin(); fbi != Free_blocks_list.end(); fbi++) {
				if (fbi->biggest == true && fbi->size >= length)
				{
					F_b.begining = fbi->begining + length;

					break;

				}

			}
			bool finder = false;
			for (auto a : RAM_processes_list) {
				if (a.start >= F_b.begining) {
					F_b.end = a.start-1;
					finder = true;
					break;
				}
			}
			if (!finder) {
				F_b.end = 256;
			}
			F_b.size = F_b.end - F_b.begining+1; 

			if (F_b.size > 0)
				Free_blocks_list.emplace_front(F_b);

			Free_blocks_list.erase(fbi);
		}

		RAM_process RAM_process;

		RAM_process.id = id;
		RAM_process.size = length;
		RAM_process.commands = commands;
		RAM_process.start = (F_b.begining - length);
		RAM_processes_list.push_back(RAM_process);

		segment_tab[1]->is_in_RAM = true;
		segment_tab[1]->baseRAM = RAM_process.start;
		process->set_segment_tab(segment_tab);
		int j = 0;
		for (auto i = RAM_process.start; i < (RAM_process.size + RAM_process.start); i++) {

			memory[i] = commands[j];
			
			j++;
		}




		free_space -= length;
	}





}

void RAM::show_RAM() {

	/*cout << "\n\tMEMORY\n  " << endl << "[ID]\t size\t  begining\t end" << endl;
	   for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); ++it)
	   {
		   cout << it->id << "\t " << it->size << "\t   " << it->start << "\t\t  " << it->start + it->size <<"\t" << it->commands<< endl;
		   i++;
	   }

	   if (i == 0)
		   cout << "Brak procesow w pamieci" << endl;

	   cout << "\nPozostalo wolnej pamieci:  " << endl;
	   for (auto e : Free_blocks_list)
	   {
		   cout << "\tStart: " << e.begining << " --> End: " << e.end << "  =  Size: " << e.size << endl;
		   ilosc_w += e.size;
	   }
	   cout << "Razem:  " << ilosc_w << endl;
	   cout << "" << endl;

	   for (int i = 1; i < 129; i++) {
		   std::cout << i << ": " << memory[i] << "\t";

	   }

	   std::cout << endl;
	   std::cout << endl;
	   std::cout << endl;
	   */

	list<RAM_process>::iterator it;
	int i = 0, ilosc_w = 0;

	TablePrinter tp;
	tp.AddColumn("ID", 4);
	tp.AddColumn("ROZMIAR", 5);
	tp.AddColumn("POCZATEK", 5);
	tp.AddColumn("KONIEC", 5);
	tp.AddColumn("KOMENDY", 70);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "LISTA PROCESOW W PAMIECI" << endl;
	tp.PrintHeader();

	for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); ++it)
	{
		string com = it->commands;
		tp << it->id << it->size << it->start << ((it->start + it->size) - 1) << com;
		i++;
	}
	if (i == 0)
		cout << "Brak procesow w pamieci" << endl;

	tp.PrintFooter();
std:cout << std::endl;

	TablePrinter tp1;

	tp1.AddColumn("POCZATEK", 5);
	tp1.AddColumn("KONIEC", 5);
	tp1.AddColumn("ROZMIAR", 5);
	std::cout << "LISTA WOLNYCH DZIUR" << endl;
	tp1.PrintHeader();

	;
	for (auto e : Free_blocks_list)
	{
		tp1 << e.begining << e.end << e.size;
		ilosc_w += e.size;
	}
	cout << "CALKOWITE WOLNE MIEJSCE:  " << ilosc_w << endl;
	tp1.PrintFooter();
	std::cout << std::endl;
	std::cout << "PAMIEC RAM" << std::endl;
	TablePrinter tp2;
	tp2.AddColumn("KOMORKA", 10);
	tp2.AddColumn("DANE", 8 * 2);
	tp2.PrintHeader();

	for (int i = 0; i < 32; i++)
	{
		std::string help = std::to_string((i * 8) + 1) + " - " + std::to_string(8 * (1 + i));

		std::string bytes;

		for (int j = 1; j < 9; j++)
		{
			bytes += memory[i * 8 + j];
			bytes += " ";
		}
		tp2 << help;
		tp2 << bytes;
	}

	/*for (int i = 1; i < 129; i++) {
		std::cout<<i << ": "  << memory[i] << "\t";
	}*/
	tp2.PrintFooter();












}

void RAM::delete_from_RAM(Process* process) {
	int size = 0;
	Free_blocks F_b;
	int id = process->id();
	auto segment_tab = process->segment_tab();

	list<RAM_process>::iterator it;
	bool id_not_exist = true;
	for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); ++it) {
		if (it->id == id) {
			id_not_exist = false;
			break;
		}
	}
	if (id_not_exist)
		throw std::exception("tego procesu nie ma w pamieci");

	free_space += it->size;
	size = it->size;
	int starting_point = it->start;


	F_b.begining = starting_point;
	F_b.size = it->size;
	F_b.end = starting_point + F_b.size-1; 
	Free_blocks_list.push_back(F_b);

	/*for (int i = it->start; i < F_b.end; i++) {
		memory[i] = "=";
	}*/

	for (int i = 0; i < segment_tab.size(); i++) {
		segment_tab[i]->baseRAM = -1;
		segment_tab[i]->is_in_RAM = false;
	}
	process->set_segment_tab(segment_tab);

	RAM_processes_list.erase(it);
	merge_RAM();

	if (RAM_processes_list.empty()) {

		list<Free_blocks>::iterator fbi;
		F_b.begining = 1;
		F_b.end = 256;
		F_b.size = F_b.end - F_b.begining;
		Free_blocks_list.clear();
		Free_blocks_list.push_back(F_b);

	}
}



string RAM::read_RAM(Process* process, int counter) {
	list<RAM_process>::iterator it;
	string commands, back;
	int id = process->id();
	for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); it++)
	{
		if (it->id == id)
		{
			int count = 0; int line = 1; int i = 0;

			for (int i = 0; i < it->commands.length(); it++)
			{
				if (it->commands[i] == '\n') {
					count++;
				}
				if (count == counter)
					break;


			}
			if (it->commands[i] == ';')
				i++;

			int quant = 5, loop = 0;
			for (int j = i; j <= commands.length(); j++)
			{
				if (j == it->commands.length())
					break;

				if (it->commands[j] != ';')
				{
					it->MemoryPointer++;
					back += it->commands[j];
				}
				else break;
			}
		}
	}
	return back;

}

void RAM::merge_RAM() {
	list<Free_blocks>::iterator it, it2;
	int loop = 0;
	bool help = false;
	Free_blocks_list.sort(compare);

	do {
		help = false;
		loop = 0;
		for (it = Free_blocks_list.begin(); it != Free_blocks_list.end(); ++it)
		{
			if (loop >= 1) {

				if (it->begining-1 == it2->end)
				{
					Free_blocks F_b;
					help = true;
					F_b.begining = it2->begining;
					F_b.end = it->end;
					F_b.size = it->size + it2->size;


					Free_blocks_list.push_front(F_b);
				}
				if (help == true)
				{
					Free_blocks_list.sort(compare);
					it++;
					Free_blocks_list.erase(it2, it);

				}
			}
			if (help == true) {


				break;
			}
			loop++;
			it2 = it;
		}
	} while (help == true);
}


void RAM::modify_RAM(int RAMposition, int byte) {
	if (RAMposition > 256 || RAMposition < 1) {
		throw std::exception("podana liczba przekracza zakres pamieci");
	}
	else {
		memory[RAMposition] = byte;
		int position = stoi(memory[RAMposition]);
	}
	
	
}
string RAM::char_RAM(int position) {
	if (position > 256 || position < 1) {
		throw std::exception("podana liczba przekracza zakres pamieci");
	}
	else {
		return memory[position];
	}


}