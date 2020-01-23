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
	 if (program == " " || program == "") // gdy pusto po .text ? XOXO
		 return;
	 int o = program.size();
	 if (program[o] != ' ')
	 {
		 program += " ";
	 }
	string pom_com = "";
	string com = "";
	int pom1 = reg.get_licznik();
	int pom2 = reg.get_licznik() + 1;
	com = program[pom1];
	com += program[pom2];
	int i, j;
	if (reg.ile_arg(com)==-1)
	{
		std::cout << "\nNierozpoznano komendy!";
		reg.set_licznik(reg.get_licznik() + 3);
		return;
	}
	for (i = reg.get_licznik(), j = 0; j < reg.ile_arg(com)+1; i++)
	{
		if (program[i] == ' ')
		{
			j++;
		}
		pom_com += program[i];
	}

	try
	{
		reg.runCommand(pom_com, reg);
	}
	catch(std::exception& e)
	{
		std::cout << "\n" << e.what() << "\n";
	}
	if (com == "JP" || com == "JC" || com == "JZ" || com == "JL" || com == "JM" || com=="NP")
	{
		reg.set_licznik(reg.get_licznik());
	}
	else
	{	
		int a1 = reg.get_licznik();
		int a2 = reg.countLine(pom_com);
		reg.set_licznik(a1+a2);
//		reg.set_licznik(reg.get_licznik());
	}

}

