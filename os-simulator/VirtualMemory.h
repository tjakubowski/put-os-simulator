#pragma once
#include<iostream>
#include<array>
#include<vector>
#include<string>
#include<fstream>
#include <vector>
#include"PCB.h"

extern class PCB;

class VirtualMemory
{
public:
	static const int kvirtualmemory_size = 2048;
	std::array<char, kvirtualmemory_size> pagefile;
	std::vector<std::array<int, 2>> pagefile_segment_tab; // base and limit in array

	VirtualMemory();
	~VirtualMemory();

	int get_base(const int& limit); //znajduje adres poczatkowy adresowania 
	int free_space_size();

	std::vector<char> get_segment_to_RAM(const int& base, PCB *pcb);

	void load_program_from_file(PCB* pcb);
	void load_program_from_char_vector(const std::vector<char>& program, PCB*pcb);

	void remove_program_from_virtualmemory(const int &base);
	void remove_segment_from_segment_tab(PCB *pcb, const int &base);
	void remove_process(PCB*pcb);

	void display_pagefile();
	void display_pagefile_segment_tab();
	void display_segment_tab(PCB*pcb);
};





