#include "FileM.h"
#include "pch.h"
#include <iostream>


//Zeruje Tablice FAT i DIR
bool FileM::Clearall()
{
	for (int i = 0; i < Drive::BlockCount; i++)
	{
		FileTable.Next[i] = 0;
		FileTable.Busy[i] = false;
		FreeBlockCount = Drive::BlockCount;
		DIR.Name[i] ="";
	}
}


//Szuka pierwszego wolnego bloku w FAT
int FileM::FindFreeBlock()
{
	for (int i = 0; i < Drive::BlockCount; i++)
		if (!FileTable.Busy[i] == false) return i+1;
	return -1;
}
//Szuka pierwszego wolnego miejsca w katalogu
int  FileM::FindFreeDirectory()
{
	for (int i = 0; i < Drive::BlockCount; i++)
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
		printf_s("Blad: Brak wolnego miejsca na dysku\n");
		return false;
	}

	int hjelp2 = FindFreeDirectory();
	if (hjelp2 == -1)
	{
			printf_s("Blad: FFD zwrocilo -1 kiedy niepowinno\n");
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
	for (int i = 0; i < Drive::BlockCount; i++)
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
		printf_s("Blad: Nie istnieje plik o nazwie %s\n", name);
		return false;
	}
	
	//Usuwanie innych nazw
	for (int i = 0; i < Drive::BlockCount; i++)
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
		printf_s("Blad: Nie istnieje plik o nazwie %s\n", name.data());
		return false;
	}

	int hjelp = FindFreeDirectory();
	if (hjelp == -1)
	{
			printf_s("Blad: FFD zwrocilo -1 kiedy niepowinno\n");
			return false;
	}
	DIR.Name[hjelp] += name2;
	DIR.First[hjelp] = x;
	return true;
}

bool FileM::ReplaceNewName(const std::string& name, const std::string& name2)
{
	for (int i = 0; i < Drive::BlockCount; i++)
	{
		if (DIR.Name[i] == name)
			DIR.Name[i] = name2;
		if (i == Drive::BlockCount - 1 && DIR.Name[i] != name2)
		{
			printf_s("Blad: Nie istnieje plik o nazwie %s\n", name.data());
			return false;
		}
	}
	return true;
}

bool FileM::WriteFile(const std::string& name, const std::string& tresc)
{
	int z[32], y = 0, DoDysku, LicznikBitow = 0, PoprzedniBlok;
	int hjelp = tresc.length();
	int x = FindFile(name);
	const char  cstr[tresc.size()+1];
	std::copy(tresc.begin(), tresc.end(), cstr);
	cstr[tresc.size()]='\n';

	if (x == -1)
	{
		printf_s("Blad: Nie istnieje plik o nazwie %s\n", name.data());
		return false;
	}
	
	for (int i = 0; i < 32; i++)
	{
		z[i] = -1;
	}
	//Szukamy dodatkowych blokow
	while(hjelp > 32)
	{
		z[y] = FindFreeBlock();
		if (hjelp == -1)
		{
			printf_s("Blad: Brak wolnego miejsca na dysku\n");
			return false;
		}
		FileTable.Busy[z[y]] = true;
		FreeBlockCount--;
		FileTable.Next[z[y]] = -1;
		FileTable.Next[PoprzedniBlok] = z[y];
		PoprzedniBlok = z[y];

		y++;
		hjelp = hjelp - 32;
	}
	DoDysku = (x - 1)*Drive::BlockSize;
	//Przepisywanie tresci dla pierwszego bloku pamieci
	for (int i = 0; i < Drive::BlockSize; i++)
	{
		dysk.A[DoDysku + i] = cstr[LicznikBitow];
		LicznikBitow++;
		if (LicznikBitow == tresc.size() + 1)
			break;
	}
	//Dla kolejnych
	for (int i = 0; i < 32; i++)
	{
		if (z[i] == -1)
			break;
		
		DoDysku = z[i] * Drive::BlockSize;
		for (int j = 0; j < Drive::BlockSize; j++)
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
		printf_s("Blad: Nie istnieje plik o nazwie %s\n", name.data());
		return false;
	}

	for (int i = 0; i < Drive::BlockSize; i++)
	{
		printf("%c", dysk.A[x * 32+i]);

	}
	int hjelp;
	while (hjelp != -1)
	{
		for (int i = 0; i < Drive::BlockSize; i++)
		{
			printf("%s", dysk.A[x * 32 + i]);


		}
		hjelp = FileTable.Next[hjelp];
	}
	printf("\n");
	return true;
}

bool FileM::ListDirectory() const
{
	for (int i = 0; i < Drive::BlockCount; i++)
	{
		if (DIR.Name[i] != "")
			printf("Nazwa: %s Pierwszy Blok Pamieci: %d\n", DIR.Name[i], DIR.First[i]);
	}
}

bool FileM::ListFAT() const
{
	for (int i = 0; i < Drive::BlockCount; i++)
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
		printf_s("Blad: Plik %s nieistnieje\n", name.data());
		return false;
	}
	return true;
}

bool FileM::Stats() const
{
	std::string Wyswietl;
	Wyswietl += "Miejsce (wolne/max): " + std::to_string(FreeBlockCount) + "/" + std::to_string(Drive::BlockCount) + '\n';
	printf_s("%s\n", Wyswietl.data());

}