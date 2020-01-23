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

	const unsigned int drive_size_ = 1024; // 1024
	const unsigned int cluster_size_ = 32; // 32
	const unsigned int clusters_count_ = drive_size_ / cluster_size_;

	FileSystemDirectory root_directory_;
	FatEntry* fat_;
	char* data_;

	
	unsigned get_free_clusters_count();
	int get_first_empty_cluster_index();
	bool will_fit(std::string file_name, std::string bytes, bool append);
	
public:
	FileSystem();
	~FileSystem();
	
	void print_fat() const;
	void print_data() const;
	void print_files();
	void print_file(std::string file_name);
	int how_many_clusters_occupy(std::string file_name);
	int how_many_clusters_occupy(File* file);
	void print_files_semaphores();
	void print_file_semaphore(std::string file_name);
	void print_file_semaphore(File* file);

	void create(std::string file_name);
	void create(std::string file_name, std::string bytes);
	void remove(std::string file_name);

	bool exists(std::string file_name);
	
	void open(Process* process, std::string file_name);
	void close(std::string file_name);

	void write(std::string file_name, std::string bytes, bool append = false);
	void write(std::string file_name, char byte, bool append = false);

	void reset_last_read_byte(std::string file_name);
	void reset_last_read_byte(File* file);

	void set_file_name(std::string file_name, std::string new_file_name);
	void copy_file(std::string file_name, std::string new_file_name);

	char read_next_byte(std::string file_name);
	char read_next_byte(File* file);
	std::string read_all(std::string file_name);
	std::string read_all(File* file);
};
