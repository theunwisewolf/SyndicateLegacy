#include "Camera2D.h"

namespace Syndicate { namespace Graphics {

Camera2D::Camera2D() :
	m_ModalMatrix(1.0f),
	m_Scale(1.0f, 1.0f),
	m_Position(0.0f, 0.0f),
	m_Update(true),
	m_OrthoPrMatrix(1.0f),
	m_CameraMoveSpeed(1.0f),
	m_CameraScaleSpeed(1.0f)
{
}

void Camera2D::Initialize(const Maths::Vector2& position, const Maths::Vector2& scale)
{
	KeyEvent::i()->BindKeyDown(Keys::KEY_RIGHT, Callback([this]() {
		m_Position.x -= 1;
		m_Update = true;
	}));

	KeyEvent::i()->BindKeyDown(Keys::KEY_LEFT, Callback([this]() {
		m_Position.x += 1;
		m_Update = true;
	}));

	KeyEvent::i()->BindKeyDown(Keys::KEY_DOWN, Callback([this]() {
		m_Position.y += 1;
		m_Update = true;
	}));

	KeyEvent::i()->BindKeyDown(Keys::KEY_UP, Callback([this]() {
		m_Position.y -= 1;
		m_Update = true;
	}));

	KeyEvent::i()->BindKeyDown(Keys::KEY_Q, Callback([this]() {
		m_Scale.x += 0.001f;
		m_Scale.y += 0.001f;
		m_Update = true;
	}));

	KeyEvent::i()->BindKeyDown(Keys::KEY_W, Callback([this]() {
		m_Scale.x -= 0.001f;
		m_Scale.y -= 0.001f;
		m_Update = true;
	}));

	this->m_Position = position;
	this->m_Scale = scale;

	Maths::Matrix4 translation = Maths::Matrix4::Translation(Maths::Vector3(this->m_Position.x, this->m_Position.y, 0.0f));
	Maths::Matrix4 scaleMatrix = Maths::Matrix4::Scale(Maths::Vector3(this->m_Scale.x, this->m_Scale.y, 1.0f));

	this->m_OrthoPrMatrix = Maths::Matrix4::Orthographic(0.0f, (float)Window::i()->getWidth(), 0.0f, (float)Window::i()->getHeight(), 1.0f, -1.0f);

	this->m_ModalMatrix = m_OrthoPrMatrix  * (translation * scaleMatrix);
}

void Camera2D::Update()
{
	if (m_Update)
	{
		float newX = -(m_Position.x * this->m_CameraMoveSpeed) + (float)Window::i()->getWidth() / 2;
		float newY = -(m_Position.y * this->m_CameraMoveSpeed) + (float)Window::i()->getHeight() / 2;

		Maths::Matrix4 translation = Maths::Matrix4::Translation(Maths::Vector3(newX, newY, 0.0f));
		Maths::Matrix4 scaleMatrix = Maths::Matrix4::Scale(Maths::Vector3(this->m_Scale.x * this->m_CameraScaleSpeed, this->m_Scale.y * this->m_CameraScaleSpeed, 1.0f));

		this->m_ModalMatrix = m_OrthoPrMatrix * (translation * scaleMatrix);
		m_Update = false;
	}
}

Maths::Vector2 Camera2D::screenToWorld(Maths::Vector2 coordinates)
{
	coordinates -= Maths::Vector2((float)Window::i()->getWidth() / 2, (float)Window::i()->getHeight() / 2);
	coordinates /= this->m_Scale;
	coordinates += m_Position;

	return coordinates;
}

Camera2D::~Camera2D()
{

}

} }