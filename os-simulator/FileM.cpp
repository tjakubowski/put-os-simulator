#include "pch.h"

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
		DIR.Name[i] = "";
		DIR.First[i] = 0;
		

	}
	CreateSemaphors();
}


std::string FileM::OpenFile(Process* pcb)
{
	std::string name = pcb->file_name();
	std::string ProcessName = pcb->name();
	int FoundFile = FindFile(name) - 1;
	if (FoundFile == -1)
	{
		throw std::exception("tresc");

	}
	//Semafor[name].Wait(name);
	return SendFile(name);

}

void FileM::CloseFile(std::string ProcessName)
{
	
	//Semafor.singal();
	
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
	DIR.Name[Directory - 1] = name;
	DIR.First[Directory - 1] = Adress;
	FileTable.Busy[Adress - 1] = true;
	FileTable.Next[Adress - 1] = -1;
	FreeBlockCount--;


	//Semafor[Adress].Metoda(name, 1); 
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
			return Found + 1;
		}
	}
	return 0;
}

void FileM::DeleteFileContent(const std::string& name)
{
	int Previous = FindFile(name) - 1;
	int Original = Previous;
	if (Previous == -1)
	{
		throw std::exception("tresc");
	}
	for (int j = 0; j < dysk.BlockSize; j++)
	{
		dysk.A[dysk.BlockSize * Previous + j] = 0;
	}
	int Check = FileTable.Next[Previous];
	int Next;
	if (Check != -1)
	{
		while (Previous != -1)
		{
			Next = Previous;
			for (int j = 0; j < dysk.BlockSize; j++)
			{
				dysk.A[dysk.BlockSize * Next + j] = 0;
			}
			Previous = FileTable.Next[Next];
			FileTable.Next[Next] = 0;
			FileTable.Busy[Next] = false;
		}
	}
	FileTable.Next[Original] = -1;
	FileTable.Busy[Original] = true;
}

//Dodaje dodatkowa nazwe dla istniejacego pliku 
void FileM::AddNewName(const std::string& name, const std::string& name2)
{
	int x = FindFile(name) - 1;
	if (x == -1)
	{
		throw std::exception("tresc");
	}

	int SecondAdress = FindFreeDirectory() - 1;
	if (SecondAdress == -1)
	{
		throw std::exception("tresc");
	}
	DIR.Name[SecondAdress] = name2;
	DIR.First[SecondAdress] = x;
}

void FileM::ReplaceNewName(const std::string& name, const std::string& newname)
{
	int x = FindFile(name) - 1;
	if (x == -1)
	{
		throw std::exception("tresc");
	}
	if (DIR.Name[x] == name)
		DIR.Name[x] = newname;
}

void FileM::WriteFile(const std::string& name, std::string tresc)
{
	int Previous = FindFile(name) - 1;
	int ToFinish = tresc.size();
	int FromStart = 0;
	if (Previous == -1)
	{
		throw std::exception("tresc");
	}
	int stop = 2;
	while (stop != 0)
	{
		int Adress = FindFreeBlock();
		if (Adress == -1)
		{
			throw std::exception("drive");
		}
		FileTable.Busy[Adress] = true;
		FileTable.Next[Previous] = Adress;
		FileTable.Next[Adress] = -1;

		Previous = Adress;

		for (int j = 0; j < dysk.BlockSize; j++)
		{
			if (FromStart == ToFinish)
				break;
			dysk.A[dysk.BlockSize * Adress + j] = tresc[FromStart];
			FromStart++;
		}
		if (FromStart == ToFinish)
			stop = 0;
	}
}
void FileM::PrintFile(const std::string& name)
{
	int Previous = FindFile(name) - 1;
	if (Previous == -1)
	{
		throw std::exception("tresc");
	}
	int Check = FileTable.Next[Previous];
	int Next = 0;
	if (Check != -1)
	{
		while (Previous != -1)
		{
			Next = Previous;

			for (int j = 0; j < dysk.BlockSize; j++)
			{
				if (dysk.A[dysk.BlockSize * Next + j] == 0)
					break;
				std::cout << dysk.A[dysk.BlockSize * Next + j];
			}
			Previous = FileTable.Next[Next];
		}
	}
	std::cout << "\n";
}

void FileM::ListDirectory() const
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] != "")
			std::cout << "Nazwa: " << DIR.Name[i] << "  Pierwszy Blok Pamieci:" << DIR.First[i] << "\n";
	}
}

void FileM::ListFAT() const
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (FileTable.Busy[i] == true)
			std::cout << i + 1 << "Busy: True, Nastepny Blok Pamieci:" << FileTable.Next[i] << "\n";
		else
			std::cout << i + 1 << "Busy: True, Nastepny Blok Pamieci:--\n";
	}

}

bool FileM::InvestigateFile(const std::string& name)
{
	int x = FindFile(name) - 1;
	if (x == -1)
	{
		return false;

	}
	return true;
}

void FileM::Stats()
{
	std::cout << "Miejsce (wolne/max): " << "/" << dysk.BlockCount << "\n";
}

std::string FileM::SendFile(const std::string& name)
{
	std::string data = "";
	int Previous = FindFile(name) - 1;
	if (Previous == -1)
	{
		throw std::exception("tresc");

	}

	for (int j = 0; j < dysk.BlockSize; j++)
	{
		if (dysk.A[dysk.BlockSize * Previous + j] == 0)
			break;
		data = data + dysk.A[dysk.BlockSize * Previous + j];


	}
	int Check = FileTable.Next[Previous];
	int Next;
	if (Check != -1)
	{
		while (Previous != -1)
		{
			Next = FileTable.Next[Previous];

			for (int j = 0; j < dysk.BlockSize; j++)
			{
				if (dysk.A[dysk.BlockSize * Next + j] == 0)
					break;

				data = data + dysk.A[dysk.BlockSize * Next + j];


			}

			Previous = FileTable.Next[Next];

		}
	}
	return data;
}
//WORKING ON IT
void FileM::ExtractFile(const std::string& name)
{

	CreateFile(name);
	std::string Content;
	std::string ToSend = "";
	int Count = 0;
	std::fstream FromFile;

	FromFile.open(name);
	while (!getline(FromFile, Content))
	{
		ToSend = ToSend + Content;

	}
	WriteFile(name, ToSend);
	FromFile.close();
}

void FileM::CreateSemaphors()
{
	vector<Semaphore> Semafor;
	Semafor.reserve(dysk.BlockCount);
	for (int i = 0; i <= dysk.BlockCount; i++) {
		Semafor.push_back(Semaphore(1));
	}
}






