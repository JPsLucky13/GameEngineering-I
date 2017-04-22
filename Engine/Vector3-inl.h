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
#ifdef _WIN64
		return Vector3(_mm_add_ps(input1.vector(), input2.vector()));
#else
		return Vector3(input1.x() + input2.x(), input1.y() + input2.y(), input1.z() + input2.z());
#endif
	}

	inline Vector3 operator-(const Vector3 & input1, const Vector3 & input2)
	{
#ifdef _WIN64
		return Vector3(_mm_sub_ps(input1.vector(), input2.vector()));
#else
		return Vector3(input1.x() - input2.x(), input1.y() - input2.y(), input1.z() - input2.z());
#endif
	}

	inline Vector3 operator*(const Vector3 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

#ifdef _WIN64
		__m128 scalarVec = _mm_set_ps1(i_Scalar);
		return Vector3(_mm_mul_ps(input1.vector(),scalarVec));
#else
		return Vector3(input1.x()* i_Scalar, input1.y() * i_Scalar, input1.z() * i_Scalar);
#endif
	}

	inline Vector3 operator/(const Vector3 & input1, float i_Scalar)
	{

		assert(!IsNaN(i_Scalar));

#ifdef _WIN64
		__m128 scalarVec = _mm_set_ps1(i_Scalar);
		return Vector3(_mm_div_ps(input1.vector(),scalarVec));
#else
		return Vector3(input1.x() / i_Scalar, input1.y() / i_Scalar, input1.z() / i_Scalar);
#endif
	}

	inline Vector3 cross(const Vector3 & input1, const Vector3 & input2)
	{
#ifdef _WIN64
		//vector1 cross vector2
		__m128 v1_op1 = _mm_shuffle_ps(input1.vector(), input1.vector(), _MM_SHUFFLE(3, 0, 2, 1));
		__m128 v2_op1 = _mm_shuffle_ps(input2.vector(), input2.vector(), _MM_SHUFFLE(3, 1, 0, 2));

		__m128 v1_op2 = _mm_shuffle_ps(input1.vector(), input1.vector(), _MM_SHUFFLE(3, 1, 0, 2));
		__m128 v2_op2 = _mm_shuffle_ps(input2.vector(), input2.vector(), _MM_SHUFFLE(3, 0, 2, 1));


		__m128 cross_op1 = _mm_mul_ps(v1_op1, v2_op1);
		__m128 cross_op2 = _mm_mul_ps(v1_op2, v2_op2);

		__m128 crossResult = _mm_sub_ps(cross_op1,cross_op2);

		return Vector3(crossResult);

#else
		float componentX = (input1.y() * input2.z()) - (input1.z() * input2.y());
		float componentY = (input1.z() * input2.x()) - (input1.x() * input2.z());
		float componentZ = (input1.x() * input2.y()) - (input1.y() * input2.x());


		return Vector3(componentX,componentY,componentZ);
#endif

	}

	inline float dot(const Vector3 & input1, const Vector3 & input2)
	{
#ifdef _WIN64
		__m128 vector1 = _mm_set_ps(0,input1.z(), input1.y(), input1.x());
		__m128 vector2 = _mm_set_ps(0, input2.z(), input2.y(), input2.x());

		//Get the dot product result
		__m128 vectorRes = _mm_dp_ps(vector1, vector2, 0x71);

		float dot = _mm_cvtss_f32(vectorRes);

		return dot;
#else

		return input1.x() * input2.x() + input1.y() * input2.y() + input1.z() * input2.z();
#endif
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