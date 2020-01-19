#include "pch.h"

#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Disc.h"
#include "FAT.h"
#include "DirectoryFile.h"

class FileM : public Singleton<FileM>
{

public:


	friend class Singleton<FileM>;
	//Konstruktor nowego bloku zarzadzania plikami
	FileM();
	//Instrukcja Otworzenia Pliku
	std::string OpenFile(Process*pcb);
	//instrukcja Zamknięcia Pliku
	bool CloseFile(std::string ProcessName);
	//stworz plik
	bool CreateFile(const std::string& name);
	//usun plik
	bool DeleteFile(const std::string& name);
	//dodaj dodatkowa nazwe do pliku
	bool AddNewName(const std::string& name, const std::string& name2);
	//zmien nazwe pliku
	bool ReplaceNewName(const std::string& name, const std::string& name2);
	//zapisz tresc do pliku o podanej nazwie
	bool WriteFile(const std::string& name, string tresc);
	//Przesyla plik jako string
	static std::string SendFile(const std::string& name);
	//Wyswietla plik za pomoca couta
	bool PrintFile(const std::string& name);
	//Szuka pliku true - istnieje false - nie istnieje
	bool InvestigateFile(const std::string& name);
	//Pobiera plik z zewnetrznego pliku
	bool ExtractFile(const std::string& name, std::fstream tekst);
	//Wyswietla pliki w katalogu
	bool ListDirectory() const;
	//Wyswietla tablice FAT
	bool ListFAT() const;
	//Wyswietla zajete miejsce na dysku
	bool Stats() const;
	//Znajduje miejsce na adres nowego Pliku w DIRze
	int FindFreeDirectory();
	Drive dysk;
	FAT FileTable;
	DirectoryFile DIR;

	Drive dysk2;
	
	

private:
	int FreeBlockCount;
	
	int FindFreeBlock();

	int FindFile(const std::string& name);

};

