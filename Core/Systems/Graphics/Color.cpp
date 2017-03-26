#include "Color.h"

namespace Venus { namespace Graphics {

Color::Color(float r, float g, float b, float a)
{
	m_IsNormalized = true;
	m_ColorComponents = Maths::Vector4(r, g, b, a);
}

Color::Color(int r, int g, int b, int a)
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