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

void runCommand(string c_line, Assembler &reg)
{
	string *line = split(c_line);
	cout << line[0] << " " << line[1] << " " << line[2] << endl;

	reg.set_licznik(reg.get_licznik() + 6);


	//MI rejestrX rejestrY/int
	if (line[0] == "MI") // Ustaw wartoœæ rejestru z commandLine[2] w commandLine[1]
	{
		if (line[1] == "A")
		{
			if (line[2] == "B")
			{
				reg.set_A(reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_A(reg.get_C());
			}
			else
			{
				reg.set_A(stoi(line[2]));
			}
		}
		else if (line[1] == "B")
		{
			if (line[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (line[2] == "C")
			{
				reg.set_B(reg.get_C());
			}
			else
			{
				reg.set_B(stoi(line[2]));
			}
		}
		else if (line[1] == "C")
		{
			if (line[2] == "A")
			{
				reg.set_C(reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_C(reg.get_B());
			}
			else
			{
				reg.set_C(stoi(line[2]));
			}
		}
	}
	//RD rejestrX
	else if (line[0] == "RD")
	{
		if (line[1] == "A")
		{
			short int val;
			cout << "Wpisz wartosc do rej. A: "; cin >> val;
			cin.ignore();
			reg.set_A(val);
		}
		else if (line[1] == "B")
		{
			short int val;
			cout << "Wpisz wartosc do rej. B: "; cin >> val;
			cin.ignore();
			reg.set_B(val);
		}
		else if (line[1] == "C")
		{
			short int val;
			cout << "Wpisz wartosc do rej. C: "; cin >> val;
			cin.ignore();
			reg.set_C(val);
		}
	}
	/////////////////////////////////////////////////////////////////// brak brak brak
	else if (line[0] == "MV") // Ustaw wartosc rejestru na liczbe z commandLine[2]
	{
		if (line[1] == "A")
		{
			if(line[2] == "B")
			{
				reg.set_A(reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_A(reg.get_C());
			}
			else
			{
				reg.set_A(stoi(line[2]));
			}
		}
		else if (line[1] == "B")
		{
			if (line[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (line[2] == "C")
			{
				reg.set_B(reg.get_C());
			}
			else
			{
				reg.set_B(stoi(line[2]));
			}
		}
		else if (line[1] == "C")
		{
			if (line[2] == "A")
			{
				reg.set_C(reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_C(reg.get_B());
			}
			else
			{
				reg.set_C(stoi(line[2]));
			}
		}
	}

	else if (line[0] == "AD") // AD rejestr/int ---> rejestr += rejestr/int
	{
		if (line[1] == "A")
		{
			if(line[2]=="A")
			{
				reg.set_A(reg.get_A() + reg.get_A());
			}
			else if(line[2] == "B")
			{
				reg.set_A(reg.get_A() + reg.get_B());
			}
			else if(line[2]=="C")
			{
				reg.set_A(reg.get_A() + reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() + stoi(line[2]));
			}
		}
		else if (line[1] == "B")
		{
			if(line[2]=="A")
			{
				reg.set_B(reg.get_B() + reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_B(reg.get_B() + reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_B(reg.get_B() + reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() + stoi(line[2]));
			}
		}
		else if (line[1] == "C")
		{

			if (line[2] == "A")
			{
				reg.set_C(reg.get_C() + reg.get_A());
			}
			else if(line[2] == "B")
			{
				reg.set_C(reg.get_C() + reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_C(reg.get_C() + reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() + stoi(line[2]));
			}
		}
		else
		{
			reg.set_A(reg.get_A() + stoi(line[2]));
		}
	}
	//SB rejestrX rejestrY/int   SB int
	else if (line[0] == "SB") //SB rejest/int ---> rejestr -= rejestr/int
	{
		if (line[1] == "A")
		{
			if (line[2] == "A")
			{
				reg.set_A(reg.get_A() - reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_A(reg.get_A() - reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_A(reg.get_A() - reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() - stoi(line[2]));
			}
		}
		else if (line[1] == "B")
		{
			if (line[2] == "A")
			{
				reg.set_B(reg.get_B() - reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_B(reg.get_B() - reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_B(reg.get_B() - reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() - stoi(line[2]));
			}
		}
		else if (line[1] == "C")
		{
			if (line[2] == "A")
			{
				reg.set_C(reg.get_C() - reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_C(reg.get_C() - reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_C(reg.get_C() - reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() - stoi(line[2]));
			}
		}
		else
		{
			reg.set_A(reg.get_A() - stoi(line[2]));
		}
	}

	//MU rejestrX rejestrY/int     MU int
	else if (line[0] == "MU") // 
	{
		if (line[1] == "A")
		{
			if (line[2] == "A")
			{
				reg.set_A(reg.get_A() *reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_A(reg.get_A() *reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_A(reg.get_A() *reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() *stoi(line[2]));
			}
		}
		else if (line[1] == "B")
		{
			if (line[2] == "A")
			{
				reg.set_B(reg.get_B() *reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_B(reg.get_B() *reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_B(reg.get_B() *reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() *stoi(line[2]));
			}
		}
		else if (line[1] == "A")
		{
			if (line[2] == "A")
			{
				reg.set_C(reg.get_C() *reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_C(reg.get_C() *reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_C(reg.get_C() *reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() *stoi(line[2]));
			}
		}
		else
		{
			reg.set_A(reg.get_A() * stoi(line[2]));
		}
	}
	//Jump gdy C!=0
	else if (line[0] == "JC")
	{
		if (reg.get_C() != 0)
			reg.set_licznik(stoi(line[1]));
	}

	//Jump gdy C==0
	else if (line[0] == "JZ")
	{
		if (reg.get_C() == 0)
			reg.set_licznik(stoi(line[1]));
	}

	//Jump gdy C<0
	else if (line[0] == "JL")
	{
		if (reg.get_C() < 0)
			reg.set_licznik(stoi(line[1]));
	}

	//Jump zawsze
	else if (line[0] == "JP")
	{
		reg.set_licznik(stoi(line[1]));
	}

	//Jump gdy C>0
	else if (line[0] == "JM")
	{
		if (reg.get_C() > 0)
			reg.set_licznik(stoi(line[1]));
	}
	//wyswitla rejestrX
	else if (line[0] == "PR")
	{
		if (line[1] == "A")
		{
			cout << reg.get_A();
		}
		else if (line[1] == "B")
		{
			cout << reg.get_B();
		}
		else if (line[1] == "C")
		{
			cout << reg.get_C();
		}
	}
	//CF nazwa
	else if (line[0] == "CF")
	{
		cout << "Tworzenie pliku wyjsciowego o nazwie: " << line[1] << endl;
		{
			fstream plik;
			plik.open(line[1], ios::out);
			plik.close();
		}
	}

	else if (line[0] == "AF")
	{
		if (line[2] == "A")
		{
			fstream plik;
			plik.open(line[1], ios::app);
			plik << reg.get_A();
			plik.close();
		}
		else if (line[2] == "B")
		{
			fstream plik;
			plik.open(line[1], ios::app);
			plik << reg.get_B();
			plik.close();
		}
		else if (line[2] == "C")
		{
			fstream plik;
			plik.open(line[1], ios::app);
			plik << reg.get_C();
			plik.close();
		}
		else
		{
			fstream plik;
			plik.open(line[1], ios::app);
			plik << (char)stoi(line[2]);
			plik.close();
		}
	}
	//zwieksza o 1 
	else if (line[0] == "IC")
	{
		if (line[1] == "A")
		{
			reg.set_A(reg.get_A() + 1);
		}
		else if (line[1] == "B")
		{
			reg.set_B(reg.get_B() + 1);
		}
		else if (line[1] == "C")
		{
			reg.set_C(reg.get_C() + 1);
		}
	}
	//zmnniejsza o 1
	else if (line[0] == "DC") // zmniejsza o 1 
	{
		if (line[1] == "A")
		{
			reg.set_A(reg.get_A() - 1);
		}
		else if (line[1] == "B")
		{
			reg.set_B(reg.get_B() - 1);
		}
		else if (line[1] == "C")
		{
			reg.set_C(reg.get_C() - 1);
		}
	}

	//-------------------------usunaæ jak bym nie doda³ nic tutaj--------------------------------
/*
	else if (line[0] == "FK")
	{
		//funkcja tworzenia procesu o nazwie commandLine[1]
	}
	else if (line[0] == "WT")
	{
		//funkcja wstrzymania procesu o nazwie commandLine[1]
	}
	else if (line[0] == "SE")
	{
		//
	}
	else if (line[0] == "KL")
	{
		//zabicie procesu o PID stoi(line[1])
	}
*/

	//koniec programu
	else if (line[0] == "EX")
	{
		reg.set_licznik(92);
		cout << "Koniec programu ";
	}
	//otwiera program
	else if (line[0] == "FO")
	{
	fstream plik;
		plik.open(line[1], ios::app);
	}
	//glupie to! chyba wywale 
	else if (line[0] == "FC")
	{
	fstream plik;
	plik.close();
	}
	else if (line[0] == "NP")
	{
	//nic nie robi!
	}
}

void runProgram(string program[], Assembler &reg)
{
	string com;
	while (reg.get_licznik() != 92)
	{
		com = program[reg.get_licznik() / 6];
		runCommand(com, reg);
	}
}

int main()
{
	Assembler ass;				// clasa rejestr
	string program[30];			// string program o +tablicy 30 30*6
	readFile(program,"ciagEulera.txt");	
	runProgram(program,ass);
	system("pause");
	return 0;
}

