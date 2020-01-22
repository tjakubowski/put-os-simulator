#pragma once
#include <string>
#include <vector>
#include "File.h"

class FileSystemDirectory
{
	std::string path_;
	std::vector<File*> files_;

public:
	FileSystemDirectory(std::string path = "/");
	
	std::string path() const;
	std::vector<File*> files() const;
	File* get_file(std::string file_name);
	bool exists(std::string file_name);
	void create(std::string file_name, unsigned int cluster_index);
	void remove(File* file);
};
