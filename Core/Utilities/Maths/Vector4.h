#ifndef VECTOR4_H_
#define VECTOR4_H_

#include <iostream>

namespace Venus {
	namespace Maths {

class Vector4
{
public: 
	float x;
	float y;
	float z; 
	float w;

	Vector4() = default;
	Vector4(const float& x, const float& y, const float& z, const float& w);

	Vector4& Add(const Vector4& vec);
	Vector4& Subtract(const Vector4& vec);
	Vector4& Multiply(const Vector4& vec);
	Vector4& Divide(const Vector4& vec);

	bool operator==(const Vector4& vec);
	bool operator!=(const Vector4& vec);

	Vector4& operator+=(const Vector4& vec);
	Vector4& operator-=(const Vector4& vec);
	Vector4& operator*=(const Vector4& vec);
	Vector4& operator/=(const Vector4& vec);
	Vector4& operator++();
	Vector4& operator--();
	Vector4  operator++(int);
	Vector4  operator--(int);

	friend Vector4 operator+(Vector4 vec1, const Vector4& vec2);
	friend Vector4 operator-(Vector4 vec1, const Vector4& vec2);
	friend Vector4 operator*(Vector4 vec1, const Vector4& vec2);
	friend Vector4 operator/(Vector4 vec1, const Vector4& vec2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector4& Vector4);

	~Vector4() = default;
};

	}
}

#endif