#include "pch.h"
#include <iostream>
#include "ProcessManager.h"
#include "FileSystem.h"
#include "Assembler.h"
#include "Shell.h"
#include <fstream>

int main()
{
	std::cout << "OS Simulator" << std::endl;

	/*
	try
	{
		ProcessManager::GetInstance().PrintProcesses();

		FileSystem::GetInstance().create("file1", ".text IC A .data 333");
		FileSystem::GetInstance().create("file2", ".text IC A .data 99999999999999999999999999999999");
		FileSystem::GetInstance().create("file3", ".text IC .data 7777");

		ProcessManager::GetInstance().CreateProcess("1", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("2", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("3", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("4", "file1", 7);
		ProcessManager::GetInstance().CreateProcess("5", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("6", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("7", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("8", "file1", 13);
		ProcessManager::GetInstance().CreateProcess("9", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("10", "file1", 5);
		ProcessManager::GetInstance().CreateProcess("rest", "file2", 5);
		ProcessManager::GetInstance().CreateProcess("rest2", "file2", 5);
		ProcessManager::GetInstance().CreateProcess("rest3", "file2", 5);
		VirtualMemory::GetInstance().display_pagefile_segment_tab();
		VirtualMemory::GetInstance().display_pagefile();
		ProcessManager::GetInstance().KillProcess("9");
		ProcessManager::GetInstance().KillProcess("3");
		ProcessManager::GetInstance().KillProcess("5");
		ProcessManager::GetInstance().KillProcess("7");

		ProcessManager::GetInstance().CreateProcess("seven", "file3", 5);

		//virtualmemory test 
		VirtualMemory::GetInstance().display_pagefile_segment_tab();
		VirtualMemory::GetInstance().display_pagefile();
		RAM::GetInstance().show_RAM();
		RAM::GetInstance().show_RAM();
		ProcessManager::GetInstance().PrintProcesses();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	FileSystem::GetInstance().print_data();
	FileSystem::GetInstance().print_fat();
	FileSystem::GetInstance().print_files();
	*/

	std::ifstream file;
	file.open("ciagEulera.txt", std::ios::in);
	FileSystem::GetInstance().create("ciagEulera");
	std::string kod;
	std::string h;
	while (getline(file, h)) {
		kod += h;
		kod += " ";
	}
	file.close();
	FileSystem::GetInstance().write("ciagEulera", kod, false);

	h.clear();
	kod.clear();

	file.open("CheckProcess.txt", std::ios::in);
	FileSystem::GetInstance().create("CheckProcess");
	while (getline(file, h)) {
		kod += h;
		kod += " ";
	}
	file.close();
	FileSystem::GetInstance().write("CheckProcess", kod, false);

	
	Shell shell;
	shell.run();
	return 0;
}
