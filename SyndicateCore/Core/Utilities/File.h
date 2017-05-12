#ifndef FILE_H_
#define FILE_H_

#include <Common.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

#include <Utilities/VException.h>
#include <Utilities/Logger.h>

namespace Syndicate {
namespace Utilities {

enum class FILETYPE { BINARY, TEXT };
enum class MODE { READ, WRITE, READWRITE };

class SYNDICATE_API File
{
private:
	// Char is trivially copyable
	std::vector<char> data;
	std::string filePath;
	std::streamoff fileSize;
	std::streamoff readSize;
	FILETYPE fileType;

	bool m_NoRead;

public:

	File();
	File(std::string, bool binary = false);

	File& Read(int mode = std::ios::in);
	File& Read(std::streampos startPos, int mode = std::ios::in);
	File& Read(std::streampos startPos, std::streampos endPos, int mode = std::ios::in);

	std::string getData() { 
		if (m_NoRead) {
			SYNDICATE_ERROR("Retrieving data without calling Read()");
		} else m_NoRead = true;

		return std::string(this->data.begin(), this->data.end()); 
	};

	std::vector<char> getRawData() { 
		if (m_NoRead) {
			SYNDICATE_ERROR("Retrieving data without calling Read()");
		} else m_NoRead = true;
		
		return this->data; 
	}

	std::streamoff getFileSize() const { return this->fileSize;  };

	~File();
	
public:
	static inline bool Exists(const std::string& name) 
	{
		if (FILE *file = fopen(name.c_str(), "r")) { fclose(file); return true; }
		return false;
	}

private:
	std::vector<char> _Read(std::ifstream& file);
};


}}

#endif