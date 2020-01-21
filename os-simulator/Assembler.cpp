#include "pch.h"
#include "Assembler.h"
#include "FileSystem.h"

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

short int Assembler::get_D()
{
	return registerD;
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

void Assembler::set_D(short int v)
{
	registerD = v;
}

int Assembler::get_licznik()
{
	return licznik;
}

void Assembler::set_licznik(int v)
{
	licznik = v;
}

void Assembler::saveFile(Assembler& reg, Process* pcb)
{
 string program = pcb->text_segment();
	string pom_com = "";
	string com = "";
	int pom1 = reg.get_licznik();
	int pom2 = reg.get_licznik() + 1;
	com = program[pom1];
	com += program[pom2];
	int i, j;
	for (i = reg.get_licznik(), j = 0; j < reg.ile_arg(com)+1; i++)
	{
		if (program[i] == ' ')
		{
			j++;
		}
		pom_com += program[i];
	}
	reg.runCommand(pom_com, reg);
	reg.set_licznik(reg.countLine(pom_com) + 2);
}

int Assembler::countLine(std::string line)
{
	int licznik = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')
		{
			licznik++;
		}
	}
	return licznik;
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
	else if (command == "FP")
		return 1;
	else if (command == "PC")
		return 3;
	else if (command == "PW")
		return 1;
	else if (command == "PR")
		return 1;
	else if (command == "RP")
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
	cout <<"Wykonuje rozkaz " << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << endl;

	string ss = line[0] + line[1] + line[2] + line[3];
	int size_ss = ss.size();
	reg.set_licznik(reg.get_licznik() + size_ss);

	if (line[0] == "MV")
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
			else if (line[2] == "D")
			{
				reg.set_A(reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_A(stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_A(stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_B(reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_B(stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_B(stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_C(reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_C(stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_C(stoi(x));
				}
			}
		}

		else if (line[1] == "C")
		{
			if (line[2] == "D")
			{
				reg.set_D(reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_D(reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_D(reg.get_C());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_D(stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_D(stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_A(reg.get_A() + reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_A(reg.get_A() + stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_A(reg.get_A() + stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_B(reg.get_B() + reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_B(reg.get_B() + stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_B(reg.get_B() + stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_C(reg.get_C() + reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_C(reg.get_C() + stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() + stoi(x));
				}
			}
		}
		else if (line[1] == "D")
		{

			if (line[2] == "A")
			{
				reg.set_D(reg.get_D() + reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_D(reg.get_D() + reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_D(reg.get_D() + reg.get_C());
			}
			else if (line[2] == "D")
			{
				reg.set_D(reg.get_D() + reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_D(reg.get_D() + stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}	
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_D(reg.get_D() + stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_A(reg.get_A() - reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_A(reg.get_A() - stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_A(reg.get_A() - stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_B(reg.get_B() - reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_B(reg.get_B() - stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_B(reg.get_B() - stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_C(reg.get_C() - reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_C(reg.get_C() - stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() - stoi(x));
				}
			}
		}
		else if (line[1] == "D")
			{
			if (line[2] == "A")
			{
				reg.set_D(reg.get_D() - reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_D(reg.get_D() - reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_D(reg.get_D() - reg.get_C());
			}
			else if (line[2] == "D")
			{
				reg.set_D(reg.get_D() - reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_D(reg.get_D() - stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}	
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_D(reg.get_D() - stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_A(reg.get_A() * reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_A(reg.get_A() * stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_A(reg.get_A() * stoi(x));
				}
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
			else if (line[2] == "D")
			{
				reg.set_B(reg.get_B() * reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_B(reg.get_B()* stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_B(reg.get_B()* stoi(x));
				}
			}
		}
		else if (line[1] == "C")
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
			else if (line[2] == "D")
			{
				reg.set_C(reg.get_C() * reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_C(reg.get_C() * stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() * stoi(x));
				}
			}
		}
		else if (line[1] == "D")
		{
		if (line[2] == "A")
			{
				reg.set_D(reg.get_D() * reg.get_A());
			}
			else if (line[2] == "B")
			{
				reg.set_D(reg.get_D() * reg.get_B());
			}
			else if (line[2] == "C")
			{
				reg.set_D(reg.get_D() * reg.get_C());
			}
			else if (line[2] == "D")
			{
				reg.set_D(reg.get_D() * reg.get_D());
			}
			else
			{
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_D(reg.get_D() * stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_D(reg.get_D() * stoi(x));
				}
			}
		}
		//
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
				string x = line[2];
				string xy = "";
				if (x[0] == '[' && x[x.size() - 1] == ']')
				{
					for (int o = 1; o < x.size() - 1; o++)
					{
						xy += x[o];
					}
					reg.set_C(reg.get_C() * stoi(RAM::GetInstance().char_RAM(stoi(xy))));
				}
				else if (x[0] > '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() * stoi(x));
				}
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

	//Odczytywanie rejestrów?
	else if (line[0] == "PR")
	{
		if (line[1] == "A")
		{
			std::cout << "\nRejestr " << line[1] << ": " << reg.get_A();
		}
		else if (line[1] == "B")
		{
			std::cout << "\nRejestr " << line[1] << ": " << reg.get_B();
		}
		else if (line[1] == "C")
		{
			std::cout << "\nRejestr " << line[1] << ": " << reg.get_C();
		}
		else if (line[1] == "D")
		{
			std::cout << "\nRejestr " << line[1] << ": " << reg.get_D();
		}
	}


	else if (line[0] == "CF")
	{
		FileSystem::GetInstance().create(line[1]);
	}

	else if (line[0] == "AF")
	{
		FileSystem::GetInstance().write(line[1], line[2]);
	}

	else if (line[0] == "AR")
	{
		if (line[2] == "A")
		{
			int rej_A = reg.get_A();
			stringstream ss;
			ss << rej_A;
			string A = ss.str();
			FileSystem::GetInstance().write(line[1], A);

		}
		else if (line[2] == "B")
		{
			int rej_B = reg.get_B();
			stringstream ss;
			ss << rej_B;
			string B = ss.str();
			FileSystem::GetInstance().write(line[1], B);
		}
		else if (line[2] == "C")
		{
			int rej_C = reg.get_C();
			stringstream ss;
			ss << rej_C;
			string C = ss.str();
			FileSystem::GetInstance().write(line[1], C);
		}
		else if (line[2] == "D")
		{
			int rej_D = reg.get_D();
			stringstream ss;
			ss << rej_D;
			string D = ss.str();
			FileSystem::GetInstance().write(line[1], D);
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
		else if (line[1] == "D")
		{
			reg.set_D(reg.get_D() + 1);
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
		else if (line[1] == "D")
		{
			reg.set_D(reg.get_D() - 1);
		}
	}

	else if (line[0] == "PC")		// Tworzy proces
	{
		ProcessManager::GetInstance().CreateProcess(line[1],line[2], stoi(line[3]));
	}

	else if (line[0] == "PW")		// Process Waiting
	{
		ProcessManager::GetInstance().SetProcessWaiting(line[1]);
	}

	else if (line[0] == "PR")		// Process ready
	{
		ProcessManager::GetInstance().SetProcessReady(line[1]);
	}

	else if (line[0] == "RP")		// Process Running
	{
	ProcessManager::GetInstance().SetProcessRunning(line[1]);
	}

	else if (line[0] == "PD")		//Kasuje proces
	{
		ProcessManager::GetInstance().KillProcess(line[1]);
	}

	else if (line[0] == "FO")
	{
		
	// Otwieranie pliku !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WROC TU
	//	FileSystem::GetInstance().OpenFile(line[1]);
	}

	else if (line[0] == "FC")
	{
		FileSystem::GetInstance().close(line[1]);
	}

	else if (line[0] == "DF")
	{
		FileSystem::GetInstance().remove(line[1]);
	}

	else if (line[0] == "PF")
	{
		//FileSystem::GetInstance().PrintFile(line[1]);
		// todo: call print single file
	}

	else if (line[0] == "SF")
	{
		FileSystem::GetInstance().set_file_name(line[1], line[2]);
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

void Assembler::lastLineControl(Assembler& reg, Process* pcb)
{
	string program = "";
	program = pcb->text_segment();
	int sizeProgram = program.size();
	if (sizeProgram <= reg.get_licznik())
	{
		ProcessManager::GetInstance().KillProcess(pcb);
	}
}

void Assembler::print(Assembler& reg)
{
	std::cout << "\n------------------";
	std::cout << "\nRejestry:";
	std::cout << "\nA		" << reg.get_A();
	std::cout << "\nB		" << reg.get_B();
	std::cout << "\nC		" << reg.get_C();
	std::cout << "\nD		" << reg.get_D();
	std::cout << "\nLinia	" << reg.get_licznik();
	std::cout << "\n------------------";
}

//do tej funkcji dostaje stringa od Kacpra po tym jak ustalimy juz ile argumentow rozkaz i dostaje go calego xd
void Assembler::runProgram()
{
	Assembler reg;
	auto process_run = ProcessManager::GetInstance().running_process(); // wykonywany proces process_run
	reg.set_A(process_run->ax());
	reg.set_B(process_run->bx());
	reg.set_C(process_run->cx());
	reg.set_D(process_run->dx());
	reg.set_licznik(process_run->instruction_counter());
	reg.saveFile(reg, process_run);

	process_run->set_ax(reg.get_A());
	process_run->set_bx(reg.get_B());
	process_run->set_cx(reg.get_C());
	process_run->set_dx(reg.get_D());
	//get_licznik jest wczesniej zrobione w funkcji countLine
	reg.print(reg);
	//sprawdzenie czy ostatnia linia
	lastLineControl(reg,process_run);
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
