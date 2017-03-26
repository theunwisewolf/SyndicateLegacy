#ifndef _MATHS_H
#define _MATHS_H

#include <Common.h>

#include <Utilities/Maths/Vector2.h>
#include <Utilities/Maths/Vector3.h>
#include <Utilities/Maths/Vector4.h>
#include <Utilities/Maths/Matrix4.h>

// Additional Header Files
#define _USE_MATH_DEFINES 1

#include <math.h>

namespace Venus { namespace Maths {

class Math
{
public:
	static float toRadians(float degrees);
	static float Tan(float radians);
	static float Sin(float radians);
	static float Cos(float radians);
};

}}

#endif