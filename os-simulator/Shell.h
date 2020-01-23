#pragma once
#include <map>
#include <vector>
#include <string>

class Shell {
private:

	enum class commands{
		step, cf, df, op, sf, pf, ef, copy,

		sem,

		ls, rn,

		sd, sfat,
		
		mem, cmem,
		
		vmem, cvmem,
		
		cp, load, lp, kp, of, setp,
		
		help,
		
		sh
	};

private:

	std::map<std::string, commands> komendy = {
		{"step",commands::step},

		{"cf",commands::cf},
		{"df",commands::df},
		{"op",commands::op},
		{"sf",commands::sf},
		{"pf",commands::pf},
		{"ef",commands::ef},
		{"copy",commands::copy},

		{"sem",commands::sem},
		
		{"ls",commands::ls},
		{"rn",commands::rn},

		{"sd",commands::sd},
		{"sfat",commands::sfat},

		{"mem",commands::mem},
		{"cmem",commands::cmem},

		{"vmem",commands::vmem},
		{"cvmem",commands::cvmem},

		{"cp",commands::cp},
		{"load",commands::load},
		{"lp",commands::lp},
		{"kp",commands::kp},
		{"of",commands::of},
		{"setp",commands::setp},

		{"help",commands::help},

		{"sh",commands::sh}
	};

	std::map<std::string, std::string> helpdesk = {
		{"step","step - wykonanie nastepnego rozkazu przez interpreter polecen\n"},

		{"cf","cf [nazwa_pliku] - tworzy plik\n"},
		{"df","df [nazwa_pliku] - usuwa plik\n"},
		{"op","op [nazwa_pliku] - wyswietla zawartosc pliku\n"},
		{"pf","pf [nazwa_pliku] - wyswietla atrybuty pliku/plików (nazwa pliku opcjonalna)\n"},
		{"sf","sf [nazwa_pliku] - sprawdza, czy plik o podanej nazwie istnieje\n"},
		{"ef","ef [text] > | >> [nazwa_pliku] - edytuje pliku ([text] koniecznie w cudzyslowie!) (> - nadpisanie, >> - dopisanie)\n"},
		{"copy","copy [nazwa_input][nazwa_output] - kopiuje plik\n"},

		{"sem","sem [nazwa_pliku] - wyswietla informacje o semaforze (nazwa pliku opcjonalna)\n"},

		{"ls","ls - wyswietla zawartosc katalogu o podanej nazwie lub biezacego katalogu, gdy nazwa nie jest podana\n"},
		{"rn","rn [nazwa][nowa_nazwa] - zmienia sciezke do pliku\n"},

		{"sd","sd - wyswietla zawartosc dysku\n"},
		{"sfat","sfat - wyswietla informacje o fat\n"},

		{"mem","mem - wyswietla aktualny stan pamieci RAM\n"},
		{"cmem","cmem [komorka] - wyswietla pojedyncza komorke pamieci RAM\n"},

		{"vmem","vmem - wyswietla zawartosc pamieci wirtualnej\n"},
		{"cvmem","cvmem [nazwa_procesu] - wyswietla zawartosc pamieci wirtualnej dla procesu\n"},

		{"cp","cp [nazwa_procesu][nazwa_pliku][priorytet] - tworzy nowy proces\n"},
		//{"load","load [nazwa_procesu][nazwa_pliku] - wczytuje program do procesu\n"},
		{"lp","lp - wyswietla liste utworzonych procesow\n"},
		{"kp","kp - zamyka proces\n"},
		{"of","of [nazwa_procesu] - wyswietla plik otwarte przez podany proces"},
		{"setp","setp [nazwa_procesu][priorytet] - zmienia priorytet podanego procesu"},

		{"help","help - wyswietla wszystkie dostepne komendy\n"},

		{"sh","sh - zamyka system\n"}
	};

	bool is_running = true;				// flaga dzia³ania systemu
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
