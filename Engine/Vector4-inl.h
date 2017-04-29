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
#ifdef _WIN64
		return Vector4(_mm_add_ps(input1.vector(),input2.vector()));
#else
		return Vector4(input1.x() + input2.x(), input1.y() + input2.y(), input1.z() + input2.z(), input1.w() + input2.w());
#endif
	}

	inline Vector4 operator-(const Vector4 & input1, const Vector4 & input2)
	{
#ifdef _WIN64
		return Vector4(_mm_sub_ps(input1.vector(), input2.vector()));
#else
		return Vector4(input1.x() - input2.x(), input1.y() - input2.y(), input1.z() - input2.z(), input1.w() - input2.w());
#endif
	}

	inline Vector4 operator*(const Vector4 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

#ifdef _WIN64
		__m128 scalarVec = _mm_set_ps1(i_Scalar);
		return Vector4(_mm_mul_ps(input1.vector(),scalarVec));
#else
		return Vector4(input1.x()* i_Scalar, input1.y() * i_Scalar, input1.z() * i_Scalar, input1.w() * i_Scalar);
#endif
	}

	inline Vector4 operator/(const Vector4 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));
#ifdef _WIN64
		__m128 scalarVec = _mm_set_ps1(i_Scalar);
		return Vector4(_mm_div_ps(input1.vector(),scalarVec));
#else
		return Vector4(input1.x() / i_Scalar, input1.y() / i_Scalar, input1.z() / i_Scalar, input1.w() / i_Scalar);
#endif
	}

	float dot(const Vector4 & input1, const Vector4 & input2)
	{

#ifdef _WIN64
		__m128 vector1 = _mm_set_ps(input1.w(), input1.z(), input1.y(), input1.x());
		__m128 vector2 = _mm_set_ps(input2.w(), input2.z(), input2.y(), input2.x());

		//Get the dot product result
		__m128 vectorRes = _mm_dp_ps(vector1, vector2, 0xF1);

		float dot = _mm_cvtss_f32(vectorRes);

		return dot;
#else
		return input1.x() * input2.x() + input1.y() * input2.y() + input1.z() * input2.z() + input1.w() * input2.w();
#endif
	}

	inline void Vector4::operator=(const Vector4 & input1)
	{

#ifdef _WIN64
		m_vector = { input1.x(),input1.y(),input1.z(),input1.w()};
#else
		m_x = input1.x();
		m_y = input1.y();
		m_z = input1.z();
		m_w = input1.w();
#endif


		
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
