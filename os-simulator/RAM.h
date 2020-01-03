#pragma once
#include<iostream>
#include "Process.h"
#include<conio.h>
#include<string>
#include<list>
#include<algorithm>
#include<fstream>

using namespace std;

struct Free_blocks {
	int size;
	int begining;
	int end = size + begining;
};

class RAM { //single tone do sprawdzenia
	public: //private potem
		int memory_capacity = 128;
		int free_space = 128;
		list<Process*> RAM_process_list;
		list<Free_blocks> Free_blocks_list;
		int command_length;

		RAM(){
			Free_blocks F_b;
			F_b.begining = 1;
			F_b.end = 128;
			F_b.size = F_b.end - F_b.begining;
			Free_blocks_list.push_back(F_b);
		}
private:
	int last = 0;
public:
		int add_to_RAM(Process* process);  //dodaæ wskaŸnik na proces jako argument albo ciagnac po id pobraæ kod programu z modu³u FAT
		void delete_from_RAM(Process* process);  //dodaæ wskaŸnik na proces jako argument
		string show_RAM(int id, int counter); //wyswietlenie zawartosci ram
		char char_RAM(int id, int place);
		
		void wait_for_RAM(); //nwm czy to potrzebne bedzie w ogole
		void merge_Fb(); //to chyba mozna olac ale poki co jest
		void fragment_Fb(); //jw
};


