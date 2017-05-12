#include "File.h"

namespace Syndicate {
namespace Utilities {

File::File() :
	fileSize(0),
	filePath(""),
	m_NoRead(true)
{

}

File::File(std::string path, bool binary) :
	m_NoRead(true)
{
	this->filePath = path;
	this->fileType = (binary == true) ? FILETYPE::BINARY : FILETYPE::TEXT;
	this->fileSize = 0;

	std::fstream file;
}

File& File::Read(int mode)
{
	if (!this->filePath.length())
	{
		SYNDICATE_ERROR("File path is empty.");
		return *this;
	}

	if (this->fileType == FILETYPE::BINARY)
	{
		mode |= std::ios::binary;
	}

	std::ifstream file(this->filePath, mode);

	if (file.fail())
	{
		SYNDICATE_ERROR( "Failed to open file: " + this->filePath );
		return *this;
	}
  
	if (file.is_open())
	{
		// Calculate the amount to be read (for binary files)
		std::streampos startPos = file.tellg(), endPos;
		file.seekg(0, std::ios::end);
		endPos = file.tellg();

		// Reset the file pointer
		file.seekg(0, std::ios::beg);

		this->readSize = endPos - startPos;
		this->fileSize = this->readSize;
		this->data = this->_Read(file);

		return *this;
	}
	else
	{
		SYNDICATE_ERROR("Failed to open file: " + this->filePath);
		return *this;
	}
}

File& File::Read(std::streampos startPos, int mode)
{
	if (!this->filePath.length())
	{
		SYNDICATE_ERROR("File path is empty.");
		return *this;
	}

	if (this->fileType == FILETYPE::BINARY)
	{
		mode |= std::ios::binary;
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
		this->fileSize = endPos;
		this->data = this->_Read(file);

		return *this;
	}
	else
	{
		SYNDICATE_ERROR("Failed to open file: " + this->filePath);
		return *this;
	}
}

File& File::Read(std::streampos startPos, std::streampos endPos, int mode)
{
	if (!this->filePath.length())
	{
		SYNDICATE_ERROR("File path is empty.");
		return *this;
	}

	if (this->fileType == FILETYPE::BINARY)
	{
		mode |= std::ios::binary;
	}

	std::ifstream file(this->filePath, mode);

	if (file.is_open())
	{
		this->fileSize = endPos;
		this->readSize = endPos - startPos;
		this->data = this->_Read(file);
		return *this;
	}
	else
	{
		SYNDICATE_ERROR("Failed to open file: " + this->filePath);
		return *this;
	}
}

std::vector<char> File::_Read(std::ifstream& file)
{
	std::vector<char> buffer;

	if (this->fileType == FILETYPE::BINARY)
	{
		file.seekg(0, std::ios::beg);

		if (!file)
		{
			SYNDICATE_ERROR("Failed to read from file!");
			return buffer;
		}

		buffer.resize(this->readSize);
		file.read(&buffer[0], this->readSize);
	}
	else
	{
		std::string line;

		while (std::getline(file, line))
		{
			line += "\n";
			std::copy(line.begin(), line.end(), std::back_inserter(buffer));
			line.clear();
		}
	}

	file.close();

	// Data was read
	m_NoRead = false;

	return buffer;
}

File::~File()
{
	
}

}}