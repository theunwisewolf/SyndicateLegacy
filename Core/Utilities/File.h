#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Utilities\VException.h>

namespace Venus {
namespace Utilities {

enum class FILETYPE { BINARY, TEXT };
enum class MODE { READ, WRITE, READWRITE };

class File
{
private:
	std::string data;
	std::string filePath;
	std::streamoff fileSize;
	std::streamoff readSize;
	FILETYPE fileType;

public:

	File();
	File(std::string, bool binary = false);

	File& Read(int mode = std::ios::in);
	File& Read(std::streampos startPos, int mode = std::ios::in);
	File& Read(std::streampos startPos, std::streampos endPos, int mode = std::ios::in);

	std::string getData() const { return this->data;  };

	~File();
	
private:
	std::string _Read(std::ifstream& file);
};


}}

#endif