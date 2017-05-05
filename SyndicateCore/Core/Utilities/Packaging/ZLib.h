#ifndef ZLIB_H_
#define ZLIB_H_

#include <Common.h>

#include <Utilities/Logger.h>
#include <zlib.h>

#include <cassert>
#include <sstream>

/**
 * This is an ugly hack required to avoid corruption of the input and output data on Windows/MS-DOS systems. 
 * Without this, those systems would assume that the input and output files are text, 
 * and try to convert the end-of-line characters from one standard to another. 
 * That would corrupt binary data, and in particular would render the compressed data unusable. 
 * This sets the input and output to binary which suppresses the end-of-line conversions. 
 * SET_BINARY_MODE() will be used later on stdin and stdout, at the beginning of main().
 */

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

// The Buffer Size = 128 Kilobytes
#define CHUNK 128 * 1024

namespace Syndicate {

class SYNDICATE_API ZLib 
{
private:
	int m_ChunkSize;
	int m_ErrorCode;

	bool m_ReadError;
	bool m_WriteError;

public:
	ZLib();
	ZLib(int chunksize);

	// Compresses a single file
	// The compression level varies from 0 to 9. A value 0 means no compression
	bool Compress(std::string source, std::string destination, int compressionLevel = Z_BEST_COMPRESSION);
	bool Decompress(std::string source, std::string destination);

	std::string getError() const;
	int getErrorCode() const { return this->m_ErrorCode; };

	inline void setChunkSize(const int& chunksize) { this->m_ChunkSize = chunksize; };

	~ZLib();
};

}

#endif