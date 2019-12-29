#include "pch.h"
#include "PCB.h"

PCB::PCB(const std::string& name, const std::string& file_name, const int priority, const int id) : name_(name), file_name_(file_name), id_(id), priority_(priority), registers_{}
{
}

std::string PCB::name() const
{
	return name_;
}

void PCB::set_name(const std::string& name)
{
	name_ = name;
}

std::string PCB::file_name() const
{
	return file_name_;
}

void PCB::set_file_name(const std::string& file_name)
{
	file_name_ = file_name;
}

int PCB::process_state() const
{
	return process_state_;
}

void PCB::set_process_state(State process_state)
{
	process_state_ = process_state;
}

int PCB::id() const
{
	return id_;
}

int PCB::priority() const
{
	return priority_;
}

void PCB::set_priority(int priority)
{
	priority_ = priority;
}

int PCB::instruction_counter() const
{
	return instruction_counter_;
}

void PCB::set_instruction_counter(int instruction_counter)
{
	instruction_counter_ = instruction_counter;
}

std::vector<Segment> PCB::segment_tab() const
{
	return segment_tab_;
}

void PCB::set_segment_tab(const std::vector<Segment>& segment_tab)
{
	segment_tab_ = segment_tab;
}
