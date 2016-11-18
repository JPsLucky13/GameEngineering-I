#pragma once

#include "Math.h"

namespace Engine {

	class Vector2D {

	public:
		Vector2D(float x, float y) :
			m_x(x),
			m_y(y)
		{}

		Vector2D() :
			m_x(0.0f),
			m_y(0.0f)
		{}


		//get
		float x() const { return m_x; }
		float y() const { return m_y; }

		//set
		void x(const float x) { m_x = x; }
		void y(const float y) { m_y = y; }


		inline void operator=(const Vector2D & input1);
		//Returns the normalized vector
		Vector2D normalize();

	private:
		float m_x, m_y;

	};

	inline Vector2D operator+(const Vector2D & input1, const Vector2D & input2);
	inline Vector2D operator-(const Vector2D & input1, const Vector2D & input2);
	inline Vector2D operator*(const Vector2D & input1, float i_Scalar);
	inline bool operator==(const Vector2D & input1, const Vector2D & input2);
	inline bool operator!=(const Vector2D & input1, const Vector2D & input2);
	
	void PrintDebugMessage(const char* file, const char* function, const int line,const char* fmt, ...);


}
#include "Vector2D-inl.h"