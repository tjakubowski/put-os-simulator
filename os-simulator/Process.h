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
	std::string name_;
	std::string file_name_;
	int process_state_{};
	int id_;
	int priority_;
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
	int process_state() const;
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

	friend std::ostream& operator<<(std::ostream& os, const Process& obj)
	{
		return os
			<< "id: " << obj.id_
			<< "\tname: " << obj.name_
			<< "\tfile: " << obj.file_name_
			<< "\tpriority: " << obj.priority_
			<< "\tstate: " << obj.process_state_;
	}
};
