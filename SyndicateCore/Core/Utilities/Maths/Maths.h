#ifndef _MATHS_H
#define _MATHS_H

#include <Common.h>

// Additional Header Files
#define _USE_MATH_DEFINES 1

#include <math.h>

namespace Syndicate { namespace Maths {

class SYNDICATE_API Math
{
public:
	static float toRadians(float degrees);
	static float toDegrees(float degrees);
	static float Tan(float radians);
	static float Sin(float radians);
	static float Cos(float radians);
};

}}

#endif