#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <Systems/Graphics/Layers/Layer.h>
#include <Systems/Graphics/BatchRenderer2D.h>

namespace Venus { namespace Graphics {

class TileLayer : public Layer
{
public:
	TileLayer(Shader* shader);
	~TileLayer();
};

}}

#endif