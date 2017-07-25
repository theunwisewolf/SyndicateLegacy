#include "Maths.h"

namespace Syndicate { namespace Maths {

float Math::toRadians(float degrees)
{
	return (float)(degrees * (M_PI / 180.0f));
}

float Math::toDegrees(float radians)
{
	return (float)(radians * (180 / M_PI));
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