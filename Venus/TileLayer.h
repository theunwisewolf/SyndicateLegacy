#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <Systems/Graphics/Layers/Layer.h>
#include <Systems/Graphics/Renderers/BatchRenderer2D.h>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace Syndicate { namespace Graphics {

class TileLayer : public Layer
{
public:
	TileLayer();
	TileLayer(Shader* shader);
	void SetProjectionMatrix();
	void SetProjectionMatrix(const glm::mat4& prMatrix);
	~TileLayer();
};

}}

#endif