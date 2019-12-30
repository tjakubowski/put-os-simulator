#include "pch.h"
#include "VirtualMemory.h"
#include "Segment.h"
#include"Process.h"

extern class  Process;

VirtualMemory::VirtualMemory()
{
	for (int i = 0; i < kvirtualmemory_size; i++)
	{
		pagefile[i] = ' ';
	}
}

VirtualMemory::~VirtualMemory()
{

}

int VirtualMemory::get_base(const int& limit)
{
	std::array<bool, kvirtualmemory_size> holes;

	for (int i = 0; i < holes.size(); i++)
	{
		holes[i] = true;
	}

	for (int i = 0; i < pagefile_segment_tab.size(); i++)//false tam gdzie sa dane 
	{
		for (int j = 0; j < pagefile_segment_tab[i][1]; j++)
		{
			holes[pagefile_segment_tab[i][0] + j] = false;
		}
	}

	int base = -1;

	for (int i = 0; i < kvirtualmemory_size - 1; i++)
	{
		int temp = 1;//0
		if (holes[i] == true && holes[i + 1] == true) {
			do
			{
				temp++;
				i++;
				if (temp == limit)
				{
					base = i - temp + 1;//i-temp
					std::cout << base << std::endl;
					return base;
				}
			} while (holes[i] == true && holes[i + 1] == true);

		}
	}

	if (base == -1)
	{
		std::string exception = "NO FREE SPACE SEGMENT IS TOO BIG";
		throw  exception;
	}
}

void VirtualMemory::load_program_from_file(Process* pcb)
{
	std::vector<char>  program;
	std::string file_name = pcb->file_name();
	std::fstream stream(file_name, std::ios::in);
	if (stream.good() == true)
	{
		while (!stream.eof())
		{
			std::string temp;
			std::getline(stream, temp);
			for (int i = 0; i < temp.size(); i++)
			{
				program.push_back(temp[i]);
			}
		}
	}

	load_program_from_char_vector(program, pcb);
}

void VirtualMemory::load_program_from_char_vector(const std::vector<char> &program, Process*pcb)
{
	std::vector<Segment> segment_tab = pcb->segment_tab();
	bool is_arleady_in_virtualmemory = false;
	for (int i = 0; i < segment_tab.size(); i++)
	{
		if (program.size() == segment_tab[i].limit)
		{
			for (int j = 0; j < pagefile_segment_tab.size(); j++)
			{
				if (segment_tab[i].base == pagefile_segment_tab[j][0] && segment_tab[i].limit == pagefile_segment_tab[j][1])
				{
					is_arleady_in_virtualmemory = true;
					segment_tab[i].is_in_RAM = false;
					pcb->set_segment_tab(segment_tab);
					//std::cout << "zmiana na false\n\n";//do usunieca potem
				}
			}
		}
	}

	if (is_arleady_in_virtualmemory == false)
	{
		//std::cout << "ROMIAR PROGRAMU TO " << program.size() << std::endl; //do usuniecia potem
		std::vector<Segment> segment_tab = pcb->segment_tab();
		int base = get_base(program.size());
		for (int i = 0; i < program.size(); i++)
		{
			pagefile[base + i] = program[i];
		}

		std::array<int, 2> segment{ base, program.size() };
		pagefile_segment_tab.push_back(segment);

		Segment temp(base, program.size(), false);
		segment_tab.push_back(temp);
		pcb->set_segment_tab(segment_tab);
	}


}

void VirtualMemory::remove_program_from_virtualmemory(const int &base)
{
	for (int i = 0; i < pagefile_segment_tab.size(); i++)
	{
		if (pagefile_segment_tab[i][0] == base)
		{
			for (int index = base; index < base + pagefile_segment_tab[i][1]; index++)
			{
				pagefile[index] = ' ';
			}
			pagefile_segment_tab.erase(pagefile_segment_tab.begin() + i);//////
			break;
		}
	}
}

void VirtualMemory::remove_segment_from_segment_tab(Process* pcb, const int& base)
{
	std::vector<Segment> segment_tab = pcb->segment_tab();
	for (int i = 0; i < segment_tab.size(); i++)
	{
		if (segment_tab[i].base == base)
		{
			segment_tab.erase(segment_tab.begin() + i);
		}
	}
	pcb->set_segment_tab(segment_tab);
}

void VirtualMemory::remove_process(Process*pcb)
{
	std::vector<Segment> segment_tab = pcb->segment_tab();
	for (int i = 0; i < segment_tab.size(); i++)
	{
		remove_program_from_virtualmemory(segment_tab[i].base);
	}
	segment_tab.clear();
	pcb->set_segment_tab(segment_tab);
}

std::vector<char> VirtualMemory::get_segment_to_RAM(const int& base, Process *pcb) //tu dodaj dla pagefileSemgnt to z bool
{
	std::vector<Segment> segment_tab = pcb->segment_tab();
	int limit = -1;
	for (int i = 0; i < pagefile_segment_tab.size(); i++)
	{
		if (pagefile_segment_tab[i][0] == base) {
			limit = pagefile_segment_tab[i][1];
			for (int j = 0; j < segment_tab.size(); j++)
			{
				if (segment_tab[j].base == base)
				{
					std::vector<char> result;
					segment_tab[j].is_in_RAM = true;
					for (int index = 0; index < limit; index++) {
						result.push_back(pagefile[base + index]);
					}
					//remove_program_from_virtualmemory(base);
					/*
					 tutaj nie wiem czy wyjebac zawartosc segmentu z pagefila czy zostawic
					 */
					pcb->set_segment_tab(segment_tab);
					return result;
				}
			}
		}
	}
	if (limit == -1) {
		std::string exception = "THERE IS NO SEGMENT WITH THAT BASE";
		throw exception;
	}
}

void VirtualMemory::display_pagefile()
{
	for (auto a : pagefile) std::cout << a;
}

void VirtualMemory::display_pagefile_segment_tab()
{
	for (int i = 0; i < pagefile_segment_tab.size(); i++)
	{
		std::cout << "<base: " << pagefile_segment_tab[i][0] << " limit: " << pagefile_segment_tab[i][1] << " >" << std::endl;
	}
}

void VirtualMemory::display_segment_tab(Process* pcb)
{
	std::vector<Segment> segment_tab = pcb->segment_tab();
	for (int i = 0; i < segment_tab.size(); i++)
	{
		std::cout << "<base: " << segment_tab[i].base << " limit: " << segment_tab[i].limit << " is in RAM: ";
		if (segment_tab[i].is_in_RAM)
		{
			std::cout << "true>";
		}
		else
		{
			std::cout << "false>";
		}
		std::cout << std::endl;
	}
}

int VirtualMemory::free_space_size() //funkcja nigdy nie uzywana ale byla na mojej prezentacji to ja zostawi³em 
{
	int size = kvirtualmemory_size;
	for (int i = 0; i < pagefile_segment_tab.size(); i++)
	{
		size -= pagefile_segment_tab[i][1];
	}
	return size;
}
