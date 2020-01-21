#include "pch.h"

#include "FileM.h"
#include <exception>

using namespace std;

int main()
{
	try
	{
		FileM Dummy;
		Dummy.CreateFile("Nazwa");
		Dummy.WriteFile("Nazwa", "Small step for process big step for program  abcdefghijklmnoprstuwzyxbb");
		Dummy.PrintFile("Nazwa");
		Dummy.AddNewName("Nazwa", "NowaNazwa");
	}
	catch (string tresc)
	{
		std::cout << "Tresc";
	}
	catch (const std::exception & a)
	{
		std::cout << "Blad";
	};




	return 0;
}
