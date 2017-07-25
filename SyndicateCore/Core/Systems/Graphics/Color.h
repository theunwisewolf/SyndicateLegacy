#ifndef COLOR_H_
#define COLOR_H_

#include <Common.h>

#include <string>
#include <GLM/vec4.hpp>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Color
{
private:
	bool m_IsNormalized;
	glm::vec4 m_ColorComponents;

public:
	Color(float r, float g, float b, float a = 1.0f);
	Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
	Color(const glm::vec4& color);
	Color(const unsigned int& color, bool autoSetAlpha = true);

	const float& Red() const { return m_ColorComponents.x; }
	const float& Green() const { return m_ColorComponents.y; }
	const float& Blue() const { return m_ColorComponents.z; }
	const float& Alpha() const { return m_ColorComponents.w; }

	float RedN() const { return m_ColorComponents.x / 255.0f; }
	float GreenN() const { return m_ColorComponents.y / 255.f; }
	float BlueN() const { return m_ColorComponents.z / 255.0f; }
	float AlphaN() const { return m_ColorComponents.w / 255.0f; }

	glm::vec4 Normalize() const;
	unsigned int Pack(const std::string& format = "abgr") const;

	~Color();
};

}}

#endif