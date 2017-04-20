#include "Image.h"

namespace Syndicate { namespace Utilities {

BYTE* loadImage(const char* filename, unsigned int *width, unsigned int* height, int* bits)
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

	FIBITMAP* bitmap = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(dib);

	BYTE* pixels = FreeImage_GetBits(bitmap);
	int _bits = FreeImage_GetBPP(bitmap);
	*width = FreeImage_GetWidth(bitmap);
	*height = FreeImage_GetHeight(bitmap);
	//byte* pixels = FreeImage_GetBits(bitmap);

	if (FreeImage_GetRedMask(bitmap) == 0xff0000)
		SwapRedBlue32(bitmap);

	if ((width == 0) || (height == 0))
		return nullptr;

	unsigned int size = *width * *height * (_bits / 8);
	BYTE* result = synnew BYTE[size];
	memcpy(result, pixels, size);
	FreeImage_Unload(bitmap);

	return result;
}

/* From FreeImage */
template <class T> void INPLACESWAP(T& a, T& b) {
	a ^= b; b ^= a; a ^= b;
}

BOOL SwapRedBlue32(FIBITMAP* dib) {
	if (FreeImage_GetImageType(dib) != FIT_BITMAP) {
		return FALSE;
	}

	const unsigned bytesperpixel = FreeImage_GetBPP(dib) / 8;
	if (bytesperpixel > 4 || bytesperpixel < 3) {
		return FALSE;
	}

	const unsigned height = FreeImage_GetHeight(dib);
	const unsigned pitch = FreeImage_GetPitch(dib);
	const unsigned lineSize = FreeImage_GetLine(dib);

	BYTE* line = FreeImage_GetBits(dib);
	for (unsigned y = 0; y < height; ++y, line += pitch) {
		for (BYTE* pixel = line; pixel < line + lineSize; pixel += bytesperpixel) {
			INPLACESWAP(pixel[0], pixel[2]);
		}
	}

	return TRUE;
}

}}