#pragma once
#include <map>
#include <vector>
#include <string>

class Shell {
private:

	enum class commands{
		step, cf, df, op, cl, sf, pf, ovf,

		ls, cd, md, rd, move,

		sb, sd,
		
		mem,
		
		wmem,
		
		cp, load, lp, kp,
		
		help,
		
		sh
	};

private:

	std::map<std::string, commands> commands = {
		{"step",commands::step},
		{"cf",commands::cf},
		{"df",commands::df},
		{"op",commands::op},
		{"cl",commands::cl},
		{"sf",commands::sf},
		{"pf",commands::pf},
		{"ovf",commands::ovf},
		
		{"ls",commands::ls},
		{"cd",commands::cd},
		{"md",commands::md},
		{"rd",commands::rd},
		{"move",commands::move},

		{"sb",commands::sb},
		{"sd",commands::sd},

		{"mem",commands::mem},

		{"wmem",commands::wmem},

		{"cp",commands::cp},
		{"load",commands::load},
		{"lp",commands::lp},
		{"kp",commands::kp},

		{"help",commands::help},

		{"sh",commands::sh}
	};

	std::map<std::string, std::string> helpdesk = {
		{"step","step - wykonanie nastepnego rozkazu przez interpreter polecen\n"},
		{"cf","cf [nazwa_pliku] - tworzy plik\n"},
		{"df","df [nazwa_pliku] - usuwa plik\n"},
		{"op","op [nazwa_pliku][tryb] - otwiera plik w trybie (-r) odczytu lub (rw) odczytu i zapisu\n"},
		{"cl","cl [nazwa_pliku] - zamyka otwarty plik\n"},
		{"pf","pf [nazwa_pliku] - wyswietla atrybuty pliku o podanej nazwie\n"},
		{"sf","sf [nazwa_pliku] - sprawdza, czy plik o podanej nazwie istnieje\n"},
		{"ovf","ovf [nazwa_pliku] - nadpisuje plik o podanej nazwie\n"},

		{"ls","ls [nazwa_katalogu] - wyswietla zawartosc katalogu o podanej nazwie lub biezacego katalogu, gdy nazwa nie jest podana\n"},
		{"cd","cd [nazwa_katalogu] - wyswietla nazwe biezacego katalogu lub zmienia go\n"},
		{"md","md [nazwa_katalogu] - tworzy katalog\n"},
		{"rd","rd [nazwa_katalogu] - usuwa katalog\n"},
		{"move","move [sciezka][nowa_sciezka] - zmienia sciezke do pliku\n"},

		{"sb","sb [numer_bloku] - wyswietla zawartosc bloku dyskowego\n"},
		{"sd","sd - wyswietla zawartosc dysku\n"},

		{"mem","mem - wyswietla aktualny stan pamieci RAM\n"},

		{"wmem","wmem - wyswietla plik pamieci wirtualnej\n"},

		{"cp","cp [nazwa_procesu] - tworzy nowy proces\n"},
		{"load","load [nazwa_procesu][nazwa_pliku] - wczytuje program do procesu\n"},
		{"lp","lp - wyswietla liste utworzonych procesow\n\n"},
		{"kp","kp - zamyka proces\n"},

		{"help","help - wyswietla wszystkie dostepne komendy\n"},

		{"sh","shutdown - zamyka system\n"}
	};

	bool is_running = true;				// flaga dzia�ania systemu
	std::string input;					// pobrana linia
	std::vector<std::string> command;	// wektor przechowujacy komende i jej arumenty

	void create_command();				// zapisuje do wektora nazwe komendy i jej argumenty
	void help();						// wyswietla wszystkie komendy
	void perform_command();				// wykonuje komende
	void check_change_state();			// sprawdza zmiany zmiennej change_state

	std::string arguments = "Niepoprawna liczba argumentow!\n";
	std::string system_name = "<PUT-OS> ";

public:

	void run();							// uruchomienie programu

};