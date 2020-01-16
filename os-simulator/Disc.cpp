#include "Disc.h"
#include "pch.h"

//Num = liczba blocków
char* Drive::Block(int Num)
{

	//jeżeli Num < 0 zwracamy 0
	if (Num < 0)
		return nullptr;
	//jeżeli Num >= wielokości dysku zwracamy 0
	if (Num >= BlockCount)
		return nullptr;
	//Jeżeli 0 < Num <= BlockCount zajmuje miejsce równe Num*BlockSize
	return &A[Num*BlockSize];

}