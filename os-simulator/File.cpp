#include "pch.h"
#include "File.h"

File::File(const std::string& file_name, unsigned int start_cluster) : file_name_(file_name), start_cluster_(start_cluster), file_size_(0), last_read_byte_(0)
{
}

void File::open(Process* process)
{
	const bool did_open = semaphore_.Wait(process);

	if(did_open)
		process->add_opened_file(file_name_);
	else
		process->remove_opened_file(file_name_);

	set_last_read_byte(0);
}

void File::close()
{
	const auto process = semaphore_.Signal();

	if(process != nullptr)
		process->add_opened_file(file_name_);
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

bool File::is_opened()
{
	return semaphore_.is_opened();
}

void File::print_semaphore()
{
	semaphore_.show_Semaphore();
}
