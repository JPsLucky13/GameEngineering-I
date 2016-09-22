#pragma once
namespace Engine {

	class Vector2D {

	public:
		Vector2D(float x, float y) :
			m_x(x),
			m_y(y)
		{}

		Vector2D() :
			m_x(0),
			m_y(0)
		{}


		//get
		float x() const { return m_x; }
		float y() const { return m_y; }

		//set
		void x(float x) { m_x = x; }
		void y(float y) { m_y = y; }

	private:
		float m_x, m_y;

	};

	Vector2D operator+(const Vector2D & input1, const Vector2D & input2);
	Vector2D operator-(const Vector2D & input1, const Vector2D & input2);
	Vector2D operator*(const Vector2D & input1, const Vector2D & input2);
	bool operator==(const Vector2D & input1, const Vector2D & input2);



}