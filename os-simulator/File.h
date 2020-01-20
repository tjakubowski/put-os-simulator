#pragma once
#include <string>

class File
{
	std::string file_name_;
	unsigned int start_cluster_;
	unsigned int file_size_;
	unsigned int last_read_byte_;

public:
	File(const std::string& file_name, unsigned start_cluster);

	std::string file_name() const;
	unsigned int start_cluster() const;
	unsigned int file_size() const;
	unsigned last_read_byte() const;
	
	void set_file_size(unsigned file_size);
	void set_last_read_byte(unsigned last_read_byte);
};