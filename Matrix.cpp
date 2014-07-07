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
			std::cout << (float)Mtrx[i][j] << " ";
		std::cout << std::endl;
	}
}

Matrix Matrix::operator*(Matrix mtrx1)
{
	Matrix res;
	float cell = 0;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			cell = 0;
			for (int k = 0; k < 4; ++k)//i1 , j1
			{
				cell += Mtrx[i][k] * mtrx1(k, j) ;
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
		0,cosf(x),-sinf(x),0,
		0,sinf(x),cosf(x),0,
		0,0,0,1);

	Matrix ry = Matrix(
		cosf(y),0,sinf(y),0,
		0,1,0,0,
		-sinf(y),0,cosf(y),0,
		0,0,0,1);
	Matrix rz = Matrix(
		cosf(z),-sinf(z),0,0,
		sinf(z),cosf(z),0,0,
		0,0,1,0,
		0,0,0,1);

	return rz* ry* rx;
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
	
	Vector3 Z = Vector3((position-target).Normalized()) ;
	
	return LookAtDirection(position , Z) ;
	//return LookAtDirection(position , target - position) ;
}
Matrix Matrix::LookAtDirection(Vector3 position, Vector3 eyeDirection)
{
	Vector3 up = Vector3(0,1,0);
	
	Vector3 Z = eyeDirection.Normalized();
	Vector3 X = Vector3(up.Cross(Z)).Normalized();
	Vector3 Y = Vector3(Z.Cross(X)).Normalized();
	
	
	Matrix M = Matrix(
		X.X , Y.X , Z.X , 0 ,
		X.Y , Y.Y , Z.Y , 0 ,
		X.Z , Y.Z , Z.Z , 0 ,
		0 , 0 , 0 , 1) ;

	Matrix T = Matrix::Translation(position*-1) ;

	return M * T ;
}

Matrix Matrix::XYScale(float WinMinX , float WinMaxX , float WinMinY , float WinMaxY , float Near , float Far)
{
	float DiffX = WinMaxX - WinMinX ;
	float DiffY = WinMaxY - WinMinY ;
	float DiffZ = Near - Far ;
	return Matrix(2/DiffX , 0 , 0 , 0,
					0 , 2/DiffY , 0 , 0,
					0 , 0 , (Near + Far) / DiffZ , (2*Near*Far) / DiffZ,
					0 , 0 , 0 , 1);

}
Matrix Matrix::PerspectiveFOV(float fov, float aspectRatio, float zNear, float zFar)
{
	/*
	float tanHalfFOV = (float)tanf((float)fov/2.0f);
	float zRange = zNear - zFar;
	cout << tanHalfFOV <<endl;
	Matrix r = Matrix(
		(float)1.0f / (float)tanHalfFOV * (float)aspectRatio , 0 , 0 , 0 ,
		0 , (float)1.0f / tanHalfFOV , 0 , 0 ,
		0 , 0 , (float)(-zNear -zFar)/zRange , (float) 2 * zFar * zNear / zRange , 
		0 , 0 , 1 , 0) ;
		*/
	Matrix r;

	const float ar         = aspectRatio;
	const float zRange     = zNear - zFar;
	const float tanHalfFOV = tanf( ToRad( fov / 2.0f ));

	r.Mtrx[0][0] = 1.0f/(tanHalfFOV * ar); r.Mtrx[0][1] = 0.0f;            r.Mtrx[0][2] = 0.0f;            r.Mtrx[0][3] = 0.0;
	r.Mtrx[1][0] = 0.0f;                   r.Mtrx[1][1] = 1.0f/tanHalfFOV; r.Mtrx[1][2] = 0.0f;            r.Mtrx[1][3] = 0.0;
	r.Mtrx[2][0] = 0.0f;                   r.Mtrx[2][1] = 0.0f;            r.Mtrx[2][2] = (-zNear - zFar)/zRange ; r.Mtrx[2][3] = 2.0f*zFar*zNear/zRange;
	r.Mtrx[3][0] = 0.0f;                   r.Mtrx[3][1] = 0.0f;           r.Mtrx[3][2] = -1.0f;            r.Mtrx[3][3] = 0.0;    

	return r;
}
Matrix Matrix::PerspectiveFOV2(float fov, float aspectRatio, float zNear, float zFar)
{
	return Matrix(cot(fov/2)/aspectRatio , 0 , 0 , 0 ,
					0 , cot(fov/2) , 0 , 0 ,
					0 , 0 ,/**/(zNear + zFar)/(zNear - zFar) , (2.0*zNear*zFar)/(zNear - zFar) ,
					0 , 0 , -1.0 , 0);
}
Matrix Matrix::OrthoGraphic(float left, float right, float bottom, float top, float near, float far)
{
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	Matrix r = Matrix(
		(float) 2/width , 0 , 0 , (float)-(right + left)/width ,
		0 , (float)2/height , 0 , (float)-(top + bottom)/height ,
		0 , 0 , (float)-2/depth , (float)-(far + near)/depth ,
		0 , 0 , 0 , 1);

	return r;
}
Matrix Matrix::Transpose()
{
	Matrix Mnew = *this;
	for(int i = 0 ; i < 4 ; ++i)
		for(int j = 0 ; j < 4 ; ++j)
			Mnew(i,j) = Mtrx[j][i] ;
	return Mnew;
}
