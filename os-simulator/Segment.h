#pragma once
class Segment
{
public:
	bool is_in_RAM;
	int base;
	int limit;
	Segment(int base, int limit, bool is_in_RAM);
	Segment();
	~Segment();
};

