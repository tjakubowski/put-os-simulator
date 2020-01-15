#include "pch.h"
#include "RAM.h"

#include<fstream>

using namespace std;

bool compare(const Free_blocks& a, const Free_blocks& b) {
	return a.begining < b.begining;
}

int RAM::add_to_RAM(Process* process) { //zamienic na process
	fstream file;
	string commands, help, line[128];
	int max_size = 0;
	int list_index = 0;
	int id = process->id();
	
	file.open(process->file_name());
	int length = 0, counter = 0;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, help);
			line[counter] = help;
			counter++;		 //string stream
			for (int i = 0; i <= help.length(); i++) //todo do uzgodnienia z FAT jak ma wygl¹daæ czytanie. 
			{
				if (help[i] != '\n')
					length++;


			}
			commands += help;
			commands += '\n';
		}


	}
	else {
		cout << "this file cannot be found. Try to change Filename parameter" << endl;
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
	{
		cout << "\nthis file is empty\n" << endl;
		return 3;

	}
	bool find_space = false;
	try {


		if (free_space < length || free_space < 2)
		{
			cout << "\nthere is no enough space\n" << endl;
			return 1;
		}
		else {
			{
				if (Free_blocks_list.empty() == false) {
					for (auto e : Free_blocks_list)
					{
						if (e.size >= length)
							find_space = true;
					}
				}
				else {
					find_space = true;
				}
				if (find_space) {
					Free_blocks F_b; //to trzeba bêdzie chyba gdzieœ wczeœniej zainicjowaæ tbh.

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
								fbi->biggest = false;
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

					RAM_process process;

					process.id = id;
					process.size = length;
					process.commands = commands;
					process.start = F_b.begining - length;
					RAM_processes_list.push_back(process);

					free_space -= length;
				}
			}
		}

	}
	catch (int) { return 1; };
	//Process process(); //tutaj trzeba przekazac id, wielkosc, komendy i takie tam do listy procesów

	
}

void RAM::show_RAM() {
	list<RAM_process>::iterator it;
	int i = 0, ilosc_w = 0;
	cout << "\n\tMEMORY\n  " << endl << "[ID]\t size\t  begining\t end" << endl;
	for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); ++it)
	{
		cout << it->id << "\t " << it->size << "\t   " << it->start << "\t\t  " << it->start + it->size << it->commands<< endl;
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
}

void RAM::delete_from_RAM(Process* process) {
	int size = 0;
	Free_blocks F_b;
	int id = process->id();
	try {
		list<RAM_process>::iterator it;
		bool id_not_exist = true;
		for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); ++it) {
			if (it->id == id) {
				id_not_exist = false;
				break;
			}
		}
		if (id_not_exist) {
			std::cout << "tego procesu nie ma w pamieci";
			throw 0;

		}
		free_space += it->size;
		size = it->size;
		int starting_point = it->start;

		
		F_b.begining = starting_point;
		F_b.size = it->size;
		F_b.end = starting_point + F_b.size;
		Free_blocks_list.push_back(F_b);

		RAM_processes_list.erase(it);
		merge_RAM();
	}
	catch (int) { "nie ma takiego procesu w pamieci"; };
	if (RAM_processes_list.empty()) {
		//std::cout << "JESTEM PUSTA CALKIEM!!!";
		list<Free_blocks>::iterator fbi;
		F_b.begining = 1;
		F_b.end = 128;
		F_b.size = F_b.end - F_b.begining;
		Free_blocks_list.clear();
		Free_blocks_list.push_back(F_b);

	}
}

char RAM::char_RAM(Process* process, int position) {
	list<RAM_process>::iterator it;
	string commands;
	char character;
	int id = process->id();
	for (it = RAM_processes_list.begin(); it != RAM_processes_list.end(); it++) {
		if (it->id == id) {
			commands = it->commands;
		}
	}
	int pos = 0;
	for (int i = 0; i < commands.length(); i++) {
		if (i == position) {
			pos = i;
			break;
		}

	}
	return commands[pos];

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
	list<Free_blocks>::iterator it, it2, it3;
	int loop = 0;
	bool help = false;
	Free_blocks_list.sort(compare);

	do {
		help = false;
		loop = 0;
		for (it = Free_blocks_list.begin(); it != Free_blocks_list.end(); ++it) 
		{
			if (loop >= 1) {
				if (it->begining == it2->end) {
					Free_blocks F_b;
					help = true;
					F_b.begining = it->begining;
					F_b.end = it->end;
					F_b.size = it->size + it2->size;

					Free_blocks_list.push_front(F_b);
				}
				if (help == true) {
					Free_blocks_list.sort(compare);
					it++;
					Free_blocks_list.erase(it2, it);
				}
			}
			if (help == true) {
				break;
				loop++;
				it2 = it;
			}
		} 
	} while (help == true);
}