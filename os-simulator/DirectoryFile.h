#pragma once

#include "Semaphore.h"
#include "Disc.h"

class DirectoryFile
{
public:
	//Nazwa Pliku 
	std::string Name[32];
	//Pierwszy element tablicy FAT 
	int First[32];


};