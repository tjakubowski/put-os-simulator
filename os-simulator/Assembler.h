#include <iostream>
#include <string>
#include "Singleton.h"
#include "ProcessManager.h"
using namespace std;

class Assembler : public Singleton<Assembler>
{
	friend class Singleton<Assembler>;
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
	int licznikLine = 0;

	string commands[30];
	int get_licznik();
	void set_licznik(int);
	int ile_arg(string command);

	string* split(string toSplit);

	void runCommand(string c_line, Assembler& reg);

	void runProgram(Assembler& reg);

	void savefile(string withfile, Assembler& reg);
};


