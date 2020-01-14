#include <iostream>
#include "Shell.h"
#include "FileM.h"
#include "RAM.h"

extern FileM disc;
extern RAM ram;
extern int change_state;

void Shell::create_command() {

	command.clear();

	command.emplace_back();

	while (!input.empty()) {
		if (input.front() == ' ') {
			input.erase(input.begin());
			command.emplace_back();
		}
		command.back().push_back(input[0]);
		input.erase(input.begin());
	}
}

void Shell::help() {

	std::cout << system_name << "Dostepne komendy:\n\n";

	std::cout << "[command] -h - wyswietla pomoc dla wybranej komendy\n\n";

	for (auto &e : helpdesk)
	{
		std::cout << e.second;
	}
}

void Shell::perform_command() {

	// PRACA KROKOWA

	switch (commands[command[0]]) {

		case commands::step:
			switch (command.size())
			{
			case 1:
				// metoda wykonująca kolejny rozkaz przez interpreter polecen
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout << system_name << arguments;
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
		break;

	// PLIKI

		case commands::cf:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout << system_name << arguments;
				}
				break;
			case 3:
				// metoda tworząca plik
				std::cout << system_name << "Utworzono plik " << command[2] << ".\n";
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::op:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout <<  system_name  << arguments ;
				}
				break;
			case 3:
				if (command[2] == "rw" || command[2] == "r") {
					// metoda otwierająca plik
					std::cout <<  system_name  << "Otwarto plik.\n";
				}
				else {
					std::cout <<  system_name  << "Nieprawidlowy tryb otwarcia.\n" ;
				}
				break;
			default:
				std::cout <<  system_name  << arguments ;
			}
			break;

		case commands::cl:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					// metoda zamykajaca plik
					std::cout <<  system_name  << "Zamknieto plik.\n";
				}
				break;
			default:
				std::cout <<  system_name  << arguments ;
			}
			break;

		// KATALOGI

		case commands::ls:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << "Wyswietlenie zawartosci folderu.\n";
					// metoda wyswietlajaca zawartosc folderu
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		case commands::md:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			case 3:
				// metoda tworzaca katalog
				std::cout  << system_name  << "Utworzono katalog " << command[2] << ".\n";
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		case commands::rd:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					// metoda usuwajaca katalog
					std::cout  << system_name  << "Usunieto katalog" << command[1] << ".\n";
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;
		
		case commands::move:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			case 3:
				// metoda zmieniajaca nazwe lub sciezke pliku
				std::cout  << system_name  << "Plik " << command[1] << " ma nowa nazwe " << command[2] << ".\n";
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		case commands::sf:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					if (disc.InvestigateFile(command[1])) {
						std::cout << "Plik o nazwie \"" << command[1] << "\" istnieje\n";
					}
					else {
						std::cout << "Plik o nazwie \"" << command[1] << "\" nie istnieje\n";
					}
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}

		// DYSK

		case commands::sb:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else if (command[1] == "a" || command[1] == "h") {
					std::cout << system_name << "Wyswietlenie zawartosci bloku.\n";
					// metoda wyswietlajaca zawartosc calego dysku				
				}
				else {
					std::cout << system_name << arguments;
				}
				break;
			case 3:
				if (std::stoi(command[1]) >= 0) {
					std::cout << system_name << "Wyswietlenie bloku dyskowego.\n";
					// metoda wyswietlajaca zawartosc bloku dyskowego
				}
				else {
					std::cout << system_name << "Numer bloku musi byc liczba nieujemna.\n";
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		case commands::sd:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else if (command[1] == "a" || command[1] == "h") {
					std::cout << system_name << "Wyswietlenie zawartosci dysku.\n";
					// metoda wyswietlajaca zawartosc calego dysku				
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		// PAMIEC RAM

		case commands::mem:

			switch (command.size()) {
			case 1:
				std::cout  << system_name  << "Wyswietlenie aktualnego stanu pamieci RAM.\n";
				ram.show_RAM();			
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		// PAMIEC WIRTUALNA

		case commands::wmem:

			switch (command.size()) {
			case 1:
				std::cout  << system_name  << "Wyswietlenie pliku wymiany.\n";
				// metoda wyswietlajaca plik wymiany
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		// PROCESY

		case commands::cp:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout << system_name << arguments;
				}
				break;
			case 3:
				//metoda tworzaca proces z programem
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		case commands::load:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			case 3:
				// metoda ladujaca program do procesu
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		case commands::lp:

			switch (command.size()) {
			case 1:
				// metoda wyswietlajaca wszystkie istniejace procesy
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		// HELP

		case commands::help:

			switch (command.size()) {
			case 1:
				help();
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		// EXIT

		case commands::sh:

			switch (command.size()) {
			case 1:
				is_running = false;
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout  << system_name  << arguments ;
				}
				break;
			default:
				std::cout  << system_name  << arguments ;
			}
			break;

		// ERROR

		default:
			std::cout << system_name << "Nie rozpoznano tej komendy.";
	}
}

void Shell::check_change_state()
{
	if (change_state == 0) {
		return;
	}
	else if (change_state == 2) { 
		// proces przeszedl w stan ready
	}
	else if (change_state == 3) {
		// proces przeszedl w stan waiting
	}
	else if (change_state == 4) {
		// proces przeszedl w stan terminated
	}
}

void Shell::run() {

	std::cout << "<----------PUT-OS---------->\n\n";
	std::cout << "\nAby wyswietlic pomoc, wpisz komende 'help'.\n";

	while (is_running) {

		std::cout << "\nconsole: ";
		getline(std::cin, input);

		create_command();
		perform_command();
	}
}