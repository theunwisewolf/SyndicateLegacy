#ifndef GROUP_H_
#define GROUP_H_

#include <Common.h>

#include <GLM/mat4x4.hpp>
#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <vector>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Group : public Renderable2D
{
private:
	unsigned int m_ChildrenCount = 0;

private:
	std::vector<Renderable2D*> m_Sprites;
	std::map<std::string, int> m_ChildrenMap;
	glm::mat4 m_TransformationMatrix;

public:
	Group(const glm::mat4& transform);
	void Submit(Renderer2D* renderer) const override;
	unsigned int Add(Renderable2D* sprite);
	void Add(std::string name, Renderable2D* sprite);
	~Group();

	Renderable2D* GetSprite(std::string name);
	Renderable2D* GetSprite(int index);

	unsigned int getChildrenCount() const { return this->m_ChildrenCount; }
};

} }

#endif