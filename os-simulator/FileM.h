#pragma once

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

class FileM  :public Singleton<FileM>
{
public:

	friend class Singleton<FileM>;
	//Konstruktor nowego bloku zarzadzania plikami
	FileM();
	//Instrukcja Otworzenia Pliku
	std::string OpenFile(Process* pcb);
	//instrukcja Zamknięcia Pliku
	void CloseFile(std::string ProcessName);
	//stworz plik
	void CreateFile(const std::string& name);
	//usun plik
	void DeleteFile(const std::string& name);
	//dodaj dodatkowa nazwe do pliku
	void AddNewName(const std::string& name, const std::string& name2);
	//zmien nazwe pliku
	void ReplaceNewName(const std::string& name, const std::string& name2);
	//zapisz tresc do pliku o podanej nazwie
	void WriteFile(const std::string& name, string tresc);
	//Przesyla plik jako string
	std::string SendFile(const std::string& name);
	//Wyswietla plik za pomoca couta
	void PrintFile(const std::string& name);
	//Szuka pliku true - istnieje false - nie istnieje
	bool InvestigateFile(const std::string& name);
	//Pobiera plik z zewnetrznego pliku
	void ExtractFile(const std::string& name, std::fstream tekst);
	//Wyswietla pliki w katalogu
	void ListDirectory() const;
	//Wyswietla tablice FAT
	void ListFAT() const;
	//Wyswietla zajete miejsce na dysku
	void Stats() const;
	//Znajduje miejsce na adres nowego Pliku w DIRze
	int FindFreeDirectory();
	Drive dysk;
	FAT FileTable;
	DirectoryFile DIR;




private:
	int FreeBlockCount;

	int FindFreeBlock();

	int FindFile(const std::string& name);

};

