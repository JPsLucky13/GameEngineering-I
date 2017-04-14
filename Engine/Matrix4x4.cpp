#include "Matrix4x4.h"

namespace Engine {

	//copy constructor
	Matrix4x4::Matrix4x4(const Matrix4x4 & i_other):
		m_11(i_other._11()), m_12(i_other._12()), m_13(i_other._13()), m_14(i_other._14()),
		m_21(i_other._21()), m_22(i_other._22()), m_23(i_other._23()), m_24(i_other._24()),
		m_31(i_other._31()), m_32(i_other._32()), m_33(i_other._33()), m_34(i_other._34()),
		m_41(i_other._41()), m_42(i_other._42()), m_43(i_other._43()), m_44(i_other._44())
	{
	}

	//reference assignment operator 
	Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & i_other)
	{
		m_11 = i_other._11();
		m_12 = i_other._12();
		m_13 = i_other._13();
		m_14 = i_other._14();

		m_21 = i_other._21();
		m_22 = i_other._22();
		m_23 = i_other._23();
		m_24 = i_other._24();

		m_31 = i_other._31();
		m_32 = i_other._32();
		m_33 = i_other._33();
		m_34 = i_other._34();

		m_41 = i_other._41();
		m_42 = i_other._42();
		m_43 = i_other._43();
		m_44 = i_other._44();

		return *this;
	}

	Matrix4x4 Matrix4x4::CreateIdentity(void)
	{
		Matrix4x4 identity(1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f);
		return identity;
	}

	Matrix4x4 Matrix4x4::CreateXRotation(float i_RotationRadians)
	{
		Matrix4x4 xRot(1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, cosf(i_RotationRadians), -sinf(i_RotationRadians), 0.0f,
						0.0f, sinf(i_RotationRadians), cosf(i_RotationRadians), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);

		return xRot;
	}

	Matrix4x4 Matrix4x4::CreateYRotation(float i_RotationRadians)
	{
		Matrix4x4 yRot(cosf(i_RotationRadians), 0.0f, sinf(i_RotationRadians), 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-sinf(i_RotationRadians), 0.0f, cosf(i_RotationRadians), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);


		return yRot;
	}

	Matrix4x4 Matrix4x4::CreateZRotation(float i_RotationRadians)
	{
		Matrix4x4 zRot(cosf(i_RotationRadians), -sinf(i_RotationRadians), 0.0f, 0.0f,
						sinf(i_RotationRadians), cosf(i_RotationRadians), 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);


		return zRot;
	}

	Matrix4x4 Matrix4x4::CreateTranslation(Vector4 i_trans)
	{
		Matrix4x4 trans(1.0f, 0.0f, 0.0f, i_trans.x(),
						0.0f, 1.0f, 0.0f, i_trans.y(),
						0.0f, 0.0f, 1.0f, i_trans.z(),
						0.0f, 0.0f, 0.0f, 1.0f);
		return trans;
	}

	Matrix4x4 Matrix4x4::CreateTranslation(float i_transX, float i_transY, float i_transZ)
	{
		Matrix4x4 trans(1.0f, 0.0f, 0.0f, i_transX,
						0.0f, 1.0f, 0.0f, i_transY,
						0.0f, 0.0f, 1.0f, i_transZ,
						0.0f, 0.0f, 0.0f, 1.0f);
		return trans;
	}

	Matrix4x4 Matrix4x4::CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ)
	{
		Matrix4x4 scale(i_scaleX, 0.0f, 0.0f, 0.0f,
						 0.0f, i_scaleY, 0.0f, 0.0f,
						 0.0f, 0.0f, i_scaleZ, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f);
		return scale;
	}

	void Matrix4x4::Invert(void)
	{
		assert(!IsNaN(m_11));

		float det = m_11*m_22*m_33*m_44 + m_11*m_23*m_34*m_42 + m_11*m_24*m_32*m_43
				+ m_12*m_21*m_34*m_43 + m_12*m_23*m_31*m_44 + m_12*m_24*m_33*m_41
				+ m_13*m_21*m_32*m_44 + m_13*m_22*m_34*m_41 + m_13*m_24*m_31*m_42
				+ m_14*m_21*m_33*m_42 + m_14*m_22*m_31*m_43 + m_14*m_23*m_32*m_41
				- m_11*m_22*m_34*m_43 - m_11*m_23*m_32*m_44 - m_11*m_24*m_33*m_42
				- m_12*m_21*m_33*m_44 - m_12*m_23*m_34*m_41 - m_12*m_24*m_31*m_43
				- m_13*m_21*m_34*m_42 - m_13*m_22*m_31*m_44 - m_13*m_24*m_32*m_41
				- m_14*m_21*m_32*m_43 - m_14*m_22*m_33*m_41 - m_14*m_23*m_31*m_42;

		//The determinant exists
		if (det != 0.0f)
		{
			Matrix4x4 adj(m_22*m_33*m_44 + m_23*m_34*m_42 + m_24*m_32*m_43 - m_22*m_34*m_43 - m_23*m_32*m_44 - m_24*m_33*m_42,
						  m_12*m_34*m_43 + m_13*m_32*m_44 + m_14*m_33*m_42 - m_12*m_33*m_44 - m_13*m_34*m_42 - m_14*m_32*m_43,
						  m_12*m_23*m_44 + m_13*m_24*m_42 + m_14*m_22*m_43 - m_12*m_24*m_43 - m_13*m_22*m_44 - m_14*m_23*m_42,
						  m_12*m_24*m_33 + m_13*m_22*m_34 + m_14*m_23*m_32 - m_12*m_23*m_34 - m_13*m_24*m_32 - m_14*m_22*m_33,
						  m_21*m_34*m_43 + m_23*m_31*m_44 + m_24*m_33*m_41 - m_21*m_33*m_44 - m_23*m_34*m_41 - m_24*m_31*m_43,
						  m_11*m_33*m_44 + m_13*m_34*m_41 + m_14*m_31*m_43 - m_11*m_34*m_43 - m_13*m_31*m_44 - m_14*m_33*m_41,
						  m_11*m_24*m_43 + m_13*m_21*m_44 + m_14*m_23*m_41 - m_11*m_23*m_44 - m_13*m_24*m_41 - m_14*m_21*m_43,
						  m_11*m_23*m_34 + m_13*m_24*m_31 + m_14*m_21*m_33 - m_11*m_24*m_33 - m_13*m_21*m_34 - m_14*m_23*m_31,
						  m_21*m_32*m_44 + m_22*m_34*m_41 + m_24*m_31*m_42 - m_21*m_34*m_42 - m_22*m_31*m_44 - m_24*m_32*m_41,
						  m_11*m_34*m_42 + m_12*m_31*m_44 + m_14*m_32*m_41 - m_11*m_32*m_44 - m_12*m_34*m_41 - m_14*m_31*m_42,
						  m_11*m_22*m_44 + m_12*m_24*m_41 + m_14*m_21*m_42 - m_11*m_24*m_42 - m_12*m_21*m_44 - m_14*m_22*m_41,
						  m_11*m_24*m_32 + m_12*m_21*m_34 + m_14*m_22*m_31 - m_11*m_22*m_34 - m_12*m_24*m_31 - m_14*m_21*m_32,
						  m_21*m_33*m_42 + m_22*m_31*m_43 + m_23*m_32*m_41 - m_21*m_32*m_43 - m_22*m_33*m_41 - m_23*m_31*m_42,
						  m_11*m_32*m_43 + m_12*m_33*m_41 + m_13*m_31*m_42 - m_11*m_33*m_42 - m_12*m_31*m_43 - m_13*m_32*m_41,
						  m_11*m_23*m_42 + m_12*m_21*m_43 + m_13*m_22*m_41 - m_11*m_22*m_43 - m_12*m_23*m_41 - m_13*m_21*m_42,
						  m_11*m_22*m_33 + m_12*m_23*m_31 + m_13*m_21*m_32 - m_11*m_23*m_32 - m_12*m_21*m_33 - m_13*m_22*m_31
						);

			//Set the values of the inverse
			m_11 = adj._11() / det;
			m_12 = adj._12() / det;
			m_13 = adj._13() / det;
			m_14 = adj._14() / det;

			m_21 = adj._21() / det;
			m_22 = adj._22() / det;
			m_23 = adj._23() / det;
			m_24 = adj._24() / det;

			m_31 = adj._31() / det;
			m_32 = adj._32() / det;
			m_33 = adj._33() / det;
			m_34 = adj._34() / det;

			m_41 = adj._41() / det;
			m_42 = adj._42() / det;
			m_43 = adj._43() / det;
			m_44 = adj._44() / det;
		}

	}

	Matrix4x4 Matrix4x4::GetInverse(void) const
	{
		assert(!IsNaN(m_11));

		float det = m_11*m_22*m_33*m_44 + m_11*m_23*m_34*m_42 + m_11*m_24*m_32*m_43
			+ m_12*m_21*m_34*m_43 + m_12*m_23*m_31*m_44 + m_12*m_24*m_33*m_41
			+ m_13*m_21*m_32*m_44 + m_13*m_22*m_34*m_41 + m_13*m_24*m_31*m_42
			+ m_14*m_21*m_33*m_42 + m_14*m_22*m_31*m_43 + m_14*m_23*m_32*m_41
			- m_11*m_22*m_34*m_43 - m_11*m_23*m_32*m_44 - m_11*m_24*m_33*m_42
			- m_12*m_21*m_33*m_44 - m_12*m_23*m_34*m_41 - m_12*m_24*m_31*m_43
			- m_13*m_21*m_34*m_42 - m_13*m_22*m_31*m_44 - m_13*m_24*m_32*m_41
			- m_14*m_21*m_32*m_43 - m_14*m_22*m_33*m_41 - m_14*m_23*m_31*m_42;

		Matrix4x4 adj(m_22*m_33*m_44 + m_23*m_34*m_42 + m_24*m_32*m_43 - m_22*m_34*m_43 - m_23*m_32*m_44 - m_24*m_33*m_42,
			m_12*m_34*m_43 + m_13*m_32*m_44 + m_14*m_33*m_42 - m_12*m_33*m_44 - m_13*m_34*m_42 - m_14*m_32*m_43,
			m_12*m_23*m_44 + m_13*m_24*m_42 + m_14*m_22*m_43 - m_12*m_24*m_43 - m_13*m_22*m_44 - m_14*m_23*m_42,
			m_12*m_24*m_33 + m_13*m_22*m_34 + m_14*m_23*m_32 - m_12*m_23*m_34 - m_13*m_24*m_32 - m_14*m_22*m_33,
			m_21*m_34*m_43 + m_23*m_31*m_44 + m_24*m_33*m_41 - m_21*m_33*m_44 - m_23*m_34*m_41 - m_24*m_31*m_43,
			m_11*m_33*m_44 + m_13*m_34*m_41 + m_14*m_31*m_43 - m_11*m_34*m_43 - m_13*m_31*m_44 - m_14*m_33*m_41,
			m_11*m_24*m_43 + m_13*m_21*m_44 + m_14*m_23*m_41 - m_11*m_23*m_44 - m_13*m_24*m_41 - m_14*m_21*m_43,
			m_11*m_23*m_34 + m_13*m_24*m_31 + m_14*m_21*m_33 - m_11*m_24*m_33 - m_13*m_21*m_34 - m_14*m_23*m_31,
			m_21*m_32*m_44 + m_22*m_34*m_41 + m_24*m_31*m_42 - m_21*m_34*m_42 - m_22*m_31*m_44 - m_24*m_32*m_41,
			m_11*m_34*m_42 + m_12*m_31*m_44 + m_14*m_32*m_41 - m_11*m_32*m_44 - m_12*m_34*m_41 - m_14*m_31*m_42,
			m_11*m_22*m_44 + m_12*m_24*m_41 + m_14*m_21*m_42 - m_11*m_24*m_42 - m_12*m_21*m_44 - m_14*m_22*m_41,
			m_11*m_24*m_32 + m_12*m_21*m_34 + m_14*m_22*m_31 - m_11*m_22*m_34 - m_12*m_24*m_31 - m_14*m_21*m_32,
			m_21*m_33*m_42 + m_22*m_31*m_43 + m_23*m_32*m_41 - m_21*m_32*m_43 - m_22*m_33*m_41 - m_23*m_31*m_42,
			m_11*m_32*m_43 + m_12*m_33*m_41 + m_13*m_31*m_42 - m_11*m_33*m_42 - m_12*m_31*m_43 - m_13*m_32*m_41,
			m_11*m_23*m_42 + m_12*m_21*m_43 + m_13*m_22*m_41 - m_11*m_22*m_43 - m_12*m_23*m_41 - m_13*m_21*m_42,
			m_11*m_22*m_33 + m_12*m_23*m_31 + m_13*m_21*m_32 - m_11*m_23*m_32 - m_12*m_21*m_33 - m_13*m_22*m_31
		);

		Matrix4x4 inverse(adj._11() / det, adj._12() / det, adj._13() / det, adj._14() / det,
						  adj._21() / det, adj._22() / det, adj._23() / det, adj._24() / det,
						  adj._31() / det, adj._32() / det, adj._33() / det, adj._34() / det,
						  adj._41() / det, adj._42() / det, adj._43() / det, adj._44() / det

		);


		return inverse;
	}

	void Matrix4x4::Transpose(void)
	{
		assert(!IsNaN(m_11));

		Switch(m_12, m_21);
		Switch(m_13, m_31);
		Switch(m_14, m_41);
		Switch(m_23, m_32);
		Switch(m_24, m_42);
		Switch(m_34, m_43);

	}

	Matrix4x4 Matrix4x4::GetTranspose(void) const
	{
		assert(!IsNaN(m_11));

		Matrix4x4 transpose(m_11, m_21, m_31, m_41,
							m_12, m_22, m_32, m_42,
							m_13, m_23, m_33, m_43,
							m_14, m_24, m_34, m_44
							);

		return transpose;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & i_other) const
	{
		Matrix4x4 result(m_11 * i_other._11() + m_12 * i_other._21() + m_13 * i_other._31() + m_14 * i_other._41(), m_11 * i_other._12() + m_12 * i_other._22() + m_13 * i_other._32() + m_14 * i_other._42(), m_11 * i_other._13() + m_12 * i_other._23() + m_13 * i_other._33() + m_14 * i_other._43(), m_11 * i_other._14() + m_12 * i_other._24() + m_13 * i_other._34() + m_14 * i_other._44(),
						 m_21 * i_other._11() + m_22 * i_other._21() + m_23 * i_other._31() + m_24 * i_other._41(), m_21 * i_other._12() + m_22 * i_other._22() + m_23 * i_other._32() + m_24 * i_other._42(), m_21 * i_other._13() + m_22 * i_other._23() + m_23 * i_other._33() + m_24 * i_other._43(), m_21 * i_other._14() + m_22 * i_other._24() + m_23 * i_other._34() + m_24 * i_other._44(),
						 m_31 * i_other._11() + m_32 * i_other._21() + m_33 * i_other._31() + m_34 * i_other._41(), m_31 * i_other._12() + m_32 * i_other._22() + m_33 * i_other._32() + m_34 * i_other._42(), m_31 * i_other._13() + m_32 * i_other._23() + m_33 * i_other._33() + m_34 * i_other._43(), m_31 * i_other._14() + m_32 * i_other._24() + m_33 * i_other._34() + m_34 * i_other._44(),
						 m_41 * i_other._11() + m_42 * i_other._21() + m_43 * i_other._31() + m_44 * i_other._41(), m_41 * i_other._12() + m_42 * i_other._22() + m_43 * i_other._32() + m_44 * i_other._42(), m_41 * i_other._13() + m_42 * i_other._23() + m_43 * i_other._33() + m_44 * i_other._43(), m_41 * i_other._14() + m_42 * i_other._24() + m_43 * i_other._34() + m_44 * i_other._44()
						);
		return result;
	}

	//return v * M
	Vector4 Matrix4x4::MultiplyLeft(const Vector4 & i_Vector) const
	{
		//Old operation

		/*Vector4 res(i_Vector.x() * m_11 + i_Vector.y() * m_21 + i_Vector.z() * m_31 + i_Vector.w() * m_41,
					i_Vector.x() * m_12 + i_Vector.y() * m_22 + i_Vector.z() * m_32 + i_Vector.w() * m_42,
					i_Vector.x() * m_13 + i_Vector.y() * m_23 + i_Vector.z() * m_33 + i_Vector.w() * m_43,
					i_Vector.x() * m_14 + i_Vector.y() * m_24 + i_Vector.z() * m_34 + i_Vector.w() * m_44
					);*/
		

		//Columns of matrix 4x4
		__m128 col1 = _mm_set_ps(m_14, m_13, m_12, m_11);
		__m128 col2 = _mm_set_ps(m_24, m_23, m_22, m_21);
		__m128 col3 = _mm_set_ps(m_34, m_33, m_32, m_31);
		__m128 col4 = _mm_set_ps(m_44, m_43, m_42, m_41);

		//The vector
		__m128 vectorXComp = _mm_set_ps1(i_Vector.x());
		__m128 vectorYComp = _mm_set_ps1(i_Vector.y());
		__m128 vectorZComp = _mm_set_ps1(i_Vector.z());
		__m128 vectorWComp = _mm_set_ps1(i_Vector.w());

		//The multiplications
		__m128 mulOp1 = _mm_mul_ps(col1,vectorXComp);
		__m128 mulOp2 = _mm_mul_ps(col2, vectorYComp);
		__m128 mulOp3 = _mm_mul_ps(col3, vectorZComp);
		__m128 mulOp4 = _mm_mul_ps(col4, vectorWComp);

		//The sums
		__m128 sumOp1 = _mm_add_ps(mulOp1, mulOp2);
		__m128 sumOp2 = _mm_add_ps(mulOp3, mulOp4);
		__m128 sumOp3 = _mm_add_ps(sumOp1, sumOp2);


		return Vector4(sumOp3);
	}

	//return M * v
	Vector4 Matrix4x4::MultiplyRight(const Vector4 & i_Vector) const
	{
		//Old operation
		/*
		Vector4 res(m_11 * i_Vector.x() + m_12 * i_Vector.y() + m_13 * i_Vector.z() + m_14 * i_Vector.w(),
					m_21 * i_Vector.x() + m_22 * i_Vector.y() + m_23 * i_Vector.z() + m_24 * i_Vector.w(),
					m_31 * i_Vector.x() + m_32 * i_Vector.y() + m_33 * i_Vector.z() + m_34 * i_Vector.w(),
					m_41 * i_Vector.x() + m_42 * i_Vector.y() + m_43 * i_Vector.z() + m_44 * i_Vector.w()
					);
					*/

		//Columns of matrix 4x4
		__m128 col1 = _mm_set_ps(m_41, m_31, m_21, m_11);
		__m128 col2 = _mm_set_ps(m_42, m_32, m_22, m_12);
		__m128 col3 = _mm_set_ps(m_43, m_33, m_23, m_13);
		__m128 col4 = _mm_set_ps(m_44, m_34, m_24, m_14);

		//The vector
		__m128 vectorXComp = _mm_set_ps1(i_Vector.x());
		__m128 vectorYComp = _mm_set_ps1(i_Vector.y());
		__m128 vectorZComp = _mm_set_ps1(i_Vector.z());
		__m128 vectorWComp = _mm_set_ps1(i_Vector.w());

		//The multiplications
		__m128 mulOp1 = _mm_mul_ps(col1, vectorXComp);
		__m128 mulOp2 = _mm_mul_ps(col2, vectorYComp);
		__m128 mulOp3 = _mm_mul_ps(col3, vectorZComp);
		__m128 mulOp4 = _mm_mul_ps(col4, vectorWComp);

		//The sums
		__m128 sumOp1 = _mm_add_ps(mulOp1, mulOp2);
		__m128 sumOp2 = _mm_add_ps(mulOp3, mulOp4);
		__m128 sumOp3 = _mm_add_ps(sumOp1, sumOp2);


		return Vector4(sumOp3);
	}

	void Matrix4x4::Switch(float & i_value1, float & i_value2)
	{
		float temp = i_value1;
		i_value1 = i_value2;
		i_value2 = temp;


	}

}
