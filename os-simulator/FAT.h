#pragma once

#include "Disc.h"

class FAT
{
public:
	int Next[Drive::BlockCount];
	bool Busy[Drive::BlockCount];


};