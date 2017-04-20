#include "Color.h"

namespace Syndicate { namespace Graphics {

Color::Color(const unsigned int& color, bool autoSetAlpha)
{
	m_IsNormalized = false;

	int a = (color & 0xff000000) >> 24;
	int b = (color & 0xff0000) >> 16;
	int g = (color & 0xff00) >> 8;
	int r = (color & 0xff);

	if (!a && autoSetAlpha)
		a = 255;

	m_ColorComponents = Maths::Vector4(r, g, b, a);
}

Color::Color(float r, float g, float b, float a)
{
	m_IsNormalized = true;
	m_ColorComponents = Maths::Vector4(r, g, b, a);
}

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	m_IsNormalized = false;
	m_ColorComponents = Maths::Vector4((float)r, (float)g, (float)b, (float)a);
}

Color::Color(const Maths::Vector4& color)
{
	m_ColorComponents = color;
}

Maths::Vector4 Color::Normalize() const
{
	if (m_IsNormalized)
		return m_ColorComponents;

	return Maths::Vector4(m_ColorComponents.x / 255.0f, m_ColorComponents.y / 255.0f, m_ColorComponents.z / 255.0f, m_ColorComponents.w / 255.0f);
}

unsigned int Color::Pack(const std::string& format) const
{
	if (format == "rgba")
	{
		return ((int)m_ColorComponents.x << 24 | (int)m_ColorComponents.y << 16 | (int)m_ColorComponents.z << 8 | (int)m_ColorComponents.w);
	}

	return ((int)m_ColorComponents.w << 24 | (int)m_ColorComponents.z << 16 | (int)m_ColorComponents.y << 8 | (int)m_ColorComponents.x);
}

Color::~Color()
{
}

}}