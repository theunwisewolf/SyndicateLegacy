#ifndef IMAGE_H_
#define IMAGE_H_

#include <Common.h>

#include <FreeImage.h>

namespace Syndicate { namespace Utilities { 

static FIBITMAP* loadImage(const char* filename, GLsizei *width, GLsizei* height)
{
	FIBITMAP *dib = nullptr;
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	fif = FreeImage_GetFileType(filename, 0);
	
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);

	if (fif == FIF_UNKNOWN)
		return nullptr;

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);

	if (!dib)
		return nullptr;

	*width  = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);

	if ((width == 0) || (height == 0))
		return nullptr;

	return dib;
}

} }

#endif