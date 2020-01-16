#include "pch.h"

#include <bitset>
#include <string>
#include <iostream>
#include <algorithm>
#include "Disc.h"
#include "FAT.h"
#include "DirectoryFile.h"


class FileM
{
public:
	FileM();

	bool OpenFile(const std::string& name);
	bool CloseFile(const std::string& name);

	//stworz plik
	bool CreateFile(const std::string& name);
	//usun plik
	bool DeleteFile(const std::string& name);
	//dodaj dodatkowa nazwe do pliku
	bool AddNewName(const std::string& name, const std::string& name2);
	//zmien nazwe pliku
	bool ReplaceNewName(const std::string& name, const std::string& name2);
	//zapisz tresc do pliku o podanej nazwie
	bool WriteFile(const std::string& name, const std::string& tresc);
	//Wczytuje plik do string::output
	bool PrintFile(const std::string& name);
	//Szuka pliku 1 - istnieje 0 - nie istnieje
	bool InvestigateFile(const std::string& name);
	//Wyswietla pliki w katalogu
	bool ListDirectory() const;
	//Wyswietla tablice FAT
	bool ListFAT() const;
	//Wyswietla zajete miejsce na dysku
	bool Stats() const;
	int FindFreeDirectory();
	Drive dysk;
	FAT FileTable;
	DirectoryFile DIR;


private:
	int FreeBlockCount;
	int FindFree();
	int FindFreeBlock();

	int FindFile(const std::string& name);

	bool Clearall();

	bool OpenFile(const std::string&, int process_id);







};

