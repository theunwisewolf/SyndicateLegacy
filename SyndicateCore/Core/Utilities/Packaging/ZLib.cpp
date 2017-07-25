#include "Zlib.h"

namespace Syndicate {

ZLib::ZLib() :
	m_ErrorCode(Z_OK),
	m_ReadError(false),
	m_WriteError(false)
{
	this->m_ChunkSize = CHUNK;
}

ZLib::ZLib(int chunksize) :
	m_ChunkSize(chunksize),
	m_ErrorCode(Z_OK),
	m_ReadError(false),
	m_WriteError(false)
{
	// Chunk size must be a power of 2
	if (this->m_ChunkSize % 2)
	{
		SYNDICATE_WARNING( "Chunk size must be a power of 2. Defaulting to default chunk size of " + std::to_string(CHUNK) + " bytes." );
		m_ChunkSize = CHUNK;
	}
}

ZLib::~ZLib()
{

}

bool ZLib::Compress(std::string source, std::string destination, int compressionLevel)
{
	int ret, flush;
	unsigned int have;
	z_stream strm;

	unsigned char *in = synnew unsigned char[this->m_ChunkSize];
	unsigned char *out = synnew unsigned char[this->m_ChunkSize];

	/* allocate deflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, compressionLevel);

	if (ret != Z_OK)
	{
		delete[] in;
		delete[] out;

		this->m_ErrorCode = ret;

		return false;
	}

	FILE* sourceFile = fopen(source.c_str(), "rb");
	FILE* destinationFile = fopen(destination.c_str(), "wb");

	if (!sourceFile)
	{
		SYNDICATE_ERROR( "Failed to open " + source + " for reading." );
		return false;
	}

	if (!destinationFile)
	{
		std::vector<char> error(strlen(strerror(errno)));
		sprintf(&error[0], "%s", strerror(errno));
		SYNDICATE_ERROR( "Failed to open " + destination + " for writing. fopen() returned: " + std::string(error.begin(), error.end()) );
		return false;
	}

	fseek(sourceFile, 0, SEEK_SET);
	fseek(destinationFile, 0, SEEK_SET);

	/* compress until end of file */
	do {
		strm.avail_in = fread(in, 1, this->m_ChunkSize, sourceFile);
		if (ferror(sourceFile)) 
		{
			(void)deflateEnd(&strm);

			this->m_ReadError = true;

			fclose(sourceFile);
			fclose(destinationFile);

			delete[] in;
			delete[] out;

			this->m_ErrorCode = Z_ERRNO;

			return false;
		}

		flush = feof(sourceFile) ? Z_FINISH : Z_NO_FLUSH;
		strm.next_in = in;

		/* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
		do {
			strm.avail_out = this->m_ChunkSize;
			strm.next_out = out;

			ret = deflate(&strm, flush);    /* no bad return value */

			if(ret == Z_STREAM_ERROR)		/* state not clobbered */
			{
				this->m_ErrorCode = Z_STREAM_ERROR;

				fclose(sourceFile);
				fclose(destinationFile);

				delete[] in;
				delete[] out;

				return false;
			}

			have = this->m_ChunkSize - strm.avail_out;
			if (fwrite(out, 1, have, destinationFile) != have || ferror(destinationFile)) 
			{
				(void)deflateEnd(&strm);
				
				this->m_WriteError = true;

				fclose(sourceFile);
				fclose(destinationFile);

				delete[] in;
				delete[] out;

				this->m_ErrorCode = Z_ERRNO;

				return false;
			}
		} while (strm.avail_out == 0);

		assert(strm.avail_in == 0);     /* all input will be used */
										/* done when last data in file processed */
	} while (flush != Z_FINISH);

	delete[] in;
	delete[] out;

	/* clean up and return */
	(void)deflateEnd(&strm);

	fclose(sourceFile);
	fclose(destinationFile);

	if (ret == Z_STREAM_END)        /* stream will be complete */
	{
		return true;
	}

	this->m_ErrorCode = ret;
	return false;
}

bool ZLib::Decompress(std::string source, std::string destination)
{
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char *in = synnew unsigned char[this->m_ChunkSize];
	unsigned char *out = synnew unsigned char[this->m_ChunkSize];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit(&strm);

	if (ret != Z_OK)
	{
		delete[] in;
		delete[] out;

		this->m_ErrorCode = ret;
		return false;
	}

	FILE* sourceFile = fopen(source.c_str(), "rb");
	FILE* destinationFile = fopen(destination.c_str(), "wb");

	if (!sourceFile)
	{
		SYNDICATE_ERROR("Failed to open " + source + " for reading.");
		return false;
	}

	if (!destinationFile)
	{
		SYNDICATE_ERROR("Failed to open " + destination + " for writing.");
		return false;
	}

	/* decompress until deflate stream ends or end of file */
	do {
		strm.avail_in = fread(in, 1, this->m_ChunkSize, sourceFile);
		if (ferror(sourceFile)) 
		{
			(void)inflateEnd(&strm);

			fclose(sourceFile);
			fclose(destinationFile);

			delete[] in;
			delete[] out;

			this->m_ReadError = true;
			this->m_ErrorCode = Z_ERRNO;

			return false;
		}

		if (strm.avail_in == 0)
		{
			break;
		}

		strm.next_in = in;

		/* run inflate() on input until output buffer not full */
		do {
			strm.avail_out = this->m_ChunkSize;
			strm.next_out = out;

			ret = inflate(&strm, Z_NO_FLUSH);

			if (ret == Z_STREAM_ERROR)
			{
				fclose(sourceFile);
				fclose(destinationFile);

				delete[] in;
				delete[] out;

				this->m_ErrorCode = Z_STREAM_ERROR;
				return false;
			}

			switch (ret) 
			{
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */

			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);

				fclose(sourceFile);
				fclose(destinationFile);

				delete[] in;
				delete[] out;

				this->m_ErrorCode = ret;

				return false;
			}

			have = this->m_ChunkSize - strm.avail_out;
			if (fwrite(out, 1, have, destinationFile) != have || ferror(destinationFile)) 
			{
				(void)inflateEnd(&strm);

				this->m_ErrorCode = Z_ERRNO;
				this->m_WriteError = true;

				fclose(sourceFile);
				fclose(destinationFile);

				delete[] in;
				delete[] out;

				return false;
			}
		} while (strm.avail_out == 0);

		/* done when inflate() says it's done */
	} while (ret != Z_STREAM_END);

	fclose(sourceFile);
	fclose(destinationFile);

	delete[] in;
	delete[] out;

	/* clean up and return */
	(void)inflateEnd(&strm);

	if (ret == Z_STREAM_END)
	{
		return true;
	}

	this->m_ErrorCode = Z_DATA_ERROR;
	return false;
}

std::string ZLib::getError() const 
{
	std::string readwrite;

	if (this->m_ErrorCode == Z_ERRNO)
	{
		readwrite = (this->m_ReadError ? "read" : "write");
	}

	switch (this->m_ErrorCode)
	{
	case Z_DATA_ERROR:
		return "Invalid or incomplete deflate data";
	case Z_MEM_ERROR:
		return "Failed to allocate memory for processing";
	case Z_STREAM_ERROR:
		return "Invalid compression level was supplied";
	case Z_VERSION_ERROR:
		return "The linked library and the zlib header have different versions";
	case Z_ERRNO:
		return "Failed to " + readwrite + " files";
	default:
		return "An unknown error has occured";
	}
}

}