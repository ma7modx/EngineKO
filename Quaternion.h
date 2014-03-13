#pragma once
#include "Vector4.h"
#include <math.h>
class Quaternion : public Vector4
{
public :
	Quaternion(float x ,float y ,float z ,float w )
	{
		Vector4(x , y , z , w) ;
	}
	float Length()
	{
		return sqrt(X*X + Y*Y + Z*Z + W*W);
	}
	Quaternion Normalize()
	{
		float len = Length() ;
		Quaternion Q = *this;
		Q.X/= len ;
		Q.Y/= len ;
		Q.Z/= len ;
		Q.W/= len ;
		return Q;
	}
	Quaternion operator *(Quaternion val)
	{
		return Quaternion(
			X * val.W + W * val.X + Y * val.Z - Z * val.Y  ,
			Y* val.W + W*val.Y + Z*val.X - X*val.Z ,
			Z* val.W + W *val.Z + X*val.Y - Y * val.X ,
			W * val.W - X* val.X - Y*val.Y - Z*val.Z ) ;				
	}
	Quaternion Conjugate()
	{
		return Quaternion(-X , -Y , -Z , W) ;
	}
};