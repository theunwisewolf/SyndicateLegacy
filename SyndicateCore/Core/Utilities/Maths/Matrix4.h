#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <Common.h>
#include <Utilities\Maths\Maths.h>

namespace Syndicate { namespace Maths {

class SYNDICATE_API Matrix4
{
public:
	union {
		float elements[4 * 4];
		Vector4 columns[4];
	};

	Matrix4();
	Matrix4(float diagonal);

	static Matrix4 Scale(const Vector3& scale);
	static Matrix4 Rotation(float angle, const Vector3& axis);
	static Matrix4 Translation(const Vector3& translation);

	static Matrix4 Identity();
	static Matrix4 Perspective(float fov, float aspectRatio, float _near, float _far);
	static Matrix4 Orthographic(float left, float right, float top, float bottom, float _near, float _far);

	static Matrix4 Translate(Matrix4 matrix, const Matrix4& translationMatrix);

	Matrix4& Multiply(const Matrix4& mat4);
	Matrix4& Invert();
	
	Matrix4& operator*=(const Matrix4& mat4);

	friend Matrix4 operator*(Matrix4 a, const Matrix4& b);
	friend std::ostream& operator<<(std::ostream& stream, const Matrix4& mat4);

	Vector2 Multiply(const Vector2& vec2) const;
	Vector3 Multiply(const Vector3& vec3) const;
	Vector4 Multiply(const Vector4& vec4) const;

	friend Vector2 operator*(const Matrix4& a, const Vector2& b);
	friend Vector3 operator*(const Matrix4& a, const Vector3& b);
	friend Vector4 operator*(const Matrix4& a, const Vector4& b);

	~Matrix4();
};

}}

#endif