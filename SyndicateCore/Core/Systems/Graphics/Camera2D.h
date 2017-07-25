#ifndef CAMERA2D_H_
#define CAMERA2D_H_

#include <Common.h>

#include <Systems/Window.h>
#include <GLM/mat4x4.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <functional>
#include <Utilities/Callback.h>

namespace Syndicate { namespace Graphics { 

class SYNDICATE_API Camera2D
{
private:
	// Camera view angle
	float m_Angle;

	// Orthographic projection matrix
	glm::mat4 m_OrthoPrMatrix;

	// Camera Transformation Matrix
	glm::mat4 m_ModalMatrix;

	// Camera scale
	glm::vec2 m_Scale;

	// Camera position
	glm::vec2 m_Position;

	// Speed of camera movement & scale
	float m_CameraMoveSpeed;
	float m_CameraScaleSpeed;

	// Update marker
	bool m_Update;

	Callback* m_OnRotateCallback;
	Callback* m_OnMoveCallback;
	Callback* m_OnScaleCallback;

public:
	Camera2D();
	~Camera2D();

	void setTransformationMatrix(const glm::mat4& matrix)	{ this->m_ModalMatrix = matrix; m_Update = true;  }
	void setScale(const glm::vec2& scale)					{ this->m_Scale = scale; m_Update = true; }
	void setPosition(const glm::vec2& position)				{ this->m_Position = position; m_Update = true; }
	void setMovementSpeed(float speed)						{ this->m_CameraMoveSpeed = speed; }
	void setScaleSpeed(float speed)							{ this->m_CameraScaleSpeed = speed; }

	inline glm::mat4 getCameraMatrix()	const				{ return this->m_ModalMatrix; }
	inline glm::vec2 getPosition() const					{ return this->m_Position; }
	inline glm::vec2 getScale() const						{ return this->m_Scale; }
	inline float getMovementSpeed() const					{ return this->m_CameraMoveSpeed; }
	inline float getScaleSpeed() const						{ return this->m_CameraScaleSpeed; }

	/**
	 * @param	Vector2		Position of the camera
	 * @param	Vector2		Scale
	 */
	void Initialize(const glm::vec2& position, const glm::vec2& scale);
	void Update();

	glm::vec2 screenToWorld(glm::vec2 coordinates);

	void OnRotate(float angle);
	void OnMove(glm::vec3 distance, glm::vec3 direction);
	void OnScale(float scale);
};

} }

#endif