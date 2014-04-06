#pragma once

#include <iostream>

using namespace std ;

class Vector3 ;
class Matrix
{
public:
	float Mtrx[4][4];

public:
	Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	Matrix();

	static Matrix Identity();

	void Show();


#pragma region Operators
	Matrix operator*(Matrix mtrx1);
	Matrix operator*(float num);
	float operator() (int i, int j) const;
	float& operator() (int i, int j);

	static Matrix Translation(Vector3 translation);

	static Matrix Rotation( Vector3 AnglesInDegree);

	static Matrix Scale( Vector3 scale);
	
	static Matrix LookAt(Vector3 position, Vector3 target);
	static Matrix LookAtDirection(Vector3 position, Vector3 eyeDirection);
	static Matrix PerspectiveFOV(float fov, float aspectRatio, float zNear, float zFar);
	static Matrix OrthoGraphic(float left, float right, float bottom, float top, float near, float far);


	void ApplyOn(Vector3& vec);

	static void ApplyOn(Matrix mat , Vector3& vec);

#pragma endregion

	//~Matrix(){}
	// look at 
	// projection 
	//prespectivefield
};