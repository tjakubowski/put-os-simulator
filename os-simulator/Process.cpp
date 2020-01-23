#include "pch.h"
#include "Process.h"
#include "TablePrinter.h"

Process::Process(const std::string& name, const std::string& file_name, const int priority, const int id) : name_(name), file_name_(file_name), id_(id)
{
	set_priority(priority);
}

std::string Process::name() const
{
	return name_;
}

void Process::set_name(const std::string& name)
{
	name_ = name;
}

std::string Process::file_name() const
{
	return file_name_;
}

void Process::set_file_name(const std::string& file_name)
{
	file_name_ = file_name;
}

Process::State Process::process_state() const
{
	return process_state_;
}

void Process::set_process_state(State process_state)
{
	process_state_ = process_state;
}

int Process::id() const
{
	return id_;
}

int Process::ax() const
{
	return ax_;
}

void Process::set_ax(int ax)
{
	ax_ = ax;
}

int Process::bx() const
{
	return bx_;
}

void Process::set_bx(int bx)
{
	bx_ = bx;
}

int Process::cx() const
{
	return cx_;
}

void Process::set_cx(int cx)
{
	cx_ = cx;
}

int Process::dx() const
{
	return dx_;
}

void Process::set_dx(int dx)
{
	dx_ = dx;
}

int Process::priority() const
{
	return priority_;
}

void Process::set_priority(int priority)
{
	std::string exception_string;
	exception_string.append(std::to_string(min_priority_));
	
	if (priority < min_priority_)
	{
		exception_string = "Minimalna wartosc priorytetu to ";
		exception_string.append(std::to_string(min_priority_));
		throw std::exception(exception_string.c_str());
	}
	if (priority > max_priority_)
	{
		exception_string = "Maksymalna wartosc priorytetu to ";
		exception_string.append(std::to_string(max_priority_));
		throw std::exception(exception_string.c_str());
	}
	
	priority_ = priority;
}

int Process::instruction_counter() const
{
	return instruction_counter_;
}

void Process::set_instruction_counter(int instruction_counter)
{
	instruction_counter_ = instruction_counter;
}

void Process::add_opened_file(std::string file_name)
{
	opened_files_.push_back(file_name);
}

void Process::remove_opened_file(std::string file_name)
{
	opened_files_.remove(file_name);
}

std::list<std::string> Process::opened_files() const
{
	return opened_files_;
}

std::vector<Segment*> Process::segment_tab() const
{
	return segment_tab_;
}

void Process::set_segment_tab(const std::vector<Segment*>& segment_tab)
{
	segment_tab_ = segment_tab;
}

std::string Process::text_segment() {
	return segment_tab_[0]->data;
}
std::string Process::data_segment() {
	return segment_tab_[1]->data;
}
std::string Process::message_segment() {
	return segment_tab_[2]->data;
}

bool Process::is_file_opened(std::string file_name)
{
	return std::find(opened_files_.begin(), opened_files_.end(), file_name) != opened_files_.end();
}

void Process::print_opened_files()
{
	TablePrinter tp;
	tp.AddColumn("ID", 2);
	tp.AddColumn("Name", 10);
	tp.AddColumn("Opened files", 15);
	
	tp.PrintHeader();
	tp << id_ <<  name_;

	if (opened_files_.empty())
		tp << "";

	for (auto file = opened_files_.begin(); file != opened_files_.end(); ++file)
	{
		if (file != opened_files_.begin())
			tp << "" << "";
		tp << *file;
	}
	tp.PrintFooter();
}