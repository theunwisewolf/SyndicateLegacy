#include "File.h"

namespace Venus {
namespace Utilities {

File::File()
{

}

File::File(std::string path, bool binary)
{
	this->filePath = path;
	this->fileType = (binary == true) ? FILETYPE::BINARY : FILETYPE::TEXT;

	std::fstream file;
}

File& File::Read(int mode)
{
	if (!this->filePath.length())
	{
		throw VException("File path is empty.");
		return *this;
	}

	std::ifstream file(this->filePath, mode);

	if (file.is_open())
	{
		// Calculate the amount to be read (for binary files)
		std::streampos startPos = file.tellg(), endPos;
		file.seekg(0, std::ios::end);
		endPos = file.tellg();

		// Reset the file pointer
		file.seekg(0, std::ios::beg);

		this->readSize = endPos - startPos;
		this->data = this->_Read(file);

		return *this;
	}
	else
	{
		throw VException("Failed to open file: " + this->filePath);
		return *this;
	}
}

File& File::Read(std::streampos startPos, int mode)
{
	if (!this->filePath.length())
	{
		throw VException("File path is empty.");
		return *this;
	}

	std::ifstream file(this->filePath, mode);

	if (file.is_open())
	{
		// Calculate the amount to be read (for binary files)
		file.seekg(0, std::ios::end);
		std::streampos endPos = file.tellg();

		// Reset the file pointer
		file.seekg(startPos, std::ios::beg);

		this->readSize = endPos - startPos;
		this->data = this->_Read(file);

		return *this;
	}
	else
	{
		throw VException("Failed to open file: " + this->filePath);
		return *this;
	}
}

File& File::Read(std::streampos startPos, std::streampos endPos, int mode)
{
	if (!this->filePath.length())
	{
		throw VException("File path is empty.");
		return *this;
	}

	std::ifstream file(this->filePath, mode);

	if (file.is_open())
	{
		this->readSize = endPos - startPos;
		this->data = this->_Read(file);
		return *this;
	}
	else
	{
		throw VException("Failed to open file: " + this->filePath);
		return *this;
	}
}

std::string File::_Read(std::ifstream& file)
{
	std::string data;

	if (this->fileType == FILETYPE::BINARY)
	{
		char* memblock = new char[this->readSize];
		file.read(memblock, this->readSize);

		data = memblock;
		delete[] memblock;
	}
	else
	{
		std::string line;

		while (std::getline(file, line))
		{
			data += line + "\n";
		}
	}

	file.close();
	return data;
}

File::~File()
{
	
}

}}