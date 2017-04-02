#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <Common.h>

#include <Systems/Graphics/Layers/Layer.h>
#include <Systems/Graphics/Renderers/BatchRenderer2D.h>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API TileLayer : public Layer
{
public:
	TileLayer(Shader* shader);
	~TileLayer();
};

}}

#endif