#pragma once

class Drive
{
public:

	// zwraca nullptr w przypadku nieprawidlowego numeru bloku
	char* Block(int number);
	const char* Block(int number) const;

	//Rozmiar Dysku
	const static int Size = 1024;
	//Wielkosc Bloku
	const static int BlockSize = 32;
	//Ilosc blokow tworzacych dysk
	const static int BlockCount = Drive::Size /  Drive::BlockSize;
	//eDysk w formie tablicy charów
	char A[Size];
	
};