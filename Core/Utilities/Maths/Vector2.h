#ifndef Vector2_H_
#define Vector2_H_

#include <Common.h>

#include <iostream>

namespace Venus {
	namespace Maths {

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(const Vector2&);
	Vector2(const float& x, const float& y);

	Vector2& Add(const Vector2& vec);
	Vector2& Subtract(const Vector2& vec);
	Vector2& Multiply(const Vector2& vec);
	Vector2& Divide(const Vector2& vec);

	bool operator==(const Vector2& vec);
	bool operator!=(const Vector2& vec);

	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator/=(const Vector2& vec);
	Vector2& operator++();
	Vector2& operator--();
	Vector2  operator++(int);
	Vector2  operator--(int);

	friend Vector2 operator+(Vector2 vec1, const Vector2& vec2);
	friend Vector2 operator-(Vector2 vec1, const Vector2& vec2);
	friend Vector2 operator*(Vector2 vec1, const Vector2& vec2);
	friend Vector2 operator/(Vector2 vec1, const Vector2& vec2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& Vector2);

	~Vector2();
};

	}
}

#endif