#ifndef COMMON_H_
#define COMMON_H_

#include <glew.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef SYNDICATE_DYNAMIC
#	define SYNDICATE_API		__declspec(dllexport)
#	define SYNDICATE_TEMPLATE
#else
#	define SYNDICATE_API		__declspec(dllimport)
#	define SYNDICATE_TEMPLATE   extern
#endif

SYNDICATE_TEMPLATE template class SYNDICATE_API std::allocator<char>;
SYNDICATE_TEMPLATE template class SYNDICATE_API std::allocator<int>;
SYNDICATE_TEMPLATE template class SYNDICATE_API std::vector<int>;
SYNDICATE_TEMPLATE template class SYNDICATE_API std::vector<char>;

GLenum SYNDICATE_API glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

#endif