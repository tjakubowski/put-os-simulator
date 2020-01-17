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

	struct File
	{
		Semaphore sem;
		std::string name;
		int adres;

		File(std::string name, int adres) :sem(1)
		{
			this->name = name;
			this->adres = adres;

		}
		File() :sem(1)
		{

		}
	};


	//char metadata[32];

};