#pragma once
#include<iostream>
#include<array>
#include<vector>
#include<string>
#include<fstream>
#include"Singleton.h"
#include <vector>
#include"Process.h"

class VMSegment {
public:
	
	int base, limit;
	VMSegment(int base, int limit) {
		this->base = base;
		this->limit = limit;
	}
	VMSegment() {

	}
	bool operator<(const VMSegment& s) const;
};

class VirtualMemory : public Singleton <VirtualMemory>{
	friend class Singleton<VirtualMemory>;
public:
	static const int kvirtualmemory_size = 4096;
	std::array<char, kvirtualmemory_size> pagefile;
	std::vector<VMSegment> pagefile_segment_tab;

	int get_base(const int& limit); //znajduje adres poczatkowy adresowania (wolne miejsce) 
	VirtualMemory();
	~VirtualMemory();
	bool create_program(Process* pcb, std::string file);
	bool load_to_virtualmemory(Process* pcb, const std::string data);
	bool load_program_to_ram(Process* pcb);
	bool delete_program(Process* pcb);//usuwa program z ram i vm
	std::string get_segment(Process* pcb, const int segment);
	void display_pagefile();
	void display_pagefile_segment_tab();
	void display_segment_tab(Process* pcb);
};
