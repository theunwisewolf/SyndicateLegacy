#ifndef COMMON_H_
#define COMMON_H_

#include <glew.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define SYNDICATE_VERSION 100

#define SYNDICATE_VERSION_MINOR 0
#define SYNDICATE_VERSION_MAJOR 1

#if defined(DEBUG) | defined(_DEBUG)
	#define SYNDICATE_DEBUG
#endif

#ifdef SYNDICATE_DEBUG 
	#include <cstdlib>
	#include <crtdbg.h>

	#define synnew new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
	#define synnew new
#endif

#ifdef WIN32
#define SYNDICATE_WINDOWS
#endif

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

GLenum SYNDICATE_API glCheckError_(const char* function, const char *file, int line);

#define glCheckError(x) glCheckError_(#x, __FILE__, __LINE__) 

#ifdef SYNDICATE_DEBUG
#define GL(func)	\
	glCheckError(#func); \
	func;
#else
#define GL(func) func;
#endif

typedef unsigned char BYTE;

typedef unsigned char		U8;
typedef unsigned short		U16;
typedef unsigned int		U32;
typedef unsigned long long  U64;

typedef char				S8;
typedef short				S16;
typedef int					S32;
typedef long long			S64;

enum class Position { LEFT, CENTER, RIGHT };

#endif