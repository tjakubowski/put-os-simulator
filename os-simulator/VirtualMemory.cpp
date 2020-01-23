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

	return -1;
}

bool VMSegment::operator<(const VMSegment& s) const
{
	return (base < s.base);
}

bool VirtualMemory::create_program(Process* pcb, std::string file)
{

	std::vector<Segment*> segment_tab = pcb->segment_tab();
	Segment* text_pcbseg = new Segment();
	Segment* data_pcbseg = new Segment();

	size_t sLength;
	size_t text_begin = file.find(".text ");
	size_t data_begin = file.find(".data ");

	bool bool_text = false;
	bool bool_data = false;
	int temp = 0;
	/*if (text_begin != std::string::npos) {
		bool_text = true;
		temp++;
	}
	if (data_begin != std::string::npos) {
		bool_data = true;
		temp++;
	}*/
	if (text_begin < file.size()) {
		bool_text = true;
		temp++;
	}
	if (data_begin < file.size()) {
		bool_data = true;
		temp++;
	}
	//	std::cout << "temp" << temp << " indeks pocatku textu  " << text_begin << " indeks pocatku data " << data_begin << " string size " << file.size() << std::endl;
		//std::cout << std::string::npos << std::endl;
		//std::cout << "text " << bool_text << " data " << bool_data << std::endl;
	if (bool_text && bool_data) {

		int text_limit = data_begin - text_begin - 6;
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

		for (int i = 0; i < text_limit; i++) {
			pagefile[text_base + i] = file[text_begin + 6 + i];
			string_text += file[text_begin + 6 + i];
		}
		text_pcbseg->data = string_text;
		segment_tab.push_back(text_pcbseg);
		//
		int data_limit = 1;
		int data_base = get_base(data_limit);
		std::string string_data = " ";
		VMSegment data_seg(data_base, data_limit);
		pagefile_segment_tab.push_back(data_seg);
		data_pcbseg->baseVM = data_base;
		data_pcbseg->limit = data_limit;
		data_pcbseg->is_in_RAM = false;
		for (int i = 0; i < string_data.size(); i++) {
			pagefile[data_base] = ' ';
		}
		data_pcbseg->data = string_data;
		segment_tab.push_back(data_pcbseg);
		//segment_tab.emplace_back();
	}
	else if (!bool_text && bool_data) {
		//
		throw std::exception("THERE IS NO .TEXT SEGMENT");
		int text_limit = 1;
		int text_base = get_base(text_limit);
		std::string string_text = " ";
		VMSegment text_seg(text_base, text_limit);
		pagefile_segment_tab.push_back(text_seg);
		text_pcbseg->baseVM = text_base;
		text_pcbseg->limit = text_limit;
		text_pcbseg->is_in_RAM = false;
		for (int i = 0; i < string_text.size(); i++) {
			pagefile[text_base] = ' ';
		}
		text_pcbseg->data = string_text;
		segment_tab.push_back(text_pcbseg);
		//

		int data_limit = file.size() - data_begin - 6;
		int data_base = get_base(data_limit);
		VMSegment data_seg(data_base, data_limit);
		pagefile_segment_tab.push_back(data_seg);
		data_pcbseg->baseVM = data_base;
		data_pcbseg->limit = data_limit;
		data_pcbseg->is_in_RAM = false;
		std::string string_data;


		for (int i = 0; i < data_limit; i++) {
			pagefile[data_base + i] = file[data_begin + 6 + i];
			string_data += file[data_begin + 6 + i];
		}

		data_pcbseg->data = string_data;
		segment_tab.push_back(data_pcbseg);

	}
	else if (!bool_data && !bool_text) {
		throw std::exception("NIE MA .data BADZ .text");
		return false;
	}

	pcb->set_segment_tab(segment_tab);
	return true;
}

bool VirtualMemory::delete_program(Process* pcb) {
	auto segment_tab = pcb->segment_tab();
	int size = segment_tab.size();
	for (int i = 0; i < size; i++) {
		VMSegment segment = pagefile_segment_tab[i];
		for (int j = 0; j < pagefile_segment_tab.size(); j++) {
			if (segment.base == segment_tab[i]->baseVM && segment.limit == segment_tab[i]->limit) {
				pagefile_segment_tab.erase(pagefile_segment_tab.begin() + j);
				segment_tab.erase(segment_tab.begin() + i);
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

	TablePrinter tp2;
	tp2.AddColumn("INDEX", 12);
	tp2.AddColumn("PAMIEC WIRTUALNA", 70);
	tp2.PrintHeader();
	int k = 0;
	int index = 0;
	for (int i = 0; i < kvirtualmemory_size; i += 64)
	{
		std::string id;
		id = std::to_string(index) + "-" + std::to_string(index + 64);
		std::string temp;
		for (int j = 0; j < 64; j++) {
			temp += pagefile[i + j];
		}
		tp2 << id;
		tp2 << temp;
		index += 64;

	}
	tp2.PrintFooter();
}

void VirtualMemory::display_pagefile_segment_tab()
{
	std::cout << std::endl;
	for (int i = 0; i < pagefile_segment_tab.size(); i++)
	{
		std::cout << "POCZATEK: " << pagefile_segment_tab[i].base << " LIMIT: " << pagefile_segment_tab[i].limit << " >" << std::endl;
	}
}

void VirtualMemory::display_segment_tab(Process* pcb)
{
	std::cout << std::endl;
	std::vector<Segment*> segment_tab = pcb->segment_tab();
	TablePrinter tp;
	tp.AddColumn("POCZATEK", 5);
	tp.AddColumn("LIMIT", 5);
	tp.AddColumn("IS IN RAM", 5);
	tp.AddColumn("POCZATEK W RAM", 5);
	tp.PrintHeader();
	for (int i = 0; i < segment_tab.size(); i++)
	{
		if (segment_tab[i] != nullptr) {
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
	}

	tp.PrintFooter();
}







