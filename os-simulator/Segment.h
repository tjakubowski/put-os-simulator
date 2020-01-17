#pragma once
class Segment
{
public:
	bool is_in_RAM;
	int baseVM, baseRAM;
	int limit;
	Segment(int base, int limit, bool is_in_RAM);
	Segment();
	~Segment();
};

