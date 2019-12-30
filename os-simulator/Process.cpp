#include "pch.h"
#include "Process.h"

Process::Process(const std::string& name, const std::string& file_name, const int priority, const int id) : name_(name), file_name_(file_name), id_(id), priority_(priority)
{
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

int Process::process_state() const
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

int Process::priority() const
{
	return priority_;
}

void Process::set_priority(int priority)
{
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

std::vector<Segment> Process::segment_tab() const
{
	return segment_tab_;
}

void Process::set_segment_tab(const std::vector<Segment>& segment_tab)
{
	segment_tab_ = segment_tab;
}
