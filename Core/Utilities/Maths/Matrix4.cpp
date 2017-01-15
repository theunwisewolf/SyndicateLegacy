#include "Matrix4.h"

namespace Venus { namespace Maths {

Matrix4::Matrix4()
{
	for (int i = 0; i < 4 * 4; ++i)
		this->elements[i] = 0.0f;
}

Matrix4::Matrix4(float diagonal)
{
	for (int i = 0; i < 4 * 4; ++i)
		this->elements[i] = !( i % 4 - i / 4 ) ? diagonal : 0.0f;
}

Matrix4 Matrix4::Identity()
{
	return Matrix4(1.0f);
}

Matrix4& Matrix4::Multiply(const Matrix4& mat4)
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; ++e)
			{
				sum += this->elements[i + e * 4] * mat4.elements[e + j * 4];
			}

			this->elements[i + j * 4] = sum;
		}
	}

	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& mat4)
{
	return this->Multiply(mat4);
}

Matrix4 operator*(Matrix4 a, const Matrix4& b)
{
	return a.Multiply(b);
}

std::ostream& operator<<(std::ostream& stream, const Matrix4& mat4)
{
	stream << "Matrix4(" << std::endl;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			stream << mat4.elements[i + j * 4] << " ";
		}

		stream << std::endl;
	}

	stream << ")" << std::endl;

	return stream;
}

Matrix4 Matrix4::Orthographic(float left, float right, float top, float bottom, float near, float far)
{
	Matrix4 result(1.0f);

	// Diagonal elements
	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (near - far);

	// Elements of the last column
	result.elements[0 + 3 * 4] = (left + right) / (left - right);
	result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
	result.elements[2 + 3 * 4] = (far + near) / (near - far);

	return result;
}

Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float near, float far)
{
	Matrix4 result(1.0f);

	float q = 1.0f / Math::Tan(Math::toRadians(0.5f * fov));
	float a = 1 / aspectRatio;
	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[3 + 2 * 4] = -1.0f;
	result.elements[2 + 3 * 4] = c;

	return result;
}

Matrix4 Matrix4::Translation(const Vector3& translation)
{
	Matrix4 result(1.0f);

	result.elements[0 + 3 * 4] = translation.x;
	result.elements[1 + 3 * 4] = translation.y;
	result.elements[2 + 3 * 4] = translation.z;

	return result;
}

Matrix4 Matrix4::Scale(const Vector3& scale)
{
	Matrix4 result(1.0f);

	result.elements[0 + 0 * 4] = scale.x;
	result.elements[1 + 1 * 4] = scale.y;
	result.elements[2 + 2 * 4] = scale.z;

	return result;
}

Matrix4 Matrix4::Rotation(float angle, const Vector3& axis)
{
	Matrix4 result(1.0f);

	float c = Math::Cos(Math::toRadians(angle));
	float s = Math::Sin(Math::toRadians(angle));
	float lc = 1 - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	result.elements[0 + 0 * 4] = x * lc + c;
	result.elements[1 + 0 * 4] = y * x * lc + z * s;
	result.elements[2 + 0 * 4] = x * z * lc - y * s;

	result.elements[0 + 1 * 4] = x * y * lc - z * s;
	result.elements[1 + 1 * 4] = y * lc + c;
	result.elements[2 + 1 * 4] = y * z * lc + x * s;

	result.elements[0 + 2 * 4] = x * z * lc + y * s;
	result.elements[1 + 2 * 4] = y * z * lc - x * s;
	result.elements[2 + 2 * 4] = z * lc + c;

	return result;
}

Matrix4::~Matrix4()
{
}

}}