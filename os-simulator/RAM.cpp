#include "pch.h"
#include "RAM.h"


#include<fstream>

using namespace std;

bool compare(const Free_blocks& a, const Free_blocks& b) {
	return a.begining < b.begining;
}


int RAM::add_to_RAM(Process* process) {
	fstream file;
	string commands, help, line[128];
	int max_size = 0;
	int list_index = 0;
	int id = process->id();


	int length = 0, counter = 0;
	auto segment_tab = process->segment_tab();
	if (segment_tab[1]->data != "") {
		help = segment_tab[1]->data;
		length = help.size();

		commands += help;
		commands += '\n';

	}


	else {
		cout << "This string cannot be found." << endl;
		return 2;
	}
	//cout << "all commands together:" << commands << "\n";

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
		throw std::exception("this file is empty");

	bool find_space = false;

	if (free_space < length || free_space < 2)
		throw std::exception("there is no enough space");

	if (Free_blocks_list.empty() == false) {
		for (auto e : Free_blocks_list)
		{
			if (e.size >= length)
				find_space = true;
			else {
				throw exception("there is no hole that is big enough for this process");
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
			F_b.begining = length + 1;
			last = length + 1;
			F_b.end = 128;
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
					F_b.end = a.start - 1;
					finder = true;
					break;
				}
			}
			if (!finder) {
				F_b.end = 128;
			}
			F_b.size = F_b.end - F_b.begining;

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
	list<RAM_process>::iterator it;
	int i = 0, ilosc_w = 0;
	cout << "\n\tMEMORY\n  " << endl << "[ID]\t size\t  begining\t end" << endl;
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

	std::cout << endl;
	std::cout << endl;
	std::cout << endl;
	for (int i = 1; i < 129; i++) {
		std::cout << i << ": " << memory[i] << "\t";

	}
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
		F_b.end = starting_point + F_b.size;
		Free_blocks_list.push_back(F_b);

		for (int i = it->start; i < F_b.end; i++) {
			memory[i] = "=";
		}

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
		F_b.end = 128;
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
		if (it->id==id)
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

				if (it->begining == it2->end) 
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


bool RAM::modify_RAM(int RAMposition, int byte) {

	memory[RAMposition] = byte;
	int position = stoi(memory[RAMposition]);
	if (position == byte)
		return true;
	else
		return false;
}
string RAM::char_RAM(int position) {

	return memory[position];

}