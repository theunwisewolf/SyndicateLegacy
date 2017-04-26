#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <Systems/Graphics/Layers/Layer.h>
#include <Systems/Graphics/Renderers/BatchRenderer2D.h>

namespace Syndicate { namespace Graphics {

class TileLayer : public Layer
{
public:
	TileLayer();
	TileLayer(Shader* shader);
	void SetProjectionMatrix();
	void SetProjectionMatrix(const Maths::Matrix4& prMatrix);
	~TileLayer();
};

}}

#endif