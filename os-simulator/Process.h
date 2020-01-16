#pragma once
#include<vector>
#include <string>
#include <ostream>
#include"Segment.h"

class Process
{
public:
	enum State
	{
		New,
		Waiting,
		Ready,
		Running,
	};
private:
	const int min_priority_ = 0;
	const int max_priority_ = 15;
	std::string name_;
	std::string file_name_;
	State process_state_{};
	int id_;
	int priority_{};
	int ax_ = 0;
	int bx_ = 0;
	int cx_ = 0;
	int dx_ = 0;
	int instruction_counter_{};
	std::vector<Segment> segment_tab_;
public:
	Process(const std::string& name, const std::string& file_name, int priority, int id);
	~Process() = default;

	std::string name() const;
	std::string file_name() const;
	State process_state() const;
	int id() const;
	int priority() const;
	int ax() const;
	int bx() const;
	int cx() const;
	int dx() const;
	int instruction_counter() const;
	std::vector<Segment> segment_tab() const;
	
	void set_name(const std::string& name);
	void set_file_name(const std::string& file_name);
	void set_process_state(State process_state);
	void set_priority(int priority);
	void set_ax(int ax);
	void set_bx(int bx);
	void set_cx(int cx);
	void set_dx(int dx);
	void set_instruction_counter(int instruction_counter);
	void set_segment_tab(const std::vector<Segment>& segment_tab);

	friend std::ostream& operator<<(std::ostream& os, const Process& process)
	{
		// TODO: Consider replacing it with TablePrinter
		return os
			<< "id: " << process.id_
			<< "\tname: " << process.name_
			<< "\tfile: " << process.file_name_
			<< "\tpriority: " << process.priority_
			<< "\tstate: " << process.process_state_;
	}
	
	friend std::ostream& operator<<(std::ostream& os, State& state)
	{
		switch(state)
		{
		case New: os << "New"; break;
		case Waiting: os << "Waiting"; break;
		case Ready: os << "Ready"; break;
		case Running: os << "Running"; break;
		}
		return os;
	}

};

