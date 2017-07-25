#ifndef BOX_H_
#define BOX_H_

#include <Systems/Graphics/Color.h>

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

#include <Box2D/Box2D.h>

using namespace Syndicate;
using namespace Graphics;

class Box
{
private:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	Color m_Color;

	b2Body* m_Body;
	b2Fixture* m_Fixture;

public:
	Box(const Box& box);
	Box(b2World* world, const glm::vec3& position, const glm::vec2& size, Color color);

	const glm::vec3& GetPosition() const { return this->m_Position; }
	const glm::vec2& GetSize()	 const { return this->m_Size; }
	const Color& GetColor()		 const { return this->m_Color; }
	b2Body* GetBody()			 const { return this->m_Body; }
	b2Fixture* GetFixture()		 const { return this->m_Fixture; }

	~Box();
};

#endif