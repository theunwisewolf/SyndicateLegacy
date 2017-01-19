#include "TileLayer.h"

namespace Venus { namespace Graphics {

TileLayer::TileLayer(Shader* shader)
	: Layer(new BatchRenderer2D(), shader, Maths::Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f,-1.0f, 1.0f))
{

}

TileLayer::~TileLayer()
{

}

}}
