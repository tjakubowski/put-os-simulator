#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

class TablePrinter
{
	struct TableColumn
	{
		std::string column_name_;
		unsigned int column_width_;
		bool column_align_left_;
	};
	
	unsigned int input_counter_ = 0;
	std::vector<TableColumn> columns_;
	std::string column_separator_;
	unsigned int column_padding_;

	int GetTotalWidth();
	void PrintLine();

public:
	TablePrinter(std::string column_separator = "|", int column_padding = 1);
	void AddColumn(std::string column_name, unsigned int column_width, bool column_align_left = true);
	void PrintHeader();
	void PrintFooter();
	void ClearColumns();

	void set_column_separator(const std::string& column_separator);
	void set_column_padding(unsigned column_padding);

	template<typename T> TablePrinter& operator<<(T input)
	{
		auto column = columns_[input_counter_];

		std::stringstream input_string_stream;
		input_string_stream << input;
		std::string input_string = input_string_stream.str();

		if (input_string.length() > column.column_width_)
			input_string = input_string.substr(0, column.column_width_ - 1) + "*";
		
		std::cout
			<< column_separator_ << std::string(column_padding_, ' ');
		
		column.column_align_left_ ? std::cout << std::left : std::cout << std::right;
		
		std::cout << std::setw(column.column_width_) << input_string << std::string(column_padding_, ' ');

		if (++input_counter_ == columns_.size())
		{
			std::cout << column_separator_ << std::endl;
			input_counter_ = 0;
		}

		return *this;
	}

};

