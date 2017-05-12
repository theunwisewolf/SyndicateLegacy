#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <Common.h>

#include <Utilities/Logger.h>

#ifdef SYNDICATE_WINDOWS
#include <Windows.h>
#endif

namespace Syndicate {

class SYNDICATE_API FileSystem 
{
public:
	static FileSystem* i()
	{
		static FileSystem instance;
		return &instance;
	}

private:
	std::string m_TempDirectory;
	FileSystem();
	FileSystem(const FileSystem& copy) = delete;
	FileSystem& operator=(const FileSystem& copy) = delete;

public:
	~FileSystem();

	// Returns path to temp file
	bool RemoveFile(const std::string& filepath);
	bool RemoveTempFile(const std::string&filename);

	std::string GetDirectoryName(const std::string& path);
	std::string GetExtension(const std::string& path);

	std::string CreateTempFile();
	std::string getTempDirectory() const { return this->m_TempDirectory; }
};

}

#endif