#pragma once

class Drive
{
public:

	// zwraca nullptr w przypadku nieprawidlowego numeru bloku
	char* Block(int number);

	//Rozmiar Dysku
	const static int Size = 1024;
	//Wielkosc Bloku
	const static int BlockSize = 32;
	//Ilosc blokow tworzacych dysk
	const int BlockCount = Drive::Size / Drive::BlockSize;
	//eDysk w formie tablicy charów
	char A[Size];
	
};