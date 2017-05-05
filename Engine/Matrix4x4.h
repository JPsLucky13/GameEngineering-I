#pragma once


#include <xmmintrin.h>
#include <smmintrin.h>
#include "Vector4.h"
#include "math.h"
#include <assert.h>
#include "FloatCheck.h"
#define _MM_SHUFFLE(fp3,fp2,fp1,fp0)(((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))


namespace Engine
{

	class Matrix4x4
	{

	public:

		Matrix4x4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44):
			m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
			m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
			m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
			m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
		{
			assert(!IsNaN(m_11));
			assert(!IsNaN(m_12));
			assert(!IsNaN(m_13));
			assert(!IsNaN(m_14));

			assert(!IsNaN(m_21));
			assert(!IsNaN(m_22));
			assert(!IsNaN(m_23));
			assert(!IsNaN(m_24));

			assert(!IsNaN(m_31));
			assert(!IsNaN(m_32));
			assert(!IsNaN(m_33));
			assert(!IsNaN(m_34));

			assert(!IsNaN(m_41));
			assert(!IsNaN(m_42));
			assert(!IsNaN(m_43));
			assert(!IsNaN(m_44));
		}


		Matrix4x4() :
			m_11(0.0f), m_12(0.0f), m_13(0.0f), m_14(0.0f),
			m_21(0.0f), m_22(0.0f), m_23(0.0f), m_24(0.0f),
			m_31(0.0f), m_32(0.0f), m_33(0.0f), m_34(0.0f),
			m_41(0.0f), m_42(0.0f), m_43(0.0f), m_44(0.0f)
		{}

		//get
		float _11() const { return m_11; }
		float _12() const { return m_12; }
		float _13() const { return m_13; }
		float _14() const { return m_14; }

		float _21() const { return m_21; }
		float _22() const { return m_22; }
		float _23() const { return m_23; }
		float _24() const { return m_24; }

		float _31() const { return m_31; }
		float _32() const { return m_32; }
		float _33() const { return m_33; }
		float _34() const { return m_34; }

		float _41() const { return m_41; }
		float _42() const { return m_42; }
		float _43() const { return m_43; }
		float _44() const { return m_44; }


		//set
		void _11(const float i_11) { assert(!IsNaN(m_11)); m_11 = i_11; }
		void _12(const float i_12) { assert(!IsNaN(m_12)); m_12 = i_12; }
		void _13(const float i_13){ assert(!IsNaN(m_13)); m_13 = i_13; }
		void _14(const float i_14) { assert(!IsNaN(m_14)); m_14 = i_14; }

		void _21(const float i_21) { assert(!IsNaN(m_21)); m_21 = i_21; }
		void _22(const float i_22) { assert(!IsNaN(m_22)); m_22 = i_22; }
		void _23(const float i_23){ assert(!IsNaN(m_23)); m_23 = i_23; }
		void _24(const float i_24) { assert(!IsNaN(m_24)); m_24 = i_24; }

		void _31(const float i_31) { assert(!IsNaN(m_31)); m_31 = i_31; }
		void _32(const float i_32) { assert(!IsNaN(m_32)); m_32 = i_32; }
		void _33(const float i_33){ assert(!IsNaN(m_33)); m_33 = i_33; }
		void _34(const float i_34) { assert(!IsNaN(m_34)); m_34 = i_34; }

		void _41(const float i_41) { assert(!IsNaN(m_41)); m_41 = i_41; }
		void _42(const float i_42) { assert(!IsNaN(m_42)); m_42 = i_42; }
		void _43(const float i_43){ assert(!IsNaN(m_43)); m_43 = i_43; }
		void _44(const float i_44) { assert(!IsNaN(m_44)); m_44 = i_44; }

		//Copy constructor & assignment operator
		Matrix4x4(const Matrix4x4 & i_other);
		Matrix4x4 & operator=(const Matrix4x4 & i_other);

		//Useful matrix creators
		static Matrix4x4 CreateIdentity(void);
		static Matrix4x4 CreateXRotation(float i_RotationRadians);
		static Matrix4x4 CreateYRotation(float i_RotationRadians);
		static Matrix4x4 CreateZRotation(float i_RotationRadians);

		static Matrix4x4 CreateTranslation(Vector4 & i_trans);
		static Matrix4x4 CreateTranslation(float i_transX, float i_transY, float i_transZ);
		static Matrix4x4 CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ);

		//Invert this instance
		void Invert(void);
		//Return a matrix that is the inverse of this instance but don't modify it
		Matrix4x4 GetInverse(void)const;

		//Transpose this instance
		void Transpose(void);
		//return a matrix that is a transpose of this instance but don't modify this instance.
		Matrix4x4 GetTranspose(void)const;

		//Multiply Matrix * Matrix
		//return *this * i_other
		Matrix4x4 operator*(const Matrix4x4 & i_other) const;

		//Multiply Vector by Matrix
		//return v * M
		Vector4 MultiplyLeft(const Vector4 & i_Vector) const;
		//return M * v
		Vector4 MultiplyRight(const Vector4 & i_Vector) const;

		void * operator new(size_t i_size);
		void operator delete(void * ptr);

	private:
		//Matrix entries
		float m_11, m_12, m_13, m_14,
			m_21, m_22, m_23, m_24,
			m_31, m_32, m_33, m_34,
			m_41, m_42, m_43, m_44;

		//Switch function
		void Switch(float & i_value1, float & i_value2);


	};


}