#include "pch.h"
#include "TablePrinter.h"

TablePrinter::TablePrinter(std::string column_separator, int column_padding) : column_separator_(column_separator), column_padding_(column_padding)
{
}

int TablePrinter::GetTotalWidth()
{
	const int separators_total_size = column_separator_.size() * (1 + columns_.size());
	const int paddings_total_size = column_padding_ * columns_.size() * 2;
	int columns_total_size = 0;

	for (auto& column : columns_)
		columns_total_size += column.column_width_;

	return separators_total_size + paddings_total_size + columns_total_size;
}

void TablePrinter::PrintLine()
{
	std::cout << std::string(GetTotalWidth(), '-') << std::endl;
}

void TablePrinter::AddColumn(std::string column_name, unsigned int column_width, bool column_align_left)
{
	column_width = std::max(column_width, (unsigned int)column_name.size());
	columns_.push_back({ column_name, column_width, column_align_left });
}

void TablePrinter::PrintHeader()
{
	PrintLine();

	for (auto& column : columns_)
	{
		std::cout
			<< column_separator_ << std::string(column_padding_, ' ');
		if (column.column_align_left_)
			std::cout << std::left;
		else
			std::cout << std::right;
		std::cout << std::setw(column.column_width_) << column.column_name_ << std::string(column_padding_, ' ');
	}
		
	std::cout << column_separator_ << std::endl;
	
	PrintLine();
}

void TablePrinter::PrintFooter()
{
	PrintLine();
}

void TablePrinter::ClearColumns()
{
	columns_.clear();
}

void TablePrinter::set_column_separator(const std::string& column_separator)
{
	column_separator_ = column_separator;
}

void TablePrinter::set_column_padding(unsigned column_padding)
{
	column_padding_ = column_padding;
}