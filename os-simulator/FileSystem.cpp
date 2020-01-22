#include "pch.h"
#include "FileSystem.h"
#include "TablePrinter.h"

FileSystem::FileSystem()
{
	fat_ = new FatEntry[clusters_count_];
	data_ = new char[drive_size_];
}

FileSystem::~FileSystem()
{
	delete fat_;
	delete data_;
}

void FileSystem::print_fat() const
{
	TablePrinter tp;
	tp.AddColumn("Index", 5);
	tp.AddColumn("Is busy", 5);
	tp.AddColumn("Next index", 5);

	tp.PrintHeader();
	for (int i = 0; i < clusters_count_; i++)
		tp << i << fat_[i].busy_ << fat_[i].next_;
	tp.PrintFooter();
}

void FileSystem::print_data() const
{
	TablePrinter tp;
	tp.AddColumn("Clusters", 15);
	tp.AddColumn("Bytes", cluster_size_ * 2);
	
	tp.PrintHeader();
	for(int i = 0; i < clusters_count_; i++)
	{
		tp << std::to_string(i * cluster_size_) + " - " + std::to_string( cluster_size_ * (1 + i) - 1);
		std::string bytes;

		for(int j = 0; j < cluster_size_; j++)
		{
			bytes += data_[i * cluster_size_ + j];
			bytes += ' ';
		}
		
		tp << bytes;
	}
	tp.PrintFooter();
}

void FileSystem::print_files()
{
	root_directory_.print();
}

void FileSystem::print_files_semaphores()
{
	for (auto& file : root_directory_.files())
		print_file_semaphore(file);
}

void FileSystem::print_file_semaphore(std::string file_name)
{
	auto file = root_directory_.get_file(file_name);
	print_file_semaphore(file);
}

void FileSystem::print_file_semaphore(File* file)
{
	std::cout << file->file_name() << std::endl;
	file->print_semaphore();
}

bool FileSystem::exists(std::string file_name)
{
	return root_directory_.exists(file_name);
}

unsigned int FileSystem::get_free_clusters_count()
{
	unsigned int count = 0;

	for (auto fat_index = 0; fat_index < clusters_count_; ++fat_index)
		if (!fat_[fat_index].busy_)
			count++;
	
	return count;
}

int FileSystem::get_first_empty_cluster_index()
{
	for(int fat_index = 0; fat_index < clusters_count_; ++fat_index)
	{
		const auto fat_entry = fat_[fat_index];
		if (!fat_entry.busy_)
			return fat_index;
	}

	throw std::exception("There are no free clusters");
}

void FileSystem::create(std::string file_name)
{
	if (exists(file_name))
		throw std::exception("File already exists");

	if(get_free_clusters_count() < 1)
		throw std::exception("There are no free clusters");

	const auto cluster_index = get_first_empty_cluster_index();
	root_directory_.create(file_name, cluster_index);
	fat_[cluster_index].busy_ = true;
	fat_[cluster_index].next_ = -1;
}

void FileSystem::create(std::string file_name, std::string bytes)
{
	create(file_name);
	write(file_name, bytes);
}

void FileSystem::remove(std::string file_name)
{
	if (!exists(file_name))
		throw std::exception("File does not exist");

	const auto file = root_directory_.get_file(file_name);
	root_directory_.remove(file);

	for(int next = file->start_cluster(); next != -1; next = fat_[next].next_)
		fat_[next].busy_ = false;
}

void FileSystem::open(Process* process, std::string file_name)
{
	auto file = root_directory_.get_file(file_name);
	file->open(process);
}

void FileSystem::close(std::string file_name)
{
	root_directory_.get_file(file_name)->close();
}

void FileSystem::write(std::string file_name, char byte, bool append)
{
	write(file_name, std::string(1, byte), append);
}

void FileSystem::set_file_name(std::string file_name, std::string new_file_name)
{
	auto file = root_directory_.get_file(file_name);
	file->set_file_name(new_file_name);
}

void FileSystem::copy_file(std::string file_name, std::string new_file_name)
{
	auto file_bytes = read_all(file_name);
	create(new_file_name);
	write(new_file_name, file_bytes);
}

bool FileSystem::will_fit(std::string file_name, std::string bytes, bool append)
{
	const auto file_size = root_directory_.get_file(file_name)->file_size();

	const auto free_clusters_bytes = get_free_clusters_count() * cluster_size_;
	
	if(append)
	{
		const auto bytes_left_in_cluster = cluster_size_ - file_size % cluster_size_;
		return bytes.size() <= bytes_left_in_cluster + free_clusters_bytes;
	}

	const unsigned int occupied_clusters = ceil(static_cast<float>(file_size) / cluster_size_);
	const unsigned int occupied_clusters_bytes = (occupied_clusters == 0 ? 1: occupied_clusters)  * cluster_size_;
	return bytes.size() <= occupied_clusters_bytes + free_clusters_bytes;
}

void FileSystem::write(std::string file_name, std::string bytes, bool append)
{
	auto file = root_directory_.get_file(file_name);
	auto file_bytes_count = file->file_size();
	auto cluster_index = file->start_cluster();
	int byte_index = 0;

	if (!will_fit(file_name, bytes, append))
		throw std::exception("There is not enough memory in file system.");

	while (true)
	{
		// Iterate over every byte in cluster
		for (int i = 0; i < cluster_size_; i++)
		{
			if (append && file_bytes_count > 0)
			{
				file_bytes_count--;
				continue;
			}
			
			const auto memory_address = cluster_index * cluster_size_ + i;
			const auto byte = bytes[byte_index++];
			data_[memory_address] = byte;

			// If bytes are already in file
			if(byte_index == bytes.size())
			{
				if (append)
					file->set_file_size(file->file_size() + bytes.size());
				else
					file->set_file_size(bytes.size());

				// Make next occupied clusters free
				while(fat_[cluster_index].next_ > -1)
				{
					cluster_index = fat_[cluster_index].next_;
					fat_[cluster_index].busy_ = false;
				}
				return;
			}
		}

		// Add new cluster to file if needed
		if (fat_[cluster_index].next_ == -1)
		{
			const auto new_cluster_index = get_first_empty_cluster_index();
			fat_[new_cluster_index].busy_ = true;
			fat_[new_cluster_index].next_ = -1;
			fat_[cluster_index].next_ = new_cluster_index;
		}

		cluster_index = fat_[cluster_index].next_;
	}
}

char FileSystem::read_next_byte(std::string file_name)
{
	auto file = root_directory_.get_file(file_name);
	auto byte_to_read = file->last_read_byte();
	auto cluster_index = file->start_cluster();

	if (byte_to_read >= file->file_size())
		throw std::exception("End of file");

	auto cluster_offset = byte_to_read / cluster_size_;

	while (cluster_offset-- > 0)
		cluster_index = fat_[cluster_index].next_;

	file->set_last_read_byte(byte_to_read + 1);
	return data_[cluster_index * cluster_size_ + byte_to_read % cluster_size_];
}

std::string FileSystem::read_all(std::string file_name)
{
	auto file = root_directory_.get_file(file_name);
	auto bytes_to_read = file->file_size();
	auto cluster_index = file->start_cluster();

	std::stringstream ss;

	while(true)
	{
		for (int i = 0; i < cluster_size_; i++)
		{
			if (bytes_to_read == 0)
				return ss.str();
			
			const auto memory_address = cluster_index * cluster_size_ + i;
			const auto byte = data_[memory_address];

			ss << byte;
			bytes_to_read--;
		}
		
		cluster_index = fat_[cluster_index].next_;
	}
}