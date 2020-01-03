#include "pch.h"
#include "RAM.h"
#include<fstream>
using namespace std;

int RAM::add_to_RAM(Process* process) {
	fstream file;
	string commands, help, com[128];

	file.open(process->file_name);
	int length = 0, counter = 0;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, help);
			com[counter] = help;
			counter++;		 //string stream
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
		return 1;
	}
	else {

	}

		Process process(); //tutaj trzeba przekazac id, wielkosc, komendy i takie tam do listy procesów
	
}