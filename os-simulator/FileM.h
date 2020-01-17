#include "pch.h"

#include <bitset>
#include <string>
#include <iostream>
#include <algorithm>
#include "Disc.h"
#include "FAT.h"
#include "DirectoryFile.h"
#include "Semaphore.h"


class FileM : public Singleton<FileM>
{

public:
	friend class Singleton<FileM>;
	FileM();
	//Instrukcja Otworzenia Pliku
	string OpenFile(const std::string& name, std::string ProcessName);
	//instrukcja Zamknięcia Pliku
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
	//Przesyla plik jako string
	string SendFile(const std::string& name);
	//Wyswietla plik za pomoca couta
	bool PrintFile(const std::string& name);
	//Szuka pliku true - istnieje false - nie istnieje
	bool InvestigateFile(const std::string& name);
	//Wyswietla pliki w katalogu
	bool ListDirectory() const;
	//Wyswietla tablice FAT
	bool ListFAT() const;
	//Wyswietla zajete miejsce na dysku
	bool Stats() const;
	//Szuka nastepnego wolnego miejsca w DIRze
	int FindFreeDirectory();
	Drive dysk;
	FAT FileTable;
	DirectoryFile DIR;
	


private:
	//Zlicza wolne blocki
	int FreeBlockCount;
	//Szuka wolnego bloku
	int FindFreeBlock();
	//Szuka pliku i zwraca pierwszy element 
	int FindFile(const std::string& name);

	bool Clearall()







};

