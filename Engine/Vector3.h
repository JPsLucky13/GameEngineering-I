#pragma once

#include "Math.h"
#include <assert.h>
#include "FloatCheck.h"

namespace Engine {

	class Vector3 {

	public:
		Vector3(float x, float y, float z) :
			m_x(x),
			m_y(y),
			m_z(z)
		{
			assert(!IsNaN(m_x));
			assert(!IsNaN(m_y));
			assert(!IsNaN(m_z));
		}

		Vector3() :
			m_x(0.0f),
			m_y(0.0f),
			m_z(0.0f)
		{}


		//get
		float x() const { return m_x; }
		float y() const { return m_y; }
		float z() const { return m_z; }

		//set
		void x(const float x) { assert(!IsNaN(x)); m_x = x; }
		void y(const float y) { assert(!IsNaN(y)); m_y = y; }
		void z(const float z) { assert(!IsNaN(z)); m_z = z; }


		inline void operator=(const Vector3 & input1);
		inline bool isZero();
		//Returns the normalized vector
		Vector3 normalize();

	private:
		float m_x, m_y, m_z;
	};

	inline Vector3 operator+(const Vector3 & input1, const Vector3 & input2);
	inline Vector3 operator-(const Vector3 & input1, const Vector3 & input2);
	inline Vector3 operator*(const Vector3 & input1, float i_Scalar);
	inline Vector3 operator/(const Vector3 & input1, float i_Scalar);
	inline bool operator==(const Vector3 & input1, const Vector3 & input2);
	inline bool operator!=(const Vector3 & input1, const Vector3 & input2);




}
#include "Vector3-inl.h"