#include "pch.h"
#include "FileSystemDirectory.h"
#include <algorithm>
#include "TablePrinter.h"

FileSystemDirectory::FileSystemDirectory(std::string path): path_(std::move(path)) {
}

std::string FileSystemDirectory::path() const
{
	return path_;
}

std::vector<File*> FileSystemDirectory::files() const
{
	return files_;
}


File* FileSystemDirectory::get_file(std::string file_name)
{
	const auto found_file = std::find_if(files_.begin(), files_.end(), [file_name](File* file)
		{
			return file->file_name() == file_name;
		});

	if(found_file == files_.end())
		throw std::exception("File does not exist");

	return *found_file;
}

bool FileSystemDirectory::exists(std::string file_name)
{
	return std::find_if(files_.begin(), files_.end(), [file_name](File* file)
		{
			return file->file_name() == file_name;
		}) != files_.end();
}

void FileSystemDirectory::create(std::string file_name, unsigned int cluster_index)
{
	const auto file = new File(file_name, cluster_index);
	files_.push_back(file);
}

void FileSystemDirectory::remove(File* file)
{
	files_.erase(std::remove(files_.begin(), files_.end(), file), files_.end());
}