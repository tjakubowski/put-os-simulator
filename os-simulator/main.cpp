#include "pch.h"
#include <iostream>
#include "Shell.h"
#include "FileM.h"
//#include "RAM.h"
//#include "Assembler.h"

//FileM disc;
//RAM ram;
//Assembler ass;


//PCB *p1 = new PCB(1);
int change_state = 0;
std::string code;


int main()
{
	Shell shell;
	FileM Nowy;
	Nowy.CreateFile("AAA");
	Nowy.WriteFile("AAA", "trescaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	Nowy.PrintFile("AAA");
	Nowy.ListFAT();
	Nowy.ListDirectory();
	Nowy.PrintDrive();
	Nowy.AddNewName("AAA", "A2");
	Nowy.PrintFile("A2");

	Nowy.AddFileContent("A2", "bbbbbbbbbbbbbbbbbbbb");
	Nowy.CreateFile("Kolejny plik");
	Nowy.WriteFile("Kolejny plik", "tresc2");
	Nowy.PrintDrive();



	std::cout << "OS Simulator" << std::endl;

	shell.run();
	
	return 0;
}