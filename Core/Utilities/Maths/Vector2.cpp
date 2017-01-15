#include "Vector2.h"

namespace Venus {
	namespace Maths {

Vector2::Vector2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2::Vector2(Vector2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

Vector2::Vector2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Vector2& Vector2::Add(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2& Vector2::Multiply(const Vector2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2& Vector2::Divide(const Vector2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

bool Vector2::operator==(const Vector2& vec)
{
	if (
		this->x == vec.x &&
		this->y == vec.y
		)
	{
		return true;
	}

	return false;
}

bool Vector2::operator!=(const Vector2& vec)
{
	if (
		this->x != vec.x ||
		this->y != vec.y 
		)
	{
		return true;
	}

	return false;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	return this->Add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	return this->Subtract(vec);
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	return this->Multiply(vec);
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	return this->Divide(vec);
}

Vector2& Vector2::operator++()
{
	this->x++;
	this->y++;

	return *this;
}

Vector2 Vector2::operator++(int)
{
	Vector2 temp(*this);
	operator++();

	return temp;
}

Vector2& Vector2::operator--()
{
	this->x--;
	this->y--;

	return *this;
}

Vector2 Vector2::operator--(int)
{
	Vector2 temp(*this);
	operator--();

	return temp;
}


Vector2 operator+(Vector2 vec1, const Vector2& vec2)
{
	vec1 += vec2;
	return vec1;
}

Vector2 operator-(Vector2 vec1, const Vector2& vec2)
{
	vec1 -= vec2;
	return vec1;
}

Vector2 operator*(Vector2 vec1, const Vector2& vec2)
{
	vec1 *= vec2;
	return vec1;
}

Vector2 operator/(Vector2 vec1, const Vector2& vec2)
{
	vec1 /= vec2;
	return vec1;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << "Vector2( " << vec.x << ", " << vec.y << " )";
	return stream;
}

Vector2::~Vector2()
{
}

	}
}