#pragma once
#include "pch.h"

class DirectoryFile
{
public:
	std::string Name[Drive::BlockCount];
	int First[Drive::BlockCount];
	//char metadata[32];

};