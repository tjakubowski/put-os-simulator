#include "Assembler.h"

using namespace std;

short int Assembler::get_A()
{
	return registerA;
}

short int Assembler::get_B()
{
	return registerB;
}

short int Assembler::get_C()
{
	return registerC;
}

void Assembler::set_A(short int v)
{
	registerA = v;
}

void Assembler::set_B(short int v)
{
	registerB = v;
}

void Assembler::set_C(short int v)
{
	registerC = v;
}

int Assembler::get_licznik()
{
	return licznik;
}

void Assembler::set_licznik(int v)
{
	licznik = v;
}

void readFile(string myArray[], string fileName)
{
	using namespace std;

	ifstream file(fileName);
	if (file.is_open())
	{

		for (int i = 0; i < 30; ++i)
		{
			getline(file, myArray[i]);
			//cout << myArray[i] << endl;
		}
	}
	file.close();
}

string* split(string toSplit)
{
	string* splitted = new string[5];
	short counter = 0;
	for (short i = 0; i < toSplit.length(); i++) {
		if (toSplit[i] == ' ')
			counter++;
		else
			splitted[counter] += toSplit[i];
	}
	return splitted;
}

void runCommand(string command, Assembler &reg)
{
	string *commandLine = split(command);
	cout << commandLine[0] << " " << commandLine[1] << " " << commandLine[2] << endl;

	reg.set_licznik(reg.get_licznik() + 6);


	//MI rejestrX rejestrY/int
	if (commandLine[0] == "MI") // Ustaw wartoœæ rejestru z commandLine[2] w commandLine[1]
	{
		if (commandLine[1] == "A")
		{
			if (commandLine[2] == "B")
			{
				reg.set_A(reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_A(reg.get_C());
			}
			else
			{
				reg.set_A(stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "B")
		{
			if (commandLine[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_C());
			}
			else
			{
				reg.set_B(stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "C")
		{
			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_C(reg.get_B());
			}
			else
			{
				reg.set_C(stoi(commandLine[2]));
			}
		}
	}
	//RD rejestrX
	else if (commandLine[0] == "RD")
	{
		if (commandLine[1] == "A")
		{
			short int val;
			cout << "Wpisz wartosc do rej. A: "; cin >> val;
			cin.ignore();
			reg.set_A(val);
		}
		else if (commandLine[1] == "B")
		{
			short int val;
			cout << "Wpisz wartosc do rej. B: "; cin >> val;
			cin.ignore();
			reg.set_B(val);
		}
		else if (commandLine[1] == "C")
		{
			short int val;
			cout << "Wpisz wartosc do rej. C: "; cin >> val;
			cin.ignore();
			reg.set_C(val);
		}
	}
	/////////////////////////////////////////////////////////////////// brak brak brak
	else if (commandLine[0] == "MV") // Ustaw wartosc rejestru na liczbe z commandLine[2]
	{
		if (commandLine[1] == "A")
		{
			if(commandLine[2] == "B")
			{
				reg.set_A(reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_A(reg.get_C());
			}
			else
			{
				reg.set_A(stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "B")
		{
			if (commandLine[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_C());
			}
			else
			{
				reg.set_B(stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "C")
		{
			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_C(reg.get_B());
			}
			else
			{
				reg.set_C(stoi(commandLine[2]));
			}
		}
	}

	else if (commandLine[0] == "AD") // AD rejestr/int ---> rejestr += rejestr/int
	{
		if (commandLine[1] == "A")
		{
			if(commandLine[2]=="A")
			{
				reg.set_A(reg.get_A() + reg.get_A());
			}
			else if(commandLine[2] == "B")
			{
				reg.set_A(reg.get_A() + reg.get_B());
			}
			else if(commandLine[2]=="C")
			{
				reg.set_A(reg.get_A() + reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() + stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "B")
		{
			if(commandLine[2]=="A")
			{
				reg.set_B(reg.get_B() + reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_B(reg.get_B() + reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_B() + reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() + stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "C")
		{

			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_C() + reg.get_A());
			}
			else if(commandLine[2] == "B")
			{
				reg.set_C(reg.get_C() + reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_C(reg.get_C() + reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() + stoi(commandLine[2]));
			}
		}
		else
		{
			reg.set_A(reg.get_A() + stoi(commandLine[2]));
		}
	}
	//SB rejestrX rejestrY/int   SB int
	else if (commandLine[0] == "SB") //SB rejest/int ---> rejestr -= rejestr/int
	{
		if (commandLine[1] == "A")
		{
			if (commandLine[2] == "A")
			{
				reg.set_A(reg.get_A() - reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_A(reg.get_A() - reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_A(reg.get_A() - reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() - stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "B")
		{
			if (commandLine[2] == "A")
			{
				reg.set_B(reg.get_B() - reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_B(reg.get_B() - reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_B() - reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() - stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "C")
		{
			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_C() - reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_C(reg.get_C() - reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_C(reg.get_C() - reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() - stoi(commandLine[2]));
			}
		}
		else
		{
			reg.set_A(reg.get_A() - stoi(commandLine[2]));
		}
	}

	//MU rejestrX rejestrY/int     MU int
	else if (commandLine[0] == "MU") // 
	{
		if (commandLine[1] == "A")
		{
			if (commandLine[2] == "A")
			{
				reg.set_A(reg.get_A() *reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_A(reg.get_A() *reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_A(reg.get_A() *reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() *stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "B")
		{
			if (commandLine[2] == "A")
			{
				reg.set_B(reg.get_B() *reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_B(reg.get_B() *reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_B() *reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() *stoi(commandLine[2]));
			}
		}
		else if (commandLine[1] == "A")
		{
			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_C() *reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_C(reg.get_C() *reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_C(reg.get_C() *reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() *stoi(commandLine[2]));
			}
		}
		else
		{
			reg.set_A(reg.get_A() * stoi(commandLine[2]));
		}
	}
	//Jump gdy C!=0
	else if (commandLine[0] == "JC")
	{
		if (reg.get_C() != 0)
			reg.set_licznik(stoi(commandLine[1]));
	}

	//Jump gdy C==0
	else if (commandLine[0] == "JZ")
	{
		if (reg.get_C() == 0)
			reg.set_licznik(stoi(commandLine[1]));
	}

	//Jump gdy C<0
	else if (commandLine[0] == "JL")
	{
		if (reg.get_C() < 0)
			reg.set_licznik(stoi(commandLine[1]));
	}

	//Jump zawsze
	else if (commandLine[0] == "JP")
	{
		reg.set_licznik(stoi(commandLine[1]));
	}

	//Jump gdy C>0
	else if (commandLine[0] == "JM")
	{
		if (reg.get_C() > 0)
			reg.set_licznik(stoi(commandLine[1]));
	}
	//wyswitla rejestrX
	else if (commandLine[0] == "PR")
	{
		if (commandLine[1] == "A")
		{
			cout << reg.get_A();
		}
		else if (commandLine[1] == "B")
		{
			cout << reg.get_B();
		}
		else if (commandLine[1] == "C")
		{
			cout << reg.get_C();
		}
	}
	//CF nazwa
	else if (commandLine[0] == "CF")
	{
		cout << "Tworzenie pliku wyjsciowego o nazwie: " << commandLine[1] << endl;
		{
			fstream plik;
			plik.open(commandLine[1], ios::out);
			plik.close();
		}
	}

	else if (commandLine[0] == "AF")
	{
		if (commandLine[2] == "A")
		{
			fstream plik;
			plik.open(commandLine[1], ios::app);
			plik << reg.get_A();
			plik.close();
		}
		else if (commandLine[2] == "B")
		{
			fstream plik;
			plik.open(commandLine[1], ios::app);
			plik << reg.get_B();
			plik.close();
		}
		else if (commandLine[2] == "C")
		{
			fstream plik;
			plik.open(commandLine[1], ios::app);
			plik << reg.get_C();
			plik.close();
		}
		else
		{
			fstream plik;
			plik.open(commandLine[1], ios::app);
			plik << (char)stoi(commandLine[2]);
			plik.close();
		}
	}
	//zwieksza o 1 
	else if (commandLine[0] == "IC")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() + 1);
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_B() + 1);
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_C() + 1);
		}
	}
	//zmnniejsza o 1
	else if (commandLine[0] == "DC") // zmniejsza o 1 
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() - 1);
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_B() - 1);
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_C() - 1);
		}
	}

	//-------------------------usunaæ jak bym nie doda³ nic tutaj--------------------------------
/*
	else if (commandLine[0] == "FK")
	{
		//funkcja tworzenia procesu o nazwie commandLine[1]
	}
	else if (commandLine[0] == "WT")
	{
		//funkcja wstrzymania procesu o nazwie commandLine[1]
	}
	else if (commandLine[0] == "SE")
	{
		//.sendCom(commandLine[1],commandLine[2]);
	}
	else if (commandLine[0] == "KL")
	{
		//zabicie procesu o PID stoi(commandLine[1])
	}
*/

	//koniec programu
	else if (commandLine[0] == "EX")
	{
		reg.set_licznik(92);
		cout << "Koniec programu ";
	}
	//otwiera program
	else if (commandLine[0] == "FO")
	{
	fstream plik;
		plik.open(commandLine[1], ios::app);
	}
	//glupie to! chyba wywale 
	else if (commandLine[0] == "FC")
	{
	fstream plik;
	plik.close();
	}
	else if (commandLine[0] == "NP")
	{
	//nic nie robi!
	}
}

void runProgram(string program[], Assembler &reg)
{
	string command;
	while (reg.get_licznik() != 92)
	{
		command = program[reg.get_licznik() / 6];
		runCommand(command, reg);
	}
}

int main()
{
	Assembler reg;				// clasa rejestr
	string program[30];			// string program o tablicy 30 
	readFile(program,"ciagEulera.txt");	
	
	cout << program[0] << "cos";

	// czytaj program
	runProgram(program,reg);
	cout << program[4];
	system("pause");
	return 0;
}

