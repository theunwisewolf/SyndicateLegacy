#ifndef COMMON_H_
#define COMMON_H_

#include <GL/glew.h>
#include <iostream>
#include <string>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

#endif