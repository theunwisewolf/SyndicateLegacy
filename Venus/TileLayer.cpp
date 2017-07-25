#include "TileLayer.h"

namespace Syndicate { namespace Graphics {

TileLayer::TileLayer()
{

}

TileLayer::TileLayer(Shader* shader)
	: Layer(synnew BatchRenderer2D(), shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f))
{

}

void TileLayer::SetProjectionMatrix()
{
	Layer::SetProjectionMatrix(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f));
}

void TileLayer::SetProjectionMatrix(const glm::mat4& prMatrix)
{
	Layer::SetProjectionMatrix(prMatrix);
}

TileLayer::~TileLayer()
{

}

}}
