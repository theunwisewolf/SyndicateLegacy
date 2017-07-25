#include "Box.h"

Box::Box(const Box& box) :
	m_Color(box.m_Color),
	m_Position(glm::vec3(box.m_Position.x, box.m_Position.y, box.m_Position.z)),
	m_Size(box.m_Size),
	m_Body(box.m_Body),
	m_Fixture(box.m_Fixture)
{

}

Box::Box(b2World* world, const glm::vec3& position, const glm::vec2& size, Color color)
	: m_Color(color)
{
	this->m_Position = position;
	this->m_Size = size;

	b2BodyDef boxDef;
	boxDef.type = b2_dynamicBody;
	boxDef.position.Set(this->m_Position.x, this->m_Position.y);
	
	m_Body = world->CreateBody(&boxDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(this->m_Size.x / 2.0f, this->m_Size.y / 2.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.friction = 0.3f;

	m_Fixture = m_Body->CreateFixture(&boxFixtureDef);
}

Box::~Box()
{

}