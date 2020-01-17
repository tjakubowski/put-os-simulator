#pragma once
#include "pch.h"
#include "Semaphore.h"
#include "Disc.h"

class DirectoryFile
{
public:
	std::string Name[32];
	int First[Drive::BlockCount];

	struct File
	{
		Semaphore sem;
		string name;
		int adres;

		File(string name, int adres) :sem(1)
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