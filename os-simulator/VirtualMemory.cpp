#include "pch.h"
#include "VirtualMemory.h"
#include "Segment.h"
#include"Process.h"
#include "FileSystem.h"

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
		for (int j = 0; j < pagefile_segment_tab[i].limit; j++)
		{
			holes[pagefile_segment_tab[i].base + j] = false;
		}
	}

	int occurrences = 0;
	for (int i = 0; i < holes.size() - 1; i++)
	{
		if (holes[i] && holes[i + 1])
			occurrences++;
		else
			occurrences = 0;

		if (occurrences == limit)
			return i - occurrences + 1;
	}

	return -1; //zwraca -1 gdy nie ma wolnego miejsca 

	/*if (base == -1) //gdy nie bedzie miejsca daje wyjatek ale my nie zakladamy takiej sytuacji
	{
		std::string exception = "NO FREE SPACE SEGMENT IS TOO BIG";
		throw  exception;
	}*/
}

bool VMSegment::operator<(const VMSegment& s) const
{
	return (base < s.base);
}

bool VirtualMemory::create_program(Process* pcb, std::string file)
{
	//dodaj zaladowanie stringa z FileM
	std::vector<Segment*> segment_tab = pcb->segment_tab();
	Segment* text_pcbseg = new Segment();
	Segment* data_pcbseg = new Segment();
	//int segment_tab_size = 0;
	size_t sLength;
	size_t text_begin = file.find(".text ");
	size_t data_begin = file.find(".data ");
	//sprawdzenie czy segmenty istnieja
	bool bool_text = false;
	bool bool_data = false;
	if (text_begin != std::string::npos) {
		bool_text = true;
	}
	if (data_begin != std::string::npos) {
		bool_data = true;
	}
	if (bool_text && bool_data) {

		int text_limit = data_begin - text_begin - 6;//moze jeszcze -1;	
		int text_base = get_base(text_limit);
		VMSegment text_seg(text_base, text_limit);
		pagefile_segment_tab.push_back(text_seg);
		text_pcbseg->baseVM = text_base;
		text_pcbseg->limit = text_limit;
		text_pcbseg->is_in_RAM = false;


		int data_limit = file.size() - data_begin - 6;
		int data_base = get_base(data_limit);
		VMSegment data_seg(data_base, data_limit);
		pagefile_segment_tab.push_back(data_seg);
		data_pcbseg->baseVM = data_base;
		data_pcbseg->limit = data_limit;
		data_pcbseg->is_in_RAM = false;

		std::string string_data, string_text;

		//dodaj do ramu wtedy mozesz tez isinram zmienic
		for (int i = 0; i < text_limit; i++) {
			pagefile[text_base + i] = file[text_begin + 6 + i];
			string_text += file[text_begin + 6 + i];;
		}
		for (int i = 0; i < data_limit; i++) {
			pagefile[data_base + i] = file[data_begin + 6 + i];
			string_data += file[data_begin + 6 + i];
		}
		text_pcbseg->data = string_text;
		data_pcbseg->data = string_data;

		segment_tab.push_back(text_pcbseg);
		segment_tab.push_back(data_pcbseg);

	}
	else if (bool_text && !bool_data) {
		int text_limit = file.size() - text_begin - 6;//moze jeszcze -1;
		int text_base = get_base(text_limit);
		VMSegment text_seg(text_base, text_limit);
		pagefile_segment_tab.push_back(text_seg);
		text_pcbseg->baseVM = text_base;
		text_pcbseg->limit = text_limit;
		text_pcbseg->is_in_RAM = false;

		std::string string_text;
		//dodaj do ramu
		for (int i = 0; i < text_limit; i++) {
			pagefile[text_base + i] = file[text_begin + 6 + i];
			string_text += file[text_begin + 6 + i];
		}
		text_pcbseg->data = string_text;
		segment_tab.push_back(text_pcbseg);

	}
	else if (!bool_text && bool_data) {
		int data_limit = file.size() - data_begin - 6;
		int data_base = get_base(data_limit);
		VMSegment data_seg(data_base, data_limit);
		pagefile_segment_tab.push_back(data_seg);
		data_pcbseg->baseVM = data_base;
		data_pcbseg->limit = data_limit;
		data_pcbseg->is_in_RAM = false;
		std::string string_data;

		//dodaj do ramu
		for (int i = 0; i < data_limit; i++) {
			pagefile[data_base + i] = file[data_begin + 6 + i];
			string_data += file[data_begin + 6 + i];
		}
		text_pcbseg->data = "";
		segment_tab.push_back(text_pcbseg);
		data_pcbseg->data = string_data;
		segment_tab.push_back(data_pcbseg);
	}
	else if (!bool_data && !bool_text) {
		throw std::exception("THERE IS NOT .TEXT AND .DATA SEGMENT");
		return false;
	}

	pcb->set_segment_tab(segment_tab);
	return true;
}

