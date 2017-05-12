#ifndef IMAGE_H_
#define IMAGE_H_

#include <Common.h>

#include <FreeImage.h>

namespace Syndicate { namespace Utilities { 

template <class T> void INPLACESWAP(T& a, T& b);
BOOL SwapRedBlue32(FIBITMAP* dib);
SYNDICATE_API BYTE* loadImage(const char* filename, unsigned int *width, unsigned int* height, unsigned int& size, int* bits = nullptr);
SYNDICATE_API BYTE* loadImageFromMemory(BYTE* buffer, unsigned int bufferSize, unsigned int *width, unsigned int* height);

} }

#endif