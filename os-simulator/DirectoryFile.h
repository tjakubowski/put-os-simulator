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
	/*
	struct File
	{
		Semaphore sem;
		std::string name;
		int adres;

		File(std::string name, int adres, int k) 
		{
			this->name = name;
			this->adres = adres;
		}
	
	};
	*/


	//char metadata[32];

};