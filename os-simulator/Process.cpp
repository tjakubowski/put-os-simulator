#include "pch.h"
#include "Process.h"

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
	if (priority < min_priority_)
		throw std::exception("Minimum priority value is "); // TODO: Add priority value in exception message
	if (priority > max_priority_)
		throw std::exception("Maximum priority value is "); // TODO: Add priority value in exception message
	
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