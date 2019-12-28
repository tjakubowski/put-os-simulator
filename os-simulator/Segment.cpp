#include "pch.h"
#include "Segment.h"


Segment::Segment(int base, int limit, bool is_in_RAM)
{
	this->base = base;
	this->limit = limit;
	this->is_in_RAM = is_in_RAM;
}

Segment::Segment()
{
}


Segment::~Segment()
{
}