bool VirtualMemory::load_program_to_ram(Process* pcb) {

	auto segment_tab = pcb->segment_tab();
	for (int i = 0; i < segment_tab.size(); i++) {
		if (segment_tab[i]->is_in_RAM == 0) {
			std::string result;
			for (int j = segment_tab[i]->baseVM; j < segment_tab[i]->baseVM + segment_tab[i]->limit; j++) {
				result += pagefile.at(j);
			}
			//if (za³aduj do ramu false retun false); pramaters (Process *pcb, string data, int segment)
			//{return false;
			//}
		}
	}
	std::sort(pagefile_segment_tab.begin(), pagefile_segment_tab.end());
	return true;
}

//usuwa program z VM i RAMu
bool VirtualMemory::delete_program(Process* pcb) {
	//uruchamia funkcje z ramu do usuwania programu daje jej Process*pcb jako argument
	auto segment_tab = pcb->segment_tab();
	int size = segment_tab.size();
	for (int i = 0; i < size; i++) { //for every segment (.text, .data)
		VMSegment segment = pagefile_segment_tab[i];
		for (int j = 0; j < pagefile_segment_tab.size(); j++) {
			if (segment.base == segment_tab[i]->baseVM && segment.limit == segment_tab[i]->limit) {
				for (int k = segment.base; k < segment.base + segment.limit; k++) {
					pagefile[k] = ' ';
				}
				pagefile_segment_tab.erase(pagefile_segment_tab.begin() + j);
				segment_tab.erase(segment_tab.begin() + i);
				i--;
				size--;
				break;
			}
		}
	}
	pcb->set_segment_tab(segment_tab);
	std::sort(pagefile_segment_tab.begin(), pagefile_segment_tab.end());
	return true;
}

std::string VirtualMemory::get_segment(Process* pcb, const int segment) {
	std::vector<Segment*> segment_tab = pcb->segment_tab();
	std::string result;
	for (int i = segment_tab[segment]->baseVM; i < segment_tab[segment]->baseVM + segment_tab[segment]->limit; i++) {
		result += pagefile.at(i);
	}
	return result;
}

bool VirtualMemory::load_to_virtualmemory(Process* pcb, const std::string data)
{
	std::vector<Segment*> segment_tab = pcb->segment_tab();
	for (int i = 0; i < segment_tab[1]->limit; i++) {
		pagefile.at(segment_tab[1]->baseVM + i) = data[i];
		segment_tab[i]->data = data[i];
	}
	pcb->set_segment_tab(segment_tab);
	return true;
}

void VirtualMemory::display_pagefile()
{
	std::sort(pagefile_segment_tab.begin(), pagefile_segment_tab.end());
	for (int i = 0; i < pagefile_segment_tab[pagefile_segment_tab.size() - 1].base + pagefile_segment_tab[pagefile_segment_tab.size() - 1].limit; i++) {
		std::cout <<i<<" : "<< pagefile[i]<<" ";
		if (i % 20 == 0 && i != 0)std::cout << std::endl;
	}
}

void VirtualMemory::display_pagefile_segment_tab()
{
	std::cout << std::endl;
	for (int i = 0; i < pagefile_segment_tab.size(); i++)
	{
		std::cout << "<base: " << pagefile_segment_tab[i].base << " limit: " << pagefile_segment_tab[i].limit << " >" << std::endl;
	}
}

void VirtualMemory::display_segment_tab(Process* pcb)
{
	std::cout << std::endl;
	std::vector<Segment*> segment_tab = pcb->segment_tab();
	TablePrinter tp;
	tp.AddColumn("BASE", 5);
	tp.AddColumn("LIMIT", 5);
	tp.AddColumn("IS IN RAM", 5);
	tp.AddColumn("BASE IN RAM", 5);
	tp.PrintHeader();
		for (int i = 0; i < segment_tab.size(); i++)
		{
			tp << segment_tab[i]->baseVM << segment_tab[i]->limit;
			if (segment_tab[i]->is_in_RAM)
			{
				tp << "true" << segment_tab[i]->baseRAM;
			}
			else
			{
				tp << "false" << "----";
			}
		}
	
	tp.PrintFooter();
}

