#include "pch.h"

#include "FileM.h"
#include <iostream>


//Zeruje Tablice FAT i DIR
bool FileM::Clearall()
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		FileTable.Next[i] = 0;
		FileTable.Busy[i] = false;
		FreeBlockCount = dysk.BlockCount;
		DIR.Name[i] ="";
	}
}

bool FileM::OpenFile(const std::string& name, int process_id)
{
	if (InvestigateFile(name) == false)
	{
			std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
		return false;
	}
	
	 Wait(std::string& name);
	
	//przeslij PLIK stringiem.
	SendFile(name);

}

bool FileM::CloseFile(const std::string& name)
{
	Semaphore::Signal;
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
bool FileM::CreateFile(const std::string& name)
{
	int hjelp;
	hjelp = FindFreeBlock();




	if (hjelp == -1)
	{
		std::cout << "Blad: Brak wolnego miejsca na dysku" << endl;
		return false;
	}

	int hjelp2 = FindFreeDirectory();
	if (hjelp2 == -1)
	{
			std::cout<<("Blad: FFD zwrocilo -1 kiedy niepowinno\n");
			return false;
	}

	DIR.Name[hjelp2-1] = name;
	DIR.First[hjelp2-1] = hjelp;
	FileTable.Busy[hjelp-1] = true;
	FileTable.Next[hjelp-1] = -1;
	FreeBlockCount--;

	return true;
}
	
//Szuka konkretnego pliku w katalogu
int FileM::FindFile(const std::string& name)
{
	int hjelp;
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] == name)
		{
			hjelp = DIR.First[i];
			return hjelp;
		}

	}
	return -1;
}

bool FileM::DeleteFile(const std::string& name)
{
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
		return false;
	}
	
	//Usuwanie innych nazw
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.First[i] == x)
		{
			DIR.First[i] = 0;
			DIR.Name[i] = "";
		}
	}
	//Szuka wszystkich częścipliku i usuwa je od pierwszego do ostatniego
	int hjelp2 = 1;
	while (hjelp2 != 0)
	{
		if (FileTable.Next[hjelp2] == -1)
		{
			FileTable.Busy[hjelp2] = false;
			FileTable.Next[hjelp2] = 0;
			hjelp2 = 0;
		}
		else
		{
			hjelp2 = FileTable.Next[hjelp2];
			FileTable.Next[hjelp2] = 0;
			FileTable.Busy[hjelp2] = false;
		}
	}
	return true;
}

//Dodaje dodatkowa nazwe dla istniejacego pliku 
bool FileM::AddNewName(const std::string& name, const std::string& name2)
{
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
		return false;
	}

	int hjelp = FindFreeDirectory();
	if (hjelp == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
		return false;
	}
	DIR.Name[hjelp] += name2;
	DIR.First[hjelp] = x;
	return true;
}

bool FileM::ReplaceNewName(const std::string& name, const std::string& name2)
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] == name)
			DIR.Name[i] = name2;
		if (i == dysk.BlockCount - 1 && DIR.Name[i] != name2)
		{
			std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
			return false;
		}
	}
	return true;
}

bool FileM::WriteFile(const std::string& name, const std::string& tresc)
{
	int z[32], DoDysku, LicznikBitow = 0, PoprzedniBlok, hjelp;
	int DlugoscTresci = tresc.length();
	int x = FindFile(name);
	const char  cstr[tresc.size()+1];
	//std::copy(tresc.begin(), tresc.end(), cstr);
	//cstr[tresc.size()]='\n';

	//Sprawdzamy czy istnieje taki plik
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		return false;
	}

	for (int i = 0; i < 32; i++)
	{
		z[i] = -1;
	}
	int y = 0;

	//Szukamy dodatkowych blokow
	while (DlugoscTresci > 32)
	{
		z[y] = FindFreeBlock();
		if (hjelp == -1)
		{
			std::cout <<"Blad: Brak wolnego miejsca na dysku\n";
			return false;
		}
		FileTable.Busy[z[y]] = true;
		FreeBlockCount--;
		FileTable.Next[z[y]] = -1;
		FileTable.Next[PoprzedniBlok] = z[y];
		PoprzedniBlok = z[y];

		y++;
		DlugoscTresci = DlugoscTresci - 32;
	}
	DoDysku = (x - 1)*dysk.BlockSize;
	//Przepisywanie tresci dla pierwszego bloku pamieci
	for (int i = 0; i < dysk.BlockSize; i++)
	{
		dysk.A[DoDysku + i] = cstr[LicznikBitow];
		LicznikBitow++;
		if (LicznikBitow == tresc.length())
			break;
	}
	//Dla kolejnych
	for (int i = 0; i < 32; i++)
	{
		if (z[i] == -1)
			break;
		
		DoDysku = z[i] * dysk.BlockSize;
		for (int j = 0; j < dysk.BlockSize; j++)
		{
			dysk.A[DoDysku + j] = cstr[LicznikBitow];
			LicznikBitow++;
			if (LicznikBitow == tresc.size() + 1)
				break;
		}
	}
	return true;
}

bool FileM::PrintFile(const std::string& name)
{
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
		return false;
	}
	for (int i = 0; i < dysk.BlockSize; i++)
	{
		printf("%c", dysk.A[x * 32+i]);

	}
	int hjelp;
	while (hjelp != -1)
	{
		for (int i = 0; i < dysk.BlockSize; i++)
		{
			printf("%s", dysk.A[x * 32 + i]);


		}
		hjelp = FileTable.Next[hjelp];s
	}
	cout<<("\n");
	return true;
}

bool FileM::ListDirectory() const
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] != "")
		std::cout<<"Nazwa: " << DIR.Name[i]<<"  Pierwszy Blok Pamieci:"<< DIR.First[i] << "\n";
	}
}

bool FileM::ListFAT() const
{
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (FileTable.Busy[i] == true)
			printf("%d. Busy: True, Nastepny Blok Pamieci: %d\n", i+1, FileTable.Next[i]);
		else
			printf("%d. Busy: False, Nastepny Blok Pamieci: -\n", i+1);

	}
}


bool FileM::InvestigateFile(const std::string& name)
{
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout<<"Blad: Plik "<< name <<"nieistnieje\n";
		return false;
	}
	return true;
}

bool FileM::Stats() const
{
	std::string Wyswietl;
	Wyswietl += "Miejsce (wolne/max): " + std::to_string(FreeBlockCount) + "/" + std::to_string(dysk.BlockCount) + '\n';
	cout<<Wyswietl;

}

string FileM::SendFile(const std::string& name)
{
	std::string Wysylacz = "";

	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << endl;
		return false;
	}

	for (int i = 0; i < dysk.BlockSize; i++)
	{
		Wysylacz += dysk.A[x * 32 + i];

	}
	int hjelp;
	while (hjelp != -1)
	{
		for (int i = 0; i < dysk.BlockSize; i++)
		{
			Wysylacz += dysk.A[x * 32 + i]);


		}
		hjelp = FileTable.Next[hjelp];
	}
	Wysylacz += "\n";
	return Wysylacz;


}