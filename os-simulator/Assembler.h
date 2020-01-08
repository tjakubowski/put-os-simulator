#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Assembler
{
	int licznik = 0;
	short int registerA;
	short int registerB;
	short int registerC;

public:
	Assembler()
	{
		registerA = 0;
		registerB = 1; //rejestr B
		registerC = 0; //rejestr C
		licznik = 0;   //adres rozkau który ma byæ wykonany
	}

	short int get_A();
	short int get_B();
	short int get_C();

	void set_A(short int);
	void set_B(short int);
	void set_C(short int);

	int get_licznik();
	void set_licznik(int);
};

void open_file(string tab[], string plik); // otwiera i odczytuje plik z pliku który zosta³ podany 

string* split(string toSplit);

void runComand(string command, Assembler &ass);

void runProgram(string program[], Assembler &ass);