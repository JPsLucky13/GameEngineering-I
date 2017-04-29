#include "Vector2D.h"
#pragma

namespace Engine {

	inline bool Vector2D::isZero() const
	{
		if (m_x == 0 && m_y == 0)
			return true;
		else
			return false;
	}

	inline Vector2D operator+(const Vector2D & input1, const Vector2D & input2)
	{

		return Vector2D(_mm_add_ps(input1.vector(),input2.vector()));

	}

	inline Vector2D operator-(const Vector2D & input1, const Vector2D & input2)
	{

		return Vector2D(_mm_sub_ps(input1.vector(), input2.vector()));

	}

	inline Vector2D Vector2D::operator-()const 
	{
		return Vector2D(-m_x, -m_y);
	}

	inline Vector2D operator*(const Vector2D & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

		__m128 scalarVec = _mm_set_ps1(i_Scalar);
		return Vector2D(_mm_mul_ps(input1.vector(), scalarVec));

	}

	inline Vector2D operator/(const Vector2D & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));
		__m128 scalarVec = _mm_set_ps1(i_Scalar);
		return Vector2D(_mm_div_ps(input1.vector(), scalarVec));

	}

	inline float dot(const Vector2D & input1, const Vector2D & input2)
	{

		__m128 vector1 = _mm_set_ps(0, 0, input1.y(), input1.x());
		__m128 vector2 = _mm_set_ps(0, 0, input2.y(), input2.x());

		//Get the dot product result
		__m128 vectorRes = _mm_dp_ps(vector1, vector2, 0x31);

		float dot = _mm_cvtss_f32(vectorRes);

		return dot;

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

	inline bool operator!=(const Vector2D & input1, const Vector2D & input2)
	{
		return (input1.x() != input2.x() || input1.y() != input2.y());
	}

	

}