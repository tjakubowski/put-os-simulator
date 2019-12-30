#include "pch.h"
#include "RAM.h"
#include<fstream>
using namespace std;

int RAM::add_to_RAM(int id, string Filename) {
	fstream file;
	string commands, help, com[128];

	file.open(Filename);
	int length = 0, counter = 0;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, help);
			com[counter] = help;
			counter++;
			for (int i = 0; i <= help.length(); i++)
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
	cout << "all commands together:" << commands << "\n";

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
		cout << "this file is empty" << endl;
		return 3;

	}
	bool find_space = false;
	if (free_space < length || free_space < 2)
	{

	}
	else {
		find_space = true;
	}
	if (find_space == true) {
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
			list<Free_blocks>::iterator i;
			for (i = Free_blocks_list.begin(); i != Free_blocks_list.end(); i++) {
				if (i->size >= length) {
					F_b.begining = i->begining + length;
					break;
				}
			}
			bool finder = false;
			for (auto process : RAM_process_list) {
				if (process.begining >= F_b.begining) {
					F_b.end = process.begining - 1;
					finder = true;
					break;
				}
			}
			if (finder == false) {
				F_b.end = 128;
			}
			F_b.size = F_b.end - F_b.begining;
			if (F_b.size > 0)
				Free_blocks_list.emplace_front(F_b);

			Free_blocks_list.erase(i);
		}//troche nie mam pojecia co robie, ale chyba dziala

		Process process(); //tutaj trzeba przekazac id, wielkosc, komendy i takie tam do listy procesów
	}
}