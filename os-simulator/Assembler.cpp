#include "pch.h"
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
void Assembler::savefile(string withfile, Assembler& reg)
{
	int j = 0;
	string pom = "";
	string pomCommand[500];

	for (int i = 0; i < withfile.size(); i++)
	{
		if (withfile[i] == ' ')
		{
			pomCommand[j] = pom;
			j++;
			pom = "";
		}
		else
		{
			pom += withfile[i];
		}
	}
	pomCommand[j] = pom;
	int ile = 0;
	int x = 0;
	for (int i = 0; i < j; i++)
	{

		ile = reg.ile_arg(pomCommand[i]);
		if (ile == 0)
		{
			reg.commands[x] = "";
			reg.commands[x] = pomCommand[i];
		}
		else if (ile == 1)
		{

			reg.commands[x] = pomCommand[i] + " " + pomCommand[++i];
			i += 1;
		}
		else if (ile == 2)
		{
			reg.commands[x] = pomCommand[i] + " " + pomCommand[i + 1] + " " + pomCommand[i + 2];
			i += 2;
		}
		else if (ile == 3)
		{
			reg.commands[x] = pomCommand[i] + " " + pomCommand[++i] + " " + pomCommand[++i] + " " + pomCommand[++i];
			i += 3;
		}
		else if (ile == 4)
		{
			reg.commands[x] = pomCommand[i] + pomCommand[++i] + pomCommand[++i] + pomCommand[++i] + pomCommand[++i];
			i = +4;
		}
		x++;
	}
}
int Assembler::ile_arg(const string command)
{
	if (command == "AD")
		return 2;
	else if (command == "SB")
		return 2;
	else if (command == "MV")
		return 2;
	else if (command == "MU")
		return 2;
	else if (command == "MI")
		return 2;
	else if (command == "RD")
		return 1;
	else if (command == "IC")
		return 1;
	else if (command == "DC")
		return 1;
	else if (command == "JP")
		return 1;
	else if (command == "JC")
		return 1;
	else if (command == "JZ")
		return 1;
	else if (command == "JL")
		return 1;
	else if (command == "JM")
		return 1;
	else if (command == "EX")
		return 0;
	else if (command == "NP")
		return 0;
	else if (command == "FO")
		return 1;
	else if (command == "FC")
		return 1;
	else if (command == "DF")
		return 1;
	else if (command == "CF")
		return 1;
	else if (command == "SF")
		return 2;
	else if (command == "AF")
		return 2;
	else if (command == "AR")
		return 2;
	else if (command == "PF")
		return 1;
	else if (command == "PS")
		return 1;
	else if (command == "PO")
		return 1;
	else if (command == "PC")
		return 3;
	else if (command == "PD")
		return 1;
	else
	{
		std::cout << "\nNierozpoznano komendy w ILE_ARG!";
		return 0;
	}
}

//przyjmuje string komendy i dzieli
string* Assembler::split(string toSplit)
{
	string* splitted = new string[5];
	splitted[0] = "";
	splitted[1] = "";
	splitted[2] = "";
	splitted[3] = "";
	short counter = 0;
	for (short i = 0; i < toSplit.length(); i++)
	{
		if (toSplit[i] == ' ')
			counter++;
		else
			splitted[counter] += toSplit[i];
	}
	return splitted;
}

