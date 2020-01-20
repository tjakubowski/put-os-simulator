#pragma once
#include "FileSystemDirectory.h"
#include "Singleton.h"
#include <iostream>
#include <sstream>

class FileSystem : public Singleton<FileSystem>
{
	friend class Singleton<FileSystem>;

	struct FatEntry
	{
		bool busy_ = false;
		int next_ = -1;
	};

	const unsigned int drive_size_ = 64; // 1024
	const unsigned int cluster_size_ = 16; // 32
	const unsigned int clusters_count_ = drive_size_ / cluster_size_;

	FileSystemDirectory root_directory_;
	FatEntry* fat_;
	char* data_;

	bool exists(std::string file_name);
	unsigned get_free_clusters_count();
	int get_first_empty_cluster_index();
	bool will_fit(std::string file_name, std::string bytes, bool append);
	
public:
	FileSystem();
	~FileSystem();
	
	void print_fat() const;
	void print_data() const;

	void create(std::string file_name);
	void remove(std::string file_name);
	
	void open(std::string file_name);
	void close(std::string file_name);

	void write(std::string file_name, std::string bytes, bool append = false);
	void write(std::string file_name, char byte, bool append = false);

	char read_next_byte(std::string file_name);
	std::string read_all(std::string file_name);
};