﻿#include "pch.h"

#include "FileM.h"

#include <iostream>


//Zeruje Tablice FAT i DIR
FileM::FileM()
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		FileTable.Next[i] = 0;
		FileTable.Busy[i] = false;
		FreeBlockCount = dysk.BlockCount;
		DIR.Name[i] ="";
	}
}


std::string FileM::OpenFile(Process*pcb)
{
	std::string name = pcb->file_name();
	std::string ProcessName = pcb->name();
	if (InvestigateFile(name) == false)
	{
		throw std::exception("tresc");
		
	}
	
	
	//przesyla PLIK stringiem.
	return SendFile(name);

}

void FileM::CloseFile(std::string ProcessName)
{
	//Signal(ProcessName);
	
}

//Szuka pierwszego wolnego bloku w FAT
int FileM::FindFreeBlock()
{
	for (int i = 0; i < dysk.BlockCount; i++)
		if (!FileTable.Busy[i] == false) return i+1;
	return -1;
}
//Szuka pierwszego wolnego miejsca w katalogu
int  FileM::FindFreeDirectory()
{
	for (int i = 0; i < dysk.BlockCount; i++)
		if (DIR.Name[i] == "") return i+1;

	return -1;
}

//Tworzy pusty plik
void FileM::CreateFile(const std::string& name)
{

	bool Check = InvestigateFile(name);
	if (Check == true)
	{
		throw std::exception("tresc");

	}

	int Adress = FindFreeBlock();
	if (Adress == -1)
	{
		throw std::exception("drive");
		
	}

	int Directory = FindFreeDirectory();
	if (Directory == -1)
	{
			
			throw std::exception("FFD");
	}

	DIR.Name[Directory-1] = name;
	DIR.First[Directory-1] = Adress;
	FileTable.Busy[Adress-1] = true;
	FileTable.Next[Adress-1] = -1;
	FreeBlockCount--;
}
	
//Szuka konkretnego pliku w katalogu
int FileM::FindFile(const std::string& name)
{
	int Found;
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] == name)
		{
			Found = DIR.First[i];
			return Found+1;
		}
	}
	return -1;
}

void FileM::DeleteFile(const std::string& name)
{
	int FoundFile = FindFile(name)-1;
	if (FoundFile == -1)
	{
		throw std::exception("tresc");
		
	}
	
	//Usuwanie alternatywnych nazw pliku
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.First[i] == FoundFile)
		{
			DIR.First[i] = 0;
			DIR.Name[i] = "";
		}
	}
	//Szuka wszystkich części pliku i usuwa je od pierwszego do ostatniego
	int help = FoundFile;
	while (help != 0)
	{
		if (FileTable.Next[help] == -1)
		{
			FileTable.Busy[help] = false;
			FileTable.Next[help] = 0;
			help = 0;
			FreeBlockCount++;
		}
		else
		{
			help = FileTable.Next[help];
			FileTable.Next[help] = 0;
			FileTable.Busy[help] = false;
			FreeBlockCount++;
		}
	}

}

//Dodaje dodatkowa nazwe dla istniejacego pliku 
void FileM::AddNewName(const std::string& name, const std::string& name2)
{
	int x = FindFile(name)-1;
	if (x == -1)
	{
		throw std::exception("tresc");
	}

	int SecondAdress = FindFreeDirectory()-1;
	if (SecondAdress == -1)
	{
		throw std::exception("tresc");
	}
	DIR.Name[SecondAdress] = name2;
	DIR.First[SecondAdress] = x;

}

void FileM::ReplaceNewName(const std::string& name, const std::string& name2)
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] == name)
			DIR.Name[i] = name2;
		if (i == dysk.BlockCount - 1 && DIR.Name[i] != name2)
		{
			throw std::exception("tresc");
		}
	}
}

void FileM::WriteFile(const std::string& name, std::string tresc)
{
	int HowLong = tresc.size();
	int help1 = HowLong;
	int HowMany = 0;
	while (help1 > 32)
	{
		HowMany++;
		help1 = help1 - 32;
	}

	int Previous = FindFile(name)-1;
	if (HowMany > 0)
	{
	//Kiedy uzwyamy wiecej niz jednego bloku pamieci
		for (int i = 0; i < HowMany; i++)
		{
			int  Free = FindFreeBlock()-1;
			if (Free == -1)
			{
				throw std::exception("drive");
			
			}

			FileTable.Next[Previous] = Free;
			FileTable.Busy[Free] = true;
			FileTable.Next[Free] = -1;
			Previous = Free;
			FreeBlockCount--;

			for (int j = 0; j < dysk.BlockSize; j++)
			{
				dysk.A[dysk.BlockSize * Free + j] = tresc[j];
				HowLong--;
				if (HowLong == 0)
					break;
			}


		}
	}
	//Jezeli uzywamy tylko jednego bloku pamieci
	else
	{
		for (int j = 0; j < dysk.BlockSize; j++)
		{
			dysk.A[dysk.BlockSize * Previous + j] = tresc[j];
			FreeBlockCount--;
		}

	}

}
void FileM::PrintFile(const std::string& name)
{
	int x = FindFile(name)-1;
	if (x == -1)
	{
		throw std::exception("tresc");

	}
	for (int i = 0; i < dysk.BlockSize; i++)
	{
		std::cout<< dysk.A[x * dysk.BlockSize +i];

	}
	int temp = 0;
	while (temp != -1)
	{
		for (int i = 0; i < dysk.BlockSize; i++)
		{
			std::cout<< dysk.A[x * 32 + i];


		}
		temp = FileTable.Next[temp];
	}
	std::cout<<("\n");
}

void FileM::ListDirectory() const
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] != "")
		std::cout<<"Nazwa: " << DIR.Name[i]<<"  Pierwszy Blok Pamieci:"<< DIR.First[i] << "\n";
	}
}

void FileM::ListFAT() const
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (FileTable.Busy[i] == true)
			std::cout<<("%d. Busy: True, Nastepny Blok Pamieci: %d\n", i+1, FileTable.Next[i]);
		else
			std::cout<<("%d. Busy: False, Nastepny Blok Pamieci: -\n", i+1);
	}

}

bool FileM::InvestigateFile(const std::string& name)
{
	int x = FindFile(name);
	if (x == -1)
	{
		throw std::exception("tresc");

	}
	return true;
}

void FileM::Stats() const
{
	std::string Wyswietl = "";
	Wyswietl = Wyswietl + "Miejsce (wolne/max): " + std::to_string(FreeBlockCount) + "/" + std::to_string(dysk.BlockCount) + '\n';
	std::cout << Wyswietl;
}

std::string FileM::SendFile(const std::string& name)
{
	std::string data = "";

	int Next = FindFile(name);
	if (Next == -1)
	{
		throw std::exception("tresc");
	}

	for (int i = 0; i < dysk.BlockSize; i++)
	{
		data = data + dysk.A[dysk.BlockSize * Next + i];

	}
	int temp = 0;
	while (temp != -1)
	{
		for (int i = 0; i < dysk.BlockSize; i++)
		{
			data = data + dysk.A[dysk.BlockSize* Next + i];


		}
		temp = FileTable.Next[temp];
	} 
	return data;
}
//Na potrzeby tego zakladam ze plik zostal otwarty przed wywolaniem funkcji!
void FileM::ExtractFile(const std::string& name, std::fstream tekst)
{
	CreateFile(name);
	string Content;
	string ToSend = "";
	int Count = 0;
	while (!getline(tekst, Content))
	{
		ToSend = ToSend + Content;

	}
	WriteFile(name, ToSend);

}





