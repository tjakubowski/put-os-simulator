#pragma once
#include <map>
#include <string>

class Shell {
private:

	enum class commands{
		cf,
		op,
		cl,




		ls,
		md,
		rd,
		move,

		sb,
		sd,
		mem,
		wmem,
		cp,
		load,
		lp,
		kp,
		help,
		sh
	};

private:

	std::map<std::string, commands> commands = {
		{"cf",commands::cf},
		{"op",commands::op},
		{"cl",commands::cl},
		



		{"ls",commands::ls},
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
		{"sh",commands::sh},
	};
	bool is_running = true;				// flaga dzia³ania systemu
	std::string input;					// pobrana linia
	std::vector<std::string> command;	// wektor przechowujacy komende i jej arumenty

	void create_command();				// zapisuje do wektora nazwe komendy i jej argumenty
	bool stob(std::string);				// string to bool
	unsigned short stous(std::string);	// string to unsigned short
	void help();						// wyswietla wszystkie komendy
	void perform_command();				// wykonuje komende

public:

	void run();							// uruchomienie programu

};
