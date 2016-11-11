#include "Vector2D.h"
#pragma

namespace Engine {

	inline Vector2D operator+(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() + input2.x(), input1.y() + input2.y());
	}

	inline Vector2D operator-(const Vector2D & input1, const Vector2D & input2)
	{
		return Vector2D(input1.x() - input2.x(), input1.y() - input2.y());
	}

	inline Vector2D operator*(const Vector2D & input1, float i_Scalar)
	{
		return Vector2D(input1.x()* i_Scalar, input1.y() * i_Scalar);
	}

	inline void Vector2D::operator=(const Vector2D & input1)
	{
		m_x = input1.x();
		m_y = input1.y();
	}



	inline bool operator==(const Vector2D & input1, const Vector2D & input2)
	{
		return (input1.x() == input2.x() && input1.y() == input2.y());
	}

}