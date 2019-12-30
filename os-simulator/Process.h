#pragma once
#include<vector>
#include"Segment.h"
#include <string>

class Process
{
public:
	enum State
	{
		Waiting,
		Ready,
		Running,
	};
private:
	std::string name_;
	std::string file_name_;
	int process_state_{};
	int id_{};
	int priority_;
	int registers_[3];
	int instruction_counter_{};
	std::vector<Segment> segment_tab_; // TODO: Consider changing its name
public:
	Process(const std::string& name, const std::string& file_name, int priority, int id);
	~Process() = default;

	std::string name() const;
	std::string file_name() const;
	int process_state() const;
	int id() const;
	int priority() const;
	int instruction_counter() const;
	std::vector<Segment> segment_tab() const;
	
	void set_name(const std::string& name);
	void set_file_name(const std::string& file_name);
	void set_process_state(State process_state);
	void set_priority(int priority);
	void set_instruction_counter(int instruction_counter);
	void set_segment_tab(const std::vector<Segment>& segment_tab);
};

