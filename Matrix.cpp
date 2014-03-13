#pragma once
#include "MMath.h"

Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
	{
		Mtrx[0][0] = m11; Mtrx[0][1] = m12; Mtrx[0][2] = m13; Mtrx[0][3] = m14;
		Mtrx[1][0] = m21; Mtrx[1][1] = m22; Mtrx[1][2] = m23; Mtrx[1][3] = m24;
		Mtrx[2][0] = m31; Mtrx[2][1] = m32; Mtrx[2][2] = m33; Mtrx[2][3] = m34;
		Mtrx[3][0] = m41; Mtrx[3][1] = m42; Mtrx[3][2] = m43; Mtrx[3][3] = m44;
	}

Matrix::Matrix()
	{
		*this = Identity() ;
	}

Matrix Matrix::Identity()
	{
		return Matrix
			(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

void Matrix::Show()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
				std::cout << Mtrx[i][j] << " ";
			std::cout << std::endl;
		}
	}

Matrix Matrix::operator*(Matrix mtrx1)
	{
		Matrix res;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				float cell = 0;
				for (int k = 0; k < 4; ++k)//i1 , j1
				{
					cell += mtrx1(i, k) * Mtrx[k][j];
				}
				res(i, j) = cell;
			}
			return res;
	}

	Matrix Matrix::operator*(float num)
	{
		Matrix res;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				res(i, j) = num * Mtrx[i][j];

		return res;
	}

	float Matrix::operator() (int i, int j) const
	{
		return Mtrx[i][j];
	}
	float& Matrix::operator() (int i, int j)
	{
		return Mtrx[i][j];
	}

	Matrix Matrix::Translation(const Vector3 translation)
	{
		Matrix r = Matrix(
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			translation.X , translation.Y , translation.Z , 1);

		return r;
	}

	Matrix Matrix::Rotation( Vector3 eulerAngles)
	{  
		const float x = ToRad(eulerAngles.X);
		const float y = ToRad(eulerAngles.Y);
		const float z = ToRad(eulerAngles.Z);

		Matrix rx = Matrix(
			1,0,0,0,
			0,cosf(x),sinf(x),0,
			0,-sinf(x),cosf(x),0,
			0,0,0,1);

		Matrix ry = Matrix(
			cosf(y),0,-sinf(y),0,
			0,1,0,0,
			sinf(y),0,cosf(y),0,
			0,0,0,1);
		Matrix rz = Matrix(
			cosf(z),sinf(z),0,0,
			-sinf(z),cosf(z),0,0,
			0,0,1,0,
			0,0,0,1);

		return rx * ry * rz;
	}

	Matrix Matrix::Scale( Vector3 scale)
	{
		Matrix r = Matrix(
			scale.X,0,0,0,
			0,scale.Y,0,0,
			0,0,scale.Z,0,
			0,0,0,1);

		return r;
	}

	void Matrix::ApplyOn(Vector3& vec)
	{
		Vector4 res ;
		for (int i = 0; i < 4; ++i)
		{
			float cell = 0;
			for (int j = 0; j < 4; ++j)
			{
				cell += (*this)(i, j) *vec[j];
			}
			res[i] = cell;
		}
		vec = Vector3(res.X , res.Y , res.Z) ;
	}

	 void Matrix::ApplyOn(Matrix mat , Vector3& vec)
	{
		Vector4 res ;
		for (int i = 0; i < 4; ++i)
		{
			float cell = 0;
			for (int j = 0; j < 4; ++j)
			{
				cell += mat(i, j) *vec[j];
			}
			res[i] = cell;
		}
		vec = Vector3(res.X , res.Y , res.Z) ;
	}
	 Matrix Matrix::LookAt(Vector3 position, Vector3 target)
	{
		return LookAtDirection(position , target - position) ;
	}
	 Matrix Matrix::LookAtDirection(Vector3 position, Vector3 eyeDirection)
{
	return Matrix::Rotation(eyeDirection) * Matrix::Translation(position);
}
