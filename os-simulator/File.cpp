#include "pch.h"
#include "File.h"

File::File(const std::string& file_name, unsigned int start_cluster) : file_name_(file_name), start_cluster_(start_cluster), file_size_(0), last_read_byte_(0)
{
}

void File::open(Process* process)
{
	semaphore_.Wait(process);
}

void File::close(Process* process)
{
	// semaphore_.Signal(process);
}

std::string File::file_name() const
{
	return file_name_;
}

unsigned int File::start_cluster() const
{
	return start_cluster_;
}

unsigned int File::file_size() const
{
	return file_size_;
}

void File::set_file_size(unsigned file_size)
{
	file_size_ = file_size;
}

unsigned File::last_read_byte() const
{
	return last_read_byte_;
}

void File::set_last_read_byte(unsigned last_read_byte)
{
	last_read_byte_ = last_read_byte;
}

void File::set_file_name(const std::string& file_name)
{
	file_name_ = file_name;
}