void Assembler::runCommand(string c_line, Assembler& reg)
{
	string* line = split(c_line);
	cout << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << endl;

	string ss = line[0] + line[1] + line[2] + line[3];
	int size_ss = ss.size();
	reg.set_licznik(reg.get_licznik() + size_ss);


	if (line[0] == "MI")
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

	else if (line[0] == "MV")
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

	else if (line[0] == "AD")
	{
		if (line[1] == "A")
		{
			if (line[2] == "A")
			{
				reg.set_A(reg.get_A() + reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_A(reg.get_A() + reg.get_B());
			}
			else if (line[2] == "C")
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
			if (line[2] == "A")
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
			else if (line[2] == "B")
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
	}

	else if (line[0] == "SB")
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
	}

	else if (line[0] == "MU")
	{
		if (line[1] == "A")
		{
			if (line[2] == "A")
			{
				reg.set_A(reg.get_A() * reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_A(reg.get_A() * reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_A(reg.get_A() * reg.get_C());
			}
			else
			{
				reg.set_A(reg.get_A() * stoi(line[2]));
			}
		}
		else if (line[1] == "B")
		{
			if (line[2] == "A")
			{
				reg.set_B(reg.get_B() * reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_B(reg.get_B() * reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_B(reg.get_B() * reg.get_C());
			}
			else
			{
				reg.set_B(reg.get_B() * stoi(line[2]));
			}
		}
		else if (line[1] == "A")
		{
			if (line[2] == "A")
			{
				reg.set_C(reg.get_C() * reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_C(reg.get_C() * reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_C(reg.get_C() * reg.get_C());
			}
			else
			{
				reg.set_C(reg.get_C() * stoi(line[2]));
			}
		}
	}

	else if (line[0] == "JC")
	{
		if (reg.get_C() != 0)
			reg.set_licznik(stoi(line[1]));
	}

	else if (line[0] == "JZ")
	{
		if (reg.get_C() == 0)
			reg.set_licznik(stoi(line[1]));
	}

	else if (line[0] == "JL")
	{
		if (reg.get_C() < 0)
			reg.set_licznik(stoi(line[1]));
	}

	else if (line[0] == "JP")
	{
		reg.set_licznik(stoi(line[1]));
	}

	else if (line[0] == "JM")
	{
		if (reg.get_C() > 0)
			reg.set_licznik(stoi(line[1]));
	}

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

	else if (line[0] == "CF")
	{
		//Tworzy pusty plik
		//bool FileM::CreateFile(const std::string& name)
		cout << "Tworzenie pliku wyjsciowego o nazwie: " << line[1] << endl;
		{
			/*
			fstream plik;
			plik.open(line[1], ios::out);
			plik.close();
			*/
		}
	}

	else if (line[0] == "AF")
	{
		//zapisz tresc do pliku o podanej nazwie
		//bool WriteFile(const std::string& name, const std::string& tresc);
		/*
		fstream plik;
		plik.open(line[1], ios::app);
		plik << (char)stoi(line[2]);
		plik.close();
		*/
	}

	else if (line[0] == "AR")
	{
		if (line[2] == "A")
		{
			//zapisz tresc do pliku o podanej nazwie
			//bool WriteFile(const std::string& name, const std::string& tresc);
		}
		else if (line[2] == "B")
		{
			//zapisz tresc do pliku o podanej nazwie
			//bool WriteFile(const std::string& name, const std::string& tresc);
		}
		else if (line[2] == "C")
		{
			//zapisz tresc do pliku o podanej nazwie
			//bool WriteFile(const std::string& name, const std::string& tresc);
		}
	}

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

	else if (line[0] == "DC")
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

	else if (line[0] == "PS")		// Tworzy proces
	{
		//ProcessManager::GetInstance().CreateProcess(line[1],line[2], stoi(line[3]));
	}

	else if (line[0] == "PO")		// Otwiera proces
	{

	}

	else if (line[0] == "PC")		//Zamyka proces
	{

	}

	else if (line[0] == "PD")		//Kasuje proces
	{
		//ProcessManager::GetInstance().KillProcess(line[1]);
	}

	else if (line[0] == "FO")
	{
		//otwiera plik
		//bool FileM::OpenFile(const std::string& name);
	}

	else if (line[0] == "FC")
	{
		//zamyka plik
		//bool FileM::CloseFile(const std::string& name);
	}

	else if (line[0] == "DF")
	{
		//kasuje plik
		//bool FileM::DeleteFile(const std::string& name)
	}

	else if (line[0] == "PF")
	{
		//wyswietla plik
		//bool FileM::PrintFile(const std::string& name)
	}

	else if (line[0] == "SF")
	{
		//zmienia nazwe pliku
		//bool FileM::ReplaceNewName(const std::string& name, const std::string& name2);
	}

	else if (line[0] == "NP")
	{
		//nic nie robi!
	}

	else if (line[0] == "EX")		//Koniec programu
	{
		reg.set_licznik(-1);
		cout << "Koniec programu ";
	}
	else
	{
		std::cout << "\nNierozpoznano rozkazu " << line[0];
	}
}

//do tej funkcji dostaje stringa od Kacpra po tym jak ustalimy juz ile argumentow rozkaz i dostaje go calego xd
void Assembler::runProgram(Assembler& reg)
{
	string com = reg.commands[reg.licznikLine];
	runCommand(com, reg);
	reg.licznikLine++;
}
/*
int main()
{
	Assembler reg;
	string program;
	cout << "\nPodaj program: ";
	getline(cin, program);


	reg.savefile(program, reg);
	//reg.runCommand(reg);
	reg.runProgram(reg);
	reg.runProgram(reg);
	system("pause");
	return 0;

}
*/
