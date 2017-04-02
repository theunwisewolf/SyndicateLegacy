#include "Vector3.h"

namespace Syndicate {
	namespace Maths {

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

Vector3::Vector3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3& Vector3::Add(const Vector3& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;

	return *this;
}

Vector3& Vector3::Subtract(const Vector3& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;

	return *this;
}

Vector3& Vector3::Multiply(const Vector3& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;

	return *this;
}

Vector3& Vector3::Divide(const Vector3& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;

	return *this;
}

bool Vector3::operator==(const Vector3& vec)
{
	if (
		this->x == vec.x &&
		this->y == vec.y &&
		this->z == vec.z 
		)
	{
		return true;
	}

	return false;
}

bool Vector3::operator!=(const Vector3& vec)
{
	if (
		this->x != vec.x ||
		this->y != vec.y ||
		this->z != vec.z
		)
	{
		return true;
	}

	return false;
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	return this->Add(vec);
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
	return this->Subtract(vec);
}

Vector3& Vector3::operator*=(const Vector3& vec)
{
	return this->Multiply(vec);
}

Vector3& Vector3::operator/=(const Vector3& vec)
{
	return this->Divide(vec);
}

Vector3& Vector3::operator++()
{
	this->x++;
	this->y++;
	this->z++;

	return *this;
}

Vector3 Vector3::operator++(int)
{
	Vector3 temp(*this);
	operator++();

	return temp;
}

Vector3& Vector3::operator--()
{
	this->x--;
	this->y--;
	this->z--;

	return *this;
}

Vector3 Vector3::operator--(int)
{
	Vector3 temp(*this);
	operator--();

	return temp;
}


Vector3 operator+(Vector3 vec1, const Vector3& vec2)
{
	vec1 += vec2;
	return vec1;
}

Vector3 operator-(Vector3 vec1, const Vector3& vec2)
{
	vec1 -= vec2;
	return vec1;
}

Vector3 operator*(Vector3 vec1, const Vector3& vec2)
{
	vec1 *= vec2;
	return vec1;
}

Vector3 operator/(Vector3 vec1, const Vector3& vec2)
{
	vec1 /= vec2;
	return vec1;
}

std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
	stream << "Vector3( " << vec.x << ", " << vec.y << ", " << vec.z << " )";
	return stream;
}

Vector3::~Vector3()
{
}

	}
}