#include "pch.h"
#include "Shell.h"
#include "RAM.h"
#include "Assembler.h"
#include "CPU.h"
#include "ProcessManager.h"
#include "Semaphore.h"
#include "VirtualMemory.h"
#include "FileSystem.h"
#include <iostream>

extern int change_state;

void Shell::create_command() {

	command.clear();

	command.emplace_back();

	bool texty = 0;

	while (!input.empty()) {
		if (texty) {
			command.back().push_back(input[0]);
			input.erase(input.begin());
			if (input.front() == '\"') {
				input.erase(input.begin());
				if (texty)
					texty = 0;
				else
					texty = 1;
				continue;
			}
		}
		else {
			if (input.front() == ' ') {
				while(!input.empty() && input.front() == ' ')
					input.erase(input.begin());
				command.emplace_back();
			}
			if (input.empty()) {
				command.pop_back();
				break;
			}
			if (input.front() == '\"') {
				input.erase(input.begin());
				if (texty)
					texty = 0;
				else
					texty = 1;
				continue;
			}
			command.back().push_back(input[0]);
			input.erase(input.begin());
		}
	}
}

void Shell::help() {

	std::cout << system_name << "Dostepne komendy:\n\n";

	std::cout << "[command] -h - wyswietla pomoc dla wybranej komendy\n\n";

	for (const auto &e : helpdesk)
	{
		std::cout << e.second;
	}
}

void Shell::perform_command() {

	// PRACA KROKOWA
	if (!komendy.count(command[0])) {
		std::cout << system_name << "Nie rozpoznano tej komendy.";
	}
	else {
		switch (komendy[command[0]]) {

		case commands::step:
			switch (command.size())
			{
			case 1:
				// metoda wykonująca kolejny rozkaz przez interpreter polecen
				Assembler::GetInstance().runProgram();
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
					// metoda tworząca plik
					FileSystem::GetInstance().create(command[1]);
					std::cout << system_name << "Utworzono plik " << command[1] << ".\n";
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::df:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					// metoda tworząca plik
					FileSystem::GetInstance().remove(command[1]);
					std::cout << system_name << "Usunieto plik " << command[1] << ".\n";
				}
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
					std::cout<<"\n"<<FileSystem::GetInstance().read_all(command[1])<<"\n";
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::cl:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					FileSystem::GetInstance().close(command[1]);
					std::cout << system_name << "Zamknieto plik " << command[1] << "\n";
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::sf:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					if (FileSystem::GetInstance().exists(command[1])) { // w warunku metoda zwracajaca bool wyszukujaca nazwy pliku w tablicy FAT

						std::cout << "Plik o nazwie \"" << command[1] << "\" istnieje\n";
					}
					else {
						std::cout << "Plik o nazwie \"" << command[1] << "\" nie istnieje\n";
					}
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::pf:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					// metoda wyswietlajaca atrybuty pliku

				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::ef:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else
					std::cout << system_name << arguments;
				break;
			case 4:
				// metoda edytujaca plik
				if (command[2] == ">>")
					FileSystem::GetInstance().write(command[3], command[1], true); // dopisywanie
				else if (command[2] == ">")
					FileSystem::GetInstance().write(command[3], command[1], false); // nadpisywanie
				else
					std::cout << system_name << arguments;
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::sem:

			switch (command.size()) {
			case 1:
				//FileSystem::GetInstance().print_semaphores();
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else
					std::cout << system_name << arguments;
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

			// KATALOGI

		case commands::ls:

			switch (command.size()) {
			case 1:
				std::cout << system_name << "Wyswietlenie zawartosci folderu.\n";
				// metoda wyswietlajaca zawartosc folderu
				FileSystem::GetInstance().print_files();
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

		case commands::md:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					// metoda tworzaca katalog

					std::cout << system_name << "Utworzono katalog " << command[1] << ".\n";
				}
				break;
			default:
				std::cout << system_name << arguments;
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
					std::cout << system_name << "Usunieto katalog" << command[1] << ".\n";
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::move:

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
				// metoda zmieniajaca nazwe lub sciezke pliku
				FileSystem::GetInstance().set_file_name(command[1], command[2]);
				std::cout << system_name << "Plik " << command[1] << " ma nowa nazwe " << command[2] << ".\n";
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

			// DYSK

		case commands::sb:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else if (std::stoi(command[1]) >= 0) {
					std::cout << system_name << "Wyswietlenie zawartosci bloku.\n";
					// metoda wyswietlajaca zawartosc bloku dyskowego
				}
				else {
					std::cout << system_name << arguments;
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::sd:

			switch (command.size()) {
			case 1:
				std::cout << system_name << "Wyswietlenie zawartosci dysku.\n";
				// metoda wyswietlajaca zawartosc calego dysku
				FileSystem::GetInstance().print_data();
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

		case commands::sfat:

			switch (command.size()) {
			case 1:
				std::cout << system_name << "Wyswietlenie informacji o fat.\n";
				// metoda wyswietlajaca zawartosc calego dysku
				FileSystem::GetInstance().print_fat();
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

			// PAMIEC RAM

		case commands::mem:

			switch (command.size()) {
			case 1:
				std::cout << system_name << "Wyswietlenie aktualnego stanu pamieci RAM.\n";
				RAM::GetInstance().show_RAM();
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

		case commands::cmem:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout << system_name << "Wyswietlenie komorki " << command[1] << " w RAM\n";
					std::cout<< RAM::GetInstance().char_RAM(std::stoi(command[1])) << "\n";
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		// PAMIEC WIRTUALNA

		case commands::vmem:

			switch (command.size()) {
			case 1:
				std::cout << system_name << "Wyswietlenie pliku wymiany.\n";
				// metoda wyswietlajaca plik wymiany
				VirtualMemory::GetInstance().display_pagefile();
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

		case commands::cvmem:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					std::cout << system_name << "Wyswietlenie danych w pamieci wrtualnej dla procesu " << command[1] << "\n";
					VirtualMemory::GetInstance().display_segment_tab(ProcessManager::GetInstance().GetProcess(command[1]));
				}
				break;
			default:
				std::cout << system_name << arguments;
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
			case 4:
				//metoda tworzaca proces z programem
				ProcessManager::GetInstance().CreateProcess(command[1], command[2], std::stoi(command[3]));
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::kp:

			switch (command.size()) {
			case 2:
				if (command[1] == "-h") {
					std::cout << helpdesk[command[0]];
				}
				else {
					ProcessManager::GetInstance().KillProcess(command[1]);
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::load:

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
				// metoda ladujaca program do procesu
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;

		case commands::lp:

			switch (command.size()) {
			case 1:
				// metoda wyswietlajaca wszystkie istniejace procesy
				ProcessManager::GetInstance().PrintProcesses();
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
					std::cout << system_name << arguments;
				}
				break;
			default:
				std::cout << system_name << arguments;
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
					std::cout << system_name << arguments;
				}
				break;
			default:
				std::cout << system_name << arguments;
			}
			break;
		}
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
		try {
			std::cout << "\nconsole: ";
			getline(std::cin, input);

			create_command();
			perform_command();
		}
		catch (std::exception & e) {
			std::cout << "\n" << e.what() << "\n";
		}
	}
}