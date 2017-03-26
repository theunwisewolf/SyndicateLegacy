#ifndef COMMON_H_
#define COMMON_H_

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

GLenum glCheckError_(const char *file, int line);

#define new DBG_NEW

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#define glCheckError() glCheckError_(__FILE__, __LINE__) 


#endif