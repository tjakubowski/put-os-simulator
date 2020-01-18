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

std::string FileM::OpenFile(Process*pcb)
{
	std::string name = pcb->file_name();//nazwa pliku powinno byc filename 
	std::string ProcessName = pcb->name();
	if (InvestigateFile(name) == false)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		//	return false;//jak moze byc w funkcji ktora zwraca stringa return false???
	}
	
	 //Wait(ProcessName);//wyjebuje tu blad napraw to 
	
	//przeslij PLIK stringiem.
	return SendFile(name);

}

bool FileM::CloseFile(std::string ProcessName)
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
bool FileM::CreateFile(const std::string& name)
{
	int temp;
	temp = FindFreeBlock();

	if (temp == -1)
	{
		std::cout << "Blad: Brak wolnego miejsca na dysku\n";
		return false;
	}

	int temp2 = FindFreeDirectory();
	if (temp2 == -1)
	{
			std::cout<<("Blad: FFD zwrocilo -1 kiedy niepowinno\n");
			return false;
	}

	//DIR.File(name, temp);

	DIR.Name[temp2-1] = name;
	DIR.First[temp2-1] = temp;
	FileTable.Busy[temp-1] = true;
	FileTable.Next[temp-1] = -1;
	FreeBlockCount--;

	return true;
}
	
//Szuka konkretnego pliku w katalogu
int FileM::FindFile(const std::string& name)
{
	int temp;
	for (int i = 0; i < dysk.BlockCount; i++)
	{
		if (DIR.Name[i] == name)
		{
			temp = DIR.First[i];
			return temp;
		}

	}
	return -1;
}

bool FileM::DeleteFile(const std::string& name)
{
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
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
	int temp2 = 1;
	while (temp2 != 0)
	{
		if (FileTable.Next[temp2] == -1)
		{
			FileTable.Busy[temp2] = false;
			FileTable.Next[temp2] = 0;
			temp2 = 0;
		}
		else
		{
			temp2 = FileTable.Next[temp2];
			FileTable.Next[temp2] = 0;
			FileTable.Busy[temp2] = false;
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
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		return false;
	}

	int SecondAdress = FindFreeDirectory();
	if (SecondAdress == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		return false;
	}
	DIR.Name[SecondAdress] = name2;
	DIR.First[SecondAdress] = x;
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
			std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
			return false;
		}
	}
	return true;
}


//WORK IN PROGRESS
bool FileM::WriteFile(std::string& name, std::string tresc)
{
	int z[32];
	int DoDysku, LicznikBitow = 0, PoprzedniBlok, temp;


	//Sprawdzamy czy istnieje taki plik
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		return false;
	}
	
	string hjelp = tresc;


//	temp = tresc.size();
	

	for (int i = 0; i < 32; i++)
	{
		z[i] = -1;
	}
	int y = 0;

	//Szukamy dodatkowych blokow
	/*while (DlugoscTresci > 32)
	{
		z[y] = FindFreeBlock();
		if (temp == -1)
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
	*/
	
	/*DoDysku = (x - 1)*dysk.BlockSize;
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
	*/
	return true;
}

bool FileM::PrintFile(const std::string& name)
{
	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		return false;
	}
	for (int i = 0; i < dysk.BlockSize; i++)
	{
		std::cout<< dysk.A[x * 32+i];

	}
	int temp;
	while (temp != -1)
	{
		for (int i = 0; i < dysk.BlockSize; i++)
		{
			std::cout<< dysk.A[x * 32 + i];


		}
		temp = FileTable.Next[temp];
	}
	std::cout<<("\n");
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
		std::cout<<"Blad: Plik "<< name <<"nieistnieje\n";
		return false;
	}
	return true;
}

bool FileM::Stats() const
{
	std::string Wyswietl = "";
	Wyswietl  = Wyswietl + "Miejsce (wolne/max): " + std::to_string(FreeBlockCount) + "/" + std::to_string(dysk.BlockCount) + '\n';
	std::cout<<Wyswietl;

}

std::string FileM::SendFile(const std::string& name)
{
	std::string data = "";

	int x = FindFile(name);
	if (x == -1)
	{
		std::cout << "Blad: Nie istnieje plik o nazwie " << name << "\n";
		return false;
	}

	for (int i = 0; i < dysk.BlockSize; i++)
	{
		data = data + dysk.A[x * 32 + i];

	}
	int temp;
	while (temp != -1)
	{
		for (int i = 0; i < dysk.BlockSize; i++)
		{
			data = data + dysk.A[x * 32 + i];


		}
		temp = FileTable.Next[temp];
	}
	//data += "\n";//zwiekszasz rozmiar programu bez sensu linijka 
	return data;


}