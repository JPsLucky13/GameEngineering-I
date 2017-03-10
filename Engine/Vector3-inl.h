#include "Vector3.h"
#pragma

namespace Engine {

	inline bool  Vector3::isZero()
	{
		if (m_x == 0 && m_y == 0 && m_z == 0)
			return true;
		else
			return false;
	}

	inline Vector3 operator+(const Vector3 & input1, const Vector3 & input2)
	{
		return Vector3(input1.x() + input2.x(), input1.y() + input2.y(), input1.z() + input2.z());
	}

	inline Vector3 operator-(const Vector3 & input1, const Vector3 & input2)
	{
		return Vector3(input1.x() - input2.x(), input1.y() - input2.y(), input1.z() - input2.z());
	}

	inline Vector3 operator*(const Vector3 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

		return Vector3(input1.x()* i_Scalar, input1.y() * i_Scalar, input1.z() * i_Scalar);
	}

	inline Vector3 operator/(const Vector3 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

		return Vector3(input1.x() / i_Scalar, input1.y() / i_Scalar, input1.z() / i_Scalar);
	}

	inline void Vector3::operator=(const Vector3 & input1)
	{
		m_x = input1.x();
		m_y = input1.y();
		m_z = input1.z();
	}



	inline bool operator==(const Vector3 & input1, const Vector3 & input2)
	{
		return (input1.x() == input2.x() && input1.y() == input2.y() && input1.z() == input2.z());
	}

	inline bool operator!=(const Vector3 & input1, const Vector3 & input2)
	{
		return (input1.x() != input2.x() || input1.y() != input2.y() || input1.z() != input2.z());
	}



}