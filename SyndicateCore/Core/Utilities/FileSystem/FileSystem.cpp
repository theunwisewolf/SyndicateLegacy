#include "FileSystem.h"

namespace Syndicate {

FileSystem::FileSystem()
{
	char buffer[1024];

#ifdef SYNDICATE_WINDOWS
	GetTempPath(1024, buffer);
#endif

	this->m_TempDirectory = std::string(buffer);
}

std::string FileSystem::CreateTempFile()
{
	char tempFileName[1024];
#ifdef SYNDICATE_WINDOWS
	HANDLE hTempFile;
	UINT uRetVal;

	uRetVal = GetTempFileName(this->getTempDirectory().c_str(), // directory for tmp files
		TEXT("SYNDICATE"),     // temp file name prefix 
		0,                // create unique name 
		tempFileName);  // buffer for name 

	if (uRetVal == 0)
	{
		SYNDICATE_ERROR( "GetTempFileName failed" );
		return "";
	}

	hTempFile = CreateFile((LPTSTR)tempFileName, // file name 
		GENERIC_WRITE,        // open for write 
		0,                    // do not share 
		NULL,                 // default security 
		CREATE_ALWAYS,        // overwrite existing
		FILE_ATTRIBUTE_NORMAL,// normal file 
		NULL);                // no template 

	if (hTempFile == INVALID_HANDLE_VALUE)
	{
		SYNDICATE_ERROR("Failed to create temporary file");
		return "";
	}

	CloseHandle(hTempFile);

#endif

	return tempFileName;
}

bool FileSystem::RemoveFile(const std::string& filepath)
{
	if (remove(filepath.c_str()))
	{
		perror("remove");
		SYNDICATE_ERROR("Failed to remove file " + filepath);

		return false;
	}

	return true;
}

bool FileSystem::RemoveTempFile(const std::string& filename)
{
	std::string fullPath = this->getTempDirectory() + filename;

	if (remove(fullPath.c_str()))
	{
		perror("remove");
		SYNDICATE_ERROR("Failed to remove file " + fullPath);

		return false;
	}

	return true;
}

std::string FileSystem::GetDirectoryName(const std::string& path)
{
	std::string pureDir = std::string(path);

	std::string::size_type pos = path.find_last_of("/");

	if (pos == std::string::npos)
	{
		pos = path.find_last_of("\\");
	}

	pureDir.replace(pos, pureDir.length() - pos, "");

	return pureDir;
}

// TODO: support extensions like .tar.gz
std::string FileSystem::GetExtension(const std::string& path)
{
	std::string::size_type pos = path.find_last_of(".");

	// No extension
	if (pos == std::string::npos)
	{
		return "";
	}

	std::string extension = path.substr(pos + 1);

	return extension;
}

FileSystem::~FileSystem()
{

}

}