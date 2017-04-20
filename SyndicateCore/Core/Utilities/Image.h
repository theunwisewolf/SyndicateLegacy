#ifndef IMAGE_H_
#define IMAGE_H_

#include <Common.h>

#include <FreeImage.h>

namespace Syndicate { namespace Utilities { 

template <class T> void INPLACESWAP(T& a, T& b);
BOOL SwapRedBlue32(FIBITMAP* dib);
BYTE* loadImage(const char* filename, unsigned int *width, unsigned int* height, int* bits = nullptr);

} }

#endif