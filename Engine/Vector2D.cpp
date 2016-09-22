
#include "Vector2D.h"

namespace Engine {

	Vector2D operator+(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() + input2.x(), input1.y() + input2.y());
	}

	Vector2D operator-(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() - input2.x(), input1.y() - input2.y());
	}

	Vector2D operator*(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() * input2.x(), input1.y() * input2.y());
	}

	bool operator==(const Vector2D & input1, const Vector2D & input2)
	{
		return (input1.x() == input2.x() && input1.y() == input2.y());
	}
}