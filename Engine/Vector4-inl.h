#pragma once
#include "Vector4.h"

namespace Engine {

	inline bool  Vector4::isZero()
	{
		if (m_x == 0 && m_y == 0 && m_z == 0 && m_w == 0)
			return true;
		else
			return false;
	}

	inline Vector4 operator+(const Vector4 & input1, const Vector4 & input2)
	{
		return Vector4(input1.x() + input2.x(), input1.y() + input2.y(), input1.z() + input2.z(), input1.w() + input2.w());
	}

	inline Vector4 operator-(const Vector4 & input1, const Vector4 & input2)
	{
		return Vector4(input1.x() - input2.x(), input1.y() - input2.y(), input1.z() - input2.z(), input1.w() - input2.w());
	}

	inline Vector4 operator*(const Vector4 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

		return Vector4(input1.x()* i_Scalar, input1.y() * i_Scalar, input1.z() * i_Scalar, input1.w() * i_Scalar);
	}

	inline Vector4 operator/(const Vector4 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

		return Vector4(input1.x() / i_Scalar, input1.y() / i_Scalar, input1.z() / i_Scalar, input1.w() / i_Scalar);
	}

	inline void Vector4::operator=(const Vector4 & input1)
	{
		m_x = input1.x();
		m_y = input1.y();
		m_z = input1.z();
		m_w = input1.w();
	}



	inline bool operator==(const Vector4 & input1, const Vector4 & input2)
	{
		return (input1.x() == input2.x() && input1.y() == input2.y() && input1.z() == input2.z() && input1.w() == input2.w());
	}

	inline bool operator!=(const Vector4 & input1, const Vector4 & input2)
	{
		return (input1.x() != input2.x() || input1.y() != input2.y() || input1.z() != input2.z() || input1.w() != input2.w());
	}



}
