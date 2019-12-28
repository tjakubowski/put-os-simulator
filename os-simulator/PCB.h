#pragma once
#include<vector>
#include"Segment.h"
class PCB
{
public:
	PCB();
	~PCB();
	std::vector<Segment> segment_tab;
	std::string file_name;

};

