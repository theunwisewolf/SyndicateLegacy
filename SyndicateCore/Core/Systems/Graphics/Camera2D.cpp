#include "Camera2D.h"

namespace Syndicate { namespace Graphics {

Camera2D::Camera2D() :
	m_ModalMatrix(1.0f),
	m_Scale(1.0f, 1.0f),
	m_Position(0.0f, 0.0f),
	m_Update(true),
	m_OrthoPrMatrix(1.0f),
	m_CameraMoveSpeed(1.0f),
	m_CameraScaleSpeed(1.0f),
	m_Angle(0.0f)
{
}

void Camera2D::Initialize(const glm::vec2& position, const glm::vec2& scale)
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

	KeyEvent::i()->BindKeyDown(Keys::KEY_E, Callback([this]() {
		m_Angle++;
		m_Update = true;
		//this->OnRotate(m_Angle);
	}));

	KeyEvent::i()->BindKeyDown(Keys::KEY_R, Callback([this]() {
		m_Angle--;
		m_Update = true;
		this->OnRotate(m_Angle);
	}));

	this->m_Position = position;
	this->m_Scale = scale;

	this->m_OrthoPrMatrix = glm::ortho(0.0f, (float)Window::i()->getWidth(), 0.0f, (float)Window::i()->getHeight());
	
	glm::vec3 translate(this->m_Position.x, this->m_Position.y, 0.0f);
	glm::vec3 _scale(this->m_Scale.x, this->m_Scale.y, 1.0f);
	glm::vec3 rotation(0.0f, 0.0f, 1.0f); // Along the z-axis

	// Below may seem confusing, but what happens with this code:
	// final = translate * scale * rotate
	// Which means rotate first, then scale, then translate and this 
	// is the correct order to perform a transformation
	this->m_ModalMatrix = glm::translate(this->m_OrthoPrMatrix, translate);
	this->m_ModalMatrix = glm::scale(this->m_ModalMatrix, _scale);
	this->m_ModalMatrix = glm::rotate(this->m_ModalMatrix, m_Angle * this->m_CameraMoveSpeed, rotation);
}

void Camera2D::Update()
{
	if (m_Update)
	{
		float newX = -(m_Position.x * this->m_CameraMoveSpeed) + (float)Window::i()->getWidth() / 2;
		float newY = -(m_Position.y * this->m_CameraMoveSpeed) + (float)Window::i()->getHeight() / 2;

		glm::vec3 translate(newX, newY, 0.0f);
		glm::vec3 _scale(this->m_Scale.x * this->m_CameraMoveSpeed, this->m_Scale.y * this->m_CameraMoveSpeed, 1.0f);
		glm::vec3 rotation(0.0f, 0.0f, 1.0f); // Along the z-axis

		/*this->m_ModalMatrix = glm::translate(this->m_OrthoPrMatrix, translate);
		this->m_ModalMatrix = glm::scale(this->m_ModalMatrix, _scale);
		this->m_ModalMatrix = glm::rotate(this->m_ModalMatrix, m_Angle * this->m_CameraMoveSpeed * 0.001f, rotation);*/

		glm::mat4 translatemat = glm::translate(glm::mat4(1.0f), translate);
		glm::mat4 scalemat = glm::scale(glm::mat4(1.0f), _scale);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), m_Angle * this->m_CameraMoveSpeed * 0.001f, rotation);

		this->m_ModalMatrix = this->m_OrthoPrMatrix * translatemat * scalemat * rotate;

		//this->m_ModalMatrix = glm::scale(glm::mat4(1.0f), _scale) * this->m_ModalMatrix;

		m_Update = false;
	}
}

glm::vec2 Camera2D::screenToWorld(glm::vec2 coordinates)
{
	coordinates -= glm::vec2((float)Window::i()->getWidth() / 2, (float)Window::i()->getHeight() / 2);
	coordinates /= this->m_Scale;
	coordinates += this->m_Position;

	return coordinates;
}

void Camera2D::OnMove(glm::vec3 distance, glm::vec3 direction)
{

}

void Camera2D::OnScale(float scale)
{

}

void Camera2D::OnRotate(float angle)
{
	(this->m_OnRotateCallback->getCallback())();
}

Camera2D::~Camera2D()
{

}

} }