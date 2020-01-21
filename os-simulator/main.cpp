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
	Nowy.CreateFile("plik");
	Nowy.AddFileContent("plik", "druga czesc kodu aaaaaaaaaaaaaaaaa");
	Nowy.AddFileContent("plik", "Trzecia czesc kodu iiiiiiiiiiiiiiiii");
	Nowy.ListFAT();


	std::cout << "OS Simulator" << std::endl;

	shell.run();
	
	return 0;
}