/*
bool VirtualMemory::create_program(Process* pcb, std::string data)
{
	std::vector<Segment*> segment_tab = pcb->segment_tab();
	std::string toRam;
	int segment_tab_size = 0;
	size_t sLength;
	size_t text_begin = data.find(".text");
	size_t data_begin = data.find(".data");
	//sprawdzenie czy segmenty istnieja
	if (text_begin != std::string::npos) {
		segment_tab_size++;
	}
	if (data_begin != std::string::npos) {
		segment_tab_size++;
	}

	int k = 0;
	for (int i = 0; i < segment_tab_size; i++) {
		size_t freeSpace = size_t(get_base(data.length()));
		if (freeSpace == -1) {
			return false;
		}
		int maxPos = 0, index = 0;
		k += 6;
		std::string snumber;
		int number = 0;
		int correction = 6; //6 is length of".text " or ".data "
		if (i == 0 && segment_tab_size == 2) {
			sLength = data_begin - 1;
		}
		else {
			sLength = data.length();
		}
		int pos = 0;
		while (k < sLength) {
			if (i == 0) {
				if (data.at(k - 1) == ' ' && isdigit(data.at(k))) {
					int numLength = -1;//20-22
					for (int i = 0; i < 3; i++) {
						numLength++; //count how many digits were found to correct index in pagefile later
						snumber += data.at(k + i);
						if (data.length() == (k + i + 1) || data.at(k + i + 1) == ' ') { //if next byte is not digit, it means we found whole number, convert it to int
							number = std::stoi(snumber);
							snumber.clear(); //clear string as preparation for next number
							pagefile.at(freeSpace + pos) = number; //fill pagefile byte with converted number
							toRam += number;
							k += numLength;
							correction += numLength;
							pos++;
							break;

						}
					}
				}
				else { //if byte is not a number, just copy it to pagefile (using correction counted earlier)
					pagefile.at(freeSpace + pos) = data.at(k);
					toRam += data.at(k);
					pos++;
				}
			}
			else {
				if (data.at(k - 1) == '[' && isdigit(data.at(k))) {
					int numLength = -1;
					for (int i = 0; i < 3; i++) {
						numLength++; //count how many digits were found to correct index in pagefile later
						snumber += data.at(k + i);
						if (data.length() == (k + i + 1) || data.at(k + i + 1) == ']') { //if next byte is not digit, it means we found whole number, convert it to int
							index = std::stoi(snumber);
							snumber.clear(); //clear string as preparation for next number
							k += numLength;
							correction += numLength;
							if (index > maxPos) maxPos = index;
							break;
						}
					}
				}
				else if (data.at(k - 1) == ' ' && isdigit(data.at(k))) {
					int numLength = -1;//20-22
					for (int i = 0; i < 3; i++) {
						numLength++; //count how many digits were found to correct index in pagefile later
						snumber += data.at(k + i);
						if (data.length() == (k + i + 1) || data.at(k + i + 1) == ' ') { //if next byte is not digit, it means we found whole number, convert it to int
							number = std::stoi(snumber);
							snumber.clear(); //clear string as preparation for next number
							pagefile.at(freeSpace + index) = number; //fill pagefile byte with converted number
							for (int j = 0; j <= index; j++) {
								if (toRam.size() == j) {
									if (j == index)
										toRam += number;
									else toRam += '\0';
								}
								else if (j == index) {
									toRam.at(index) = number;
								}
							}
							k += numLength;
							correction += numLength;
							pos++;
							break;
						}
					}
				}
				else {
					pagefile.at(freeSpace + pos) = 0;
					toRam += '\0';
					if (pos > maxPos) maxPos = pos;
				}
			}
			k++;
		}
		if (i == 1 && maxPos < toRam.size()) toRam.pop_back();
		VMSegment segment;
		segment.base = freeSpace;
		if (i == 0) { //.text segment
			segment.limit = pos;
		}
		else { //.data segment
			segment.limit = maxPos + 1;
		}
		pagefile_segment_tab.push_back(segment);

		Segment* segment_PCB = new Segment();
		segment_PCB->baseVM = segment.base;
		segment_PCB->limit = segment.limit;
		segment_PCB->is_in_RAM = false;
		segment_tab->push_back(segment_PCB);


		// dodaj if ktory wpisuje toRama do ramu jak bedzie false to return false
		// 1 brak miejsca 2 plik nie moze byc znaleziony 3 pusty plik

	}
	std::sort(pagefile_segment_tab.begin(), pagefile_segment_tab.end());
	return true;
}*/






