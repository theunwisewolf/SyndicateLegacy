#ifndef COLOR_H_
#define COLOR_H_

#include <string>
#include <Utilities/Maths/Vector4.h>

namespace Venus { namespace Graphics {

class Color
{
private:
	bool m_IsNormalized;
	Maths::Vector4 m_ColorComponents;

public:
	Color(float r, float g, float b, float a = 1.0f);
	Color(int r, int g, int b, int a = 255);
	Color(const Maths::Vector4& color);

	const float& Red() const { return m_ColorComponents.x; }
	const float& Green() const { return m_ColorComponents.y; }
	const float& Blue() const { return m_ColorComponents.z; }
	const float& Alpha() const { return m_ColorComponents.w; }

	const float& RedN() const { return m_ColorComponents.x / 255.0f; }
	const float& GreenN() const { return m_ColorComponents.y / 255.f; }
	const float& BlueN() const { return m_ColorComponents.z / 255.0f; }
	const float& AlphaN() const { return m_ColorComponents.w / 255.0f; }

	const Maths::Vector4& Normalize() const;
	const unsigned int& Pack(const std::string& format = "abgr") const;

	~Color();
};

}}

#endif