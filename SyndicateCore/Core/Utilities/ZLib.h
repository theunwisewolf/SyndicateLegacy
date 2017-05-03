#ifndef ZLIB_H_
#define ZLIB_H_

#include <Common.h>
#include <zlib.h>

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

// The Buffer Size
#define CHUNK 16384

namespace Syndicate {

class SYNDICATE_API ZLib 
{
private:
	int m_ChunkSize;

public:
	ZLib(int chunksize);
	~ZLib();
};

}

#endif