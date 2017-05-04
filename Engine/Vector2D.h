#pragma once

#include <smmintrin.h>
#include "Math.h"
#include <assert.h>
#include "FloatCheck.h"
#define _MM_SHUFFLE(fp3,fp2,fp1,fp0)(((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))
namespace Engine {

	union Vector2D {

	public:

		Vector2D(float x, float y) :
			m_x(x), m_y(y)
		{
			assert(!IsNaN(m_x));
			assert(!IsNaN(m_y));
		}

		Vector2D(const __m128 & i_vector) :
			m_vector(i_vector)
		{

		}

		Vector2D() :
			m_x(0.0f),
			m_y(0.0f)
		{}

		//get
		float x() const { return m_x; }
		float y() const { return m_y; }
		float lenght() const { return sqrt(m_x*m_x + m_y*m_y); }

		const __m128 & vector() const { return m_vector; }


		//set
		void x(const float x) { assert(!IsNaN(x)); m_x = x; }
		void y(const float y) { assert(!IsNaN(y)); m_y = y; }

		void vector(const __m128 & i_vector) { m_vector = i_vector; }

		inline void operator=(const Vector2D & input1);
		inline void operator+=(const Vector2D & input1);
		inline Vector2D operator-()const;
		
		inline bool isZero() const;
		//Returns the normalized vector
		Vector2D normalize();

	private:

		__m128 m_vector;
		struct
		{
			float m_x, m_y;
		};
	};

	inline Vector2D operator+(const Vector2D & input1, const Vector2D & input2);
	inline Vector2D operator-(const Vector2D & input1, const Vector2D & input2);
	inline Vector2D operator*(const Vector2D & input1, float i_Scalar);
	inline Vector2D operator/(const Vector2D & input1, float i_Scalar);
	inline float dot(const Vector2D & input1, const Vector2D & input2);
	inline bool operator==(const Vector2D & input1, const Vector2D & input2);
	inline bool operator!=(const Vector2D & input1, const Vector2D & input2);
	



}
#include "Vector2D-inl.h"