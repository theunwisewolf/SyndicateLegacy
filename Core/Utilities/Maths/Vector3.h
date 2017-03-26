#ifndef Vector3_H_
#define Vector3_H_

#include <Common.h>

#include <iostream>

namespace Venus {
	namespace Maths {

class Vector3
{
public:
	float x;
	float y;
	float z;
	
	Vector3();
	Vector3(Vector3&);
	Vector3(const float& x, const float& y, const float& z);

	Vector3& Add(const Vector3& vec);
	Vector3& Subtract(const Vector3& vec);
	Vector3& Multiply(const Vector3& vec);
	Vector3& Divide(const Vector3& vec);

	bool operator==(const Vector3& vec);
	bool operator!=(const Vector3& vec);

	Vector3& operator+=(const Vector3& vec);
	Vector3& operator-=(const Vector3& vec);
	Vector3& operator*=(const Vector3& vec);
	Vector3& operator/=(const Vector3& vec);
	Vector3& operator++();
	Vector3& operator--();
	Vector3  operator++(int);
	Vector3  operator--(int);

	friend Vector3 operator+(Vector3 vec1, const Vector3& vec2);
	friend Vector3 operator-(Vector3 vec1, const Vector3& vec2);
	friend Vector3 operator*(Vector3 vec1, const Vector3& vec2);
	friend Vector3 operator/(Vector3 vec1, const Vector3& vec2);

	friend std::ostream& operator<<(std::ostream& stream, const Vector3& Vector3);

	~Vector3();
};

	}
}

#endif