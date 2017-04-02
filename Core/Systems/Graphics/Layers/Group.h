#ifndef GROUP_H_
#define GROUP_H_

#include <Common.h>

#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <vector>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Group : public Renderable2D
{
private:
	std::vector<Renderable2D*> m_Sprites;
	Maths::Matrix4 m_TransformationMatrix;

public:
	Group(const Maths::Matrix4& transform);
	void Submit(Renderer2D* renderer) const override;
	void Add(Renderable2D* sprite);
	~Group();
};

} }

#endif