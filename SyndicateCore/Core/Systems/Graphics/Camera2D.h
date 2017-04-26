#ifndef CAMERA2D_H_
#define CAMERA2D_H_

#include <Common.h>

#include <Systems/Window.h>
#include <Utilities/Maths/Maths.h>

namespace Syndicate { namespace Graphics { 

class SYNDICATE_API Camera2D
{
private:
	// Orthographic projection matrix
	Maths::Matrix4 m_OrthoPrMatrix;

	// Camera Transformation Matrix
	Maths::Matrix4 m_ModalMatrix;

	// Camera scale
	Maths::Vector2 m_Scale;

	// Camera position
	Maths::Vector2 m_Position;

	// Speed of camera movement & scale
	float m_CameraMoveSpeed;
	float m_CameraScaleSpeed;

	// Update marker
	bool m_Update;

public:
	Camera2D();
	~Camera2D();

	void setTransformationMatrix(const Maths::Matrix4& matrix)  { this->m_ModalMatrix = matrix; m_Update = true;  }
	void setScale(const Maths::Vector2& scale)				    { this->m_Scale = scale; m_Update = true; }
	void setPosition(const Maths::Vector2& position)			{ this->m_Position = position; m_Update = true; }
	void setMovementSpeed(float speed)							{ this->m_CameraMoveSpeed = speed; }
	void setScaleSpeed(float speed)								{ this->m_CameraScaleSpeed = speed; }

	inline Maths::Matrix4 getCameraMatrix()	const				{ return this->m_ModalMatrix; }
	inline Maths::Vector2 getPosition() const					{ return this->m_Position; }
	inline Maths::Vector2 getScale() const						{ return this->m_Scale; }
	inline float getMovementSpeed() const						{ return this->m_CameraMoveSpeed; }
	inline float getScaleSpeed() const							{ return this->m_CameraScaleSpeed; }

	void Initialize(const Maths::Vector2& position, const Maths::Vector2& scale);
	void Update();

	Maths::Vector2 screenToWorld(Maths::Vector2 coordinates);
};

} }

#endif