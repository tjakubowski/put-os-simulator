#include <iostream>
#include "Shell.h"

//PCB *p1 = new PCB(1);
int licznik = 0;

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

unsigned short Shell::stous(std::string str) {
	return (unsigned short)std::stoi(str);
}

bool Shell::stob(std::string str) {
	if (str == "rw") return true; // rw - read and write
	else if (str == "r") return false; // r - read only
}

void Shell::help() {

	std::cout << system_name << "Dostepne komendy:\n\n";

	// -h

	std::cout << "[command] -h - wyswietla pomoc dla wybranej komendy\n\n";

	// PRACA KROKOWA

	std::cout << "ENTER - wykonanie nastepnego rozkazu przez interpreter polecen\n\n";

	// PLIKI

	std::cout << "cf - tworzy plik\n"; // [nazwa_pliku]
	std::cout << "op - otwiera plik\n"; // [nazwa_pliku][tryb]	open_type == (r | rw)
	std::cout << "cl - zamyka otwarty plik\n"; // [file_name]
	std::cout << "rds - read sequential (odczytywanie z pliku sekwencyjnie)\n"; // [file_name][bytes_amount]
	std::cout << "rdi - read index (odczytywanie z pliku indeksowo)\n"; // [file_name][byte_number_in_file][bytes_amount]
	std::cout << "wrts - write sequential (zapisywanie do pliku sekwencyjnie)\n"; // [folder_name][data]
	std::cout << "wrti - write index (zapisywanie do pliku indeksowo)\n"; // [file_name][data][byte_number_in_file]
	
	// KATALOGI

	std::cout << "ls - wyswietla zawartosc katalogu\n"; // [nazwa_katalogu]
	std::cout << "cd - wyswietla nazwe biezacego katalogu lub zmienia go\n"; // [nazwa_katalogu]
	std::cout << "md - tworzy katalog\n"; // [nazwa_katalogu]
	std::cout << "rd - usuwa katalog\n"; // [nazwa_katalogu]
	std::cout << "move - zmienia sciezke do pliku\n"; // [nazwa_pliku][nowa_nazwa]
	std::cout << "fds - file/directory search (szukanie pliku/katalogu)\n\n"; // [nazwa_pliku]

	// DYSK

	std::cout << "sb [numer_bloku] [tryb] - wyswietlenie zawartosci bloku dyskowego\n"; // [numer_bloku] [tryb] tryb == (a | h) ASCII | HEXADECIMAL
	std::cout << "sd [tryb] - wyswietlenie zawartosci dysku\n"; // [tryb] tryb == (a | d) ASCII | HEXADECIMAL

	// PAMIEC RAM

	std::cout << "mem - wyswietlenie aktualnego stanu ramu\n\n"; // []

	// PAMIEC WIRTUALNA

	std::cout << "wmem - wyswietlenie pliku wymiany\n"; // []

	// PROCESY

	std::cout << "cp - tworzy nowy proces\n"; // [nazwa_procesu] [nazwa_pliku]
	std::cout << "load - wczytuje program do procesu\n"; // [nazwa_procesu] [nazwa_pliku]
	std::cout << "lp – wyswietla liste utworzonych procesow\n\n"; // []
	std::cout << "kp – zamyka proces\n\n"; // []

	// HELP

	std::cout << "help - wyswietla wszystkie dostepne komendy\n"; // []

	// SHUTDOWN

	std::cout << "shutdown - zamyka system\n"; // []
}

void Shell::perform_command() {

	// PRACA KROKOWA

	if (command.empty()) {

		// metoda interpretera polecen wykonujaca kolejny rozkaz

		return;
	}

	switch (commands[command[0]]) {

	// PLIKI

		case commands::cf:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << "\n" << command[0] << " " << "[folder_name][file_name]\n";
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
					std::cout << "\n" << command[0] << " " << "[nazwa_pilku][tryb]	tryb == (r | rw)\n";
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
					std::cout << "\n" << command[0] << " " << "[file_name]\n";
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
					std::cout << "\n" << command[0] << " " << "[folder_name]\n";
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
					std::cout << "\n" << command[0] << " " << "[folder_name][folder_to_create_name]\n";
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
					std::cout << "\n" << command[0] << " " << "[folder_name]\n";
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
					std::cout << "\n" << command[0] << " " << "[file_name][new_file_name]\n";
					
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

		/*case commands::fds:

			if (command.size() == 2) {

				if (command[1] == "-h") {
					std::cout << "\n" << command[0] << " " << "[file_name]\n";
				}
				else {
					short int num = fsearch(command[1], 0);

					if (num < 0) {
						std::cout  << system_name  << "Nie znaleziono pliku.\n" ;
					}
					else {
						std::cout  << system_name  << "Numer i-wezla wskazanego pliku to: " << num << std::endl;
					}
				}
			}
			else {
				std::cout  << system_name  << arguments ;
			}*/

		// DYSK

		case commands::sb:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << "\n" << command[0] << " [numer_bloku][tryb]\n";
					std::cout << "[tryb]: a - wyswietla za pomoca znakow ASCII, h - wyswietla za pomoca kodu szesnastkowego\n";
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
					std::cout << "\n" << command[0] << " [tryb]\n";
					std::cout << "[tryb]: a - wyswietla za pomoca znakow ASCII, h - wyswietla za pomoca kodu szesnastkowego\n";
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
				// metoda wyswietlajaca pamiec RAM
			
				break;
			case 2:
				if (command[1] == "-h") {
					std::cout << "\n" << command[0] << " " << "[]\n";
					std::cout << "[] - brak argumentow\n";
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
					std::cout << "\n" << command[0] << " " << "[]\n";
					std::cout << "[] - brak argumentow\n";
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
					std::cout << "\n" << command[0] << " " << "[nazwa_procesu][nazwa_pliku]\n";
					std::cout << "[nazwa_pliku] - plik zawierajacy program\n";
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
					std::cout << "\n" << command[0] << " " << "[nazwa_procesu][nazwa_pliku]\n";
					std::cout << "[nazwa_pliku] - plik zawierajacy program\n";
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
					std::cout << "\n" << command[0] << " []\n";
					std::cout << "[] - brak argumentow\n";
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
					std::cout << "\n" << command[0] << " " << "[]\n";
					std::cout << "[] - brak argumentow\n";
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
					std::cout << "\n" << command[0] << " " << "[]\n";
					std::cout << "[] - brak argumentow\n";
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