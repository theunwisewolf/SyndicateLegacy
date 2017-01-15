#include "Vector4.h"

namespace Venus { namespace Maths {

Vector4::Vector4(const float& x, const float& y, const float& z, const float& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4& Vector4::Add(const Vector4& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;

	return *this;
}

Vector4& Vector4::Subtract(const Vector4& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;

	return *this;
}

Vector4& Vector4::Multiply(const Vector4& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->w *= vec.w;

	return *this;
}

Vector4& Vector4::Divide(const Vector4& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	this->w /= vec.w;

	return *this;
}

bool Vector4::operator==(const Vector4& vec)
{
	if (
		this->x == vec.x &&
		this->y == vec.y &&
		this->z == vec.z &&
		this->w == vec.w
		)
	{
		return true;
	}

	return false;
}

bool Vector4::operator!=(const Vector4& vec)
{
	if (
		this->x != vec.x ||
		this->y != vec.y ||
		this->z != vec.z ||
		this->w != vec.w
		)
	{
		return true;
	}

	return false;
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
	return this->Add(vec);
}

Vector4& Vector4::operator-=(const Vector4& vec)
{
	return this->Subtract(vec);
}

Vector4& Vector4::operator*=(const Vector4& vec)
{
	return this->Multiply(vec);
}

Vector4& Vector4::operator/=(const Vector4& vec)
{
	return this->Divide(vec);
}

Vector4& Vector4::operator++()
{
	this->x++;
	this->y++;
	this->z++;
	this->w++;

	return *this;
}

Vector4 Vector4::operator++(int)
{
	Vector4 temp(*this);
	operator++();

	return temp;
}

Vector4& Vector4::operator--()
{
	this->x--;
	this->y--;
	this->z--;
	this->w--;

	return *this;
}

Vector4 Vector4::operator--(int)
{
	Vector4 temp(*this);
	operator--();

	return temp;
}


Vector4 operator+(Vector4 vec1, const Vector4& vec2)
{
	vec1 += vec2;
	return vec1;
}

Vector4 operator-(Vector4 vec1, const Vector4& vec2)
{
	vec1 -= vec2;
	return vec1;
}

Vector4 operator*(Vector4 vec1, const Vector4& vec2)
{
	vec1 *= vec2;
	return vec1;
}

Vector4 operator/(Vector4 vec1, const Vector4& vec2)
{
	vec1 /= vec2;
	return vec1;
}

std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
{
	stream << "Vector4( " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " )";
	return stream;
}

}}