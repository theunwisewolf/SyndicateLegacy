#include "TileLayer.h"

namespace Syndicate { namespace Graphics {

TileLayer::TileLayer()
{

}

TileLayer::TileLayer(Shader* shader)
	: Layer(synnew BatchRenderer2D(), shader, Maths::Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f,-1.0f, 1.0f))
{

}

void TileLayer::SetProjectionMatrix()
{
	Layer::SetProjectionMatrix(Maths::Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f, -1.0f, 1.0f));
}

TileLayer::~TileLayer()
{

}

}}
