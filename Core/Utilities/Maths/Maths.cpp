#include "Maths.h"

namespace Venus { namespace Maths {

float Math::toRadians(float degrees)
{
	return degrees * (M_PI / 180.0f);
}

float Math::Tan(float radians)
{
	return tan(radians);
}

float Math::Sin(float radians)
{
	return sin(radians);
}

float Math::Cos(float radians)
{
	return cos(radians);
}

}}