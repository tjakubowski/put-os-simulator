#pragma once
#include<string>
class Segment
{
public:
	std::string data;
	bool is_in_RAM;
	int baseVM, baseRAM;
	int limit;//rozmiar 
	//Segment(int base, int limit, bool is_in_RAM);
	Segment();
	~Segment();
};

