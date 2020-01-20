#include "pch.h"
#include <iostream>
#include "FileSystem.h"


int main()
{
	std::cout << "OS Simulator" << std::endl;

	try
	{
		FileSystem::GetInstance().create("test");
		FileSystem::GetInstance().write("test", "hello");
		FileSystem::GetInstance().copy_file("test", "test2");
		FileSystem::GetInstance().copy_file("test", "test3");
		FileSystem::GetInstance().copy_file("test", "test4");
		FileSystem::GetInstance().set_file_name("test3", "test5");
	} catch( std::exception& e)
	{
		std::cout << std::endl << e.what() << std::endl;
	}
	
	FileSystem::GetInstance().print_data();
	FileSystem::GetInstance().print_fat();
	FileSystem::GetInstance().print_files();
	
	return 0;
}