int Assembler::countLine(std::string line)
{
	licznik = 0;
	for (int i = 0; i < line.size(); i++)
	{
			licznik++;
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
	else if (command == "PN")
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
	else if (command == "WF")
		return 2;
	else if (command == "AR")
		return 2;
	else if (command == "RF")
		return 1;
	else if (command == "PF")
		return 1;
	else if (command == "PC")
		return 3;
	else if (command == "PD")
		return 1;
	else
	{
	//	std::cout << "\nNierozpoznano komendy w ILE_ARG!";
		return -1;
	}
}
void toJump()
{
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
	string l1 = line[0];
	string l2 = line[1];
	string l3 = line[2];
	string l4 = line[3];
	string ss = line[0] + line[1] + line[2] + line[3];
	
	if (line[0] == "MV")
	{
		if (line[1] == "A")
		{

			if (line[2] == "A")
			{

			}
			else if (line[2] == "B")
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_A(stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
				}

			}

		}
		else if (line[1] == "B")
		{
			if (line[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (line[2] == "B")
			{

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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_B(stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
			else if (line[2] == "C")
			{

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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_C(stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
				}
			}
		}

		else if (line[1] == "D")
		{
			if (line[2] == "A")
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
			else if (line[2] == "D")
			{
			
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_D(stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_A(reg.get_A() + stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_B(reg.get_B() + stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() + stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_D(reg.get_D() + stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_A(reg.get_A() - stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_B(reg.get_B() - stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() - stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_D(reg.get_D() - stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_A(reg.get_A() * stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_B(reg.get_B()* stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() * stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_D(reg.get_D() * stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
				}
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
				else if (x[0] >= '0' && x[0] <= '9')
				{
					reg.set_C(reg.get_C() * stoi(x));
				}
				else
				{
					std::cout << "\nBledne argumenty!";
					return;
				}
			}
		}
	}
	

	else if (line[0] == "JP")
	{
		reg.set_licznik(stoi(line[1]));
	}


	else if (line[0] == "JC")
	{
		if (reg.get_C() > 0)
			reg.set_licznik(stoi(line[1]));
		else
			reg.set_licznik(reg.get_licznik() + reg.countLine(c_line));
	}


	else if (line[0] == "JZ")
	{
		if (reg.get_C() == 0)
			reg.set_licznik(stoi(line[1]));
		else
			reg.set_licznik(reg.get_licznik() + reg.countLine(c_line));
	}


	else if (line[0] == "JL")
	{
		if (reg.get_C() < 0)
			reg.set_licznik(stoi(line[1]));
		else
			reg.set_licznik(reg.get_licznik() + reg.countLine(c_line));
	}

	else if (line[0] == "JM")
	{
		if (reg.get_C() > 0)
			reg.set_licznik(stoi(line[1]));
		else
			reg.set_licznik(reg.get_licznik() + reg.countLine(c_line));
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
		else
		{
			std::cout << "\nBledne argumenty!";
			return;
		}
	}


	else if (line[0] == "CF")
	{
		FileSystem::GetInstance().create(line[1]);
	}

	else if (line[0] == "AF")
	{
		ProcessManager::GetInstance().WriteFile(ProcessManager::GetInstance().running_process(), line[1], line[2], true);
	}

	else if (line[0] == "WF")
	{
		ProcessManager::GetInstance().WriteFile(ProcessManager::GetInstance().running_process(), line[1], line[2], false);
	}

	else if (line[0] == "AR")
	{
		if (line[2] == "A")
		{
			int rej_A = reg.get_A();
			stringstream ss;
			ss << rej_A;
			string A = ss.str();
			ProcessManager::GetInstance().WriteFile(ProcessManager::GetInstance().running_process(), line[1], A,true);
		}
		else if (line[2] == "B")
		{
			int rej_B = reg.get_B();
			stringstream ss;
			ss << rej_B;
			string B = ss.str();
			ProcessManager::GetInstance().WriteFile(ProcessManager::GetInstance().running_process(), line[1], B,true);
		}
		else if (line[2] == "C")
		{
			int rej_C = reg.get_C();
			stringstream ss;
			ss << rej_C;
			string C = ss.str();
			ProcessManager::GetInstance().WriteFile(ProcessManager::GetInstance().running_process(), line[1], C);
		}
		else if (line[2] == "D")
		{
			int rej_D = reg.get_D();
			stringstream ss;
			ss << rej_D;
			string D = ss.str();
			ProcessManager::GetInstance().WriteFile(ProcessManager::GetInstance().running_process(), line[1], D);
		}
		else
		{
			std::cout << "\nBledne argumenty!";
			return;
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
		else
		{
			std::cout << "\nBledne argumenty!";
			return;
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
		else
		{
			std::cout << "\nBledne argumenty!";
			return;
		}
	}

	else if (line[0] == "PC")		// Tworzy proces
	{
		ProcessManager::GetInstance().CreateProcess(line[1],line[2], stoi(line[3]));
	}



	else if (line[0] == "PD")		//Kasuje proces
	{
		ProcessManager::GetInstance().KillProcess(line[1]);
	}

	else if (line[0] == "FO")
	{
		ProcessManager::GetInstance().OpenFile(ProcessManager::GetInstance().running_process(), line[1]);
	}

	else if (line[0] == "FC")
	{
		ProcessManager::GetInstance().CloseFile(ProcessManager::GetInstance().running_process(), line[1]);
	}

	else if (line[0] == "DF")
	{
		FileSystem::GetInstance().remove(line[1]);
	}

	else if (line[0] == "PF")					//BRAK CZYTANIA Z PLIKU
	{
		char rej_X = ProcessManager::GetInstance().ReadFileByte(ProcessManager::GetInstance().running_process(), line[1]);
		string rejX = "";
		rejX = rej_X;
		reg.set_D(stoi(rejX));
	}

	else if (line[0] == "RF")	
	{
	ProcessManager::GetInstance().ResetFilePointer(ProcessManager::GetInstance().running_process(),line[1]);
		//(line[1]);
	}

	else if (line[0] == "NP")
	{
		//nic nie robi!
	}


	else if (line[0] == "PN")
	{
	//nic nie robi!
	}

	else if (line[0] == "EX")		//Koniec programu
	{
		reg.set_licznik(int(-100));
		//cout << "Koniec programu ";
	}
	else
	{
		std::cout << "\nNierozpoznano rozkazu " << line[0];
		return;
	}
}

void Assembler::lastLineControl(Assembler& reg, Process* pcb)
{
	string program = "";
	program = pcb->text_segment();
	int sizeProgram = program.size();
	if (sizeProgram <= reg.get_licznik() || reg.get_licznik() < 0)
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
	reg.set_licznik(reg.get_licznik());
//	std::string name = process_run->name;
//	if (name != "Dummy") {
		process_run->set_instruction_counter(reg.get_licznik());
	lastLineControl(reg, process_run);
	//reg.print(reg);
}