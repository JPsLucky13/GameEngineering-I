#pragma once


#include <xmmintrin.h>
#include <smmintrin.h>
#include "Math.h"
#include <assert.h>
#include "FloatCheck.h"
#define _MM_SHUFFLE(fp3,fp2,fp1,fp0)(((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))


namespace Engine {

	class Vector4 {

	public:


#ifdef _WIN64
		Vector4(float x, float y, float z , float w) :
			m_vector(_mm_set_ps(w, z, y, x))
		{
			assert(!IsNaN(m_x));
			assert(!IsNaN(m_y));
			assert(!IsNaN(m_z));
			assert(!IsNaN(m_w));
		}

		Vector4(const __m128 i_vector) :
			m_vector(i_vector)
		{

		}
#else
		Vector4(float x, float y, float z, float w) :
			m_x(x),
			m_y(y),
			m_z(z),
			m_w(w)
		{
			assert(!IsNaN(m_x));
			assert(!IsNaN(m_y));
			assert(!IsNaN(m_z));
			assert(!IsNaN(m_w));
		}


#endif
		Vector4() :
			m_x(0.0f),
			m_y(0.0f),
			m_z(0.0f),
			m_w(0.0f)
		{}


		//get
		float x() const { return m_x; }
		float y() const { return m_y; }
		float z() const { return m_z; }
		float w() const { return m_w; }

#ifdef _WIN64
		__m128 vector() const { return m_vector; }
#endif // _WIN64
		//set
		void x(const float x) { assert(!IsNaN(x)); m_x = x; }
		void y(const float y) { assert(!IsNaN(y)); m_y = y; }
		void z(const float z) { assert(!IsNaN(z)); m_z = z; }
		void w(const float w) { assert(!IsNaN(w)); m_w = w; }

#ifdef _WIN64
		void vector(const __m128 i_vector) { m_vector = i_vector; }
#endif // _WIN64

		inline void operator=(const Vector4 & input1);
		inline bool isZero();
		//Returns the normalized vector
		Vector4 normalize();

	private:

#ifdef _WIN64
		union{
			struct
			{
				float m_x, m_y, m_z, m_w;
			};
			__m128 m_vector;
		};

#else
		float m_x, m_y, m_z, m_w;
#endif
	};

	inline Vector4 operator+(const Vector4 & input1, const Vector4 & input2);
	inline Vector4 operator-(const Vector4 & input1, const Vector4 & input2);
	inline Vector4 operator*(const Vector4 & input1, float i_Scalar);
	inline Vector4 operator/(const Vector4 & input1, float i_Scalar);
	inline float dot(const Vector4 & input1, const Vector4 & input2);
	inline bool operator==(const Vector4 & input1, const Vector4 & input2);
	inline bool operator!=(const Vector4 & input1, const Vector4 & input2);




}
#include "Vector4-inl.h"