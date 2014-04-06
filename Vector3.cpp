#include "Vector3.h"
#include "Matrix.h"

Vector3 Vector3::ZERO = Vector3(0,0,0) ;
Vector3 Vector3::UP = Vector3(0,1,0) ;

	Vector3::Vector3(){ X = Y = Z = 0; }
	Vector3::Vector3(float val)
	{
		Z = Y = X = val;
	}
	Vector3::Vector3(float X, float Y, float Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	
	Vector3 Vector3::operator-(Vector3 vec)
	{
		Vector3 res;
		res = X - vec.X ; 
		res = Y - vec.Y ;
		res = Z - vec.Z ;
		return res ;
	}
	Vector3 Vector3::operator+(Vector3 vec)
	{
		Vector3 res;
		res = X + vec.X ; 
		res = Y + vec.Y ;
		res = Z + vec.Z ;
		return res ;
	}
	Vector3 Vector3::operator *(float val)
	{
		return Vector3(X*val , Y*val , Z*val) ;
	}

	float Vector3::operator *(Vector3 vec)
	{
		Vector3 res;
		res.X = X * vec.X;
		res.Y = Y * vec.Y;
		res.Z = Z * vec.Z;
		return res.X + res.Y + res.Z ;
	}
	
	 Vector3 Vector3::operator*(Matrix mat)
	{
		Vector3 res ;
		for (int i = 0; i < 4; ++i)
		{
			float cell = 0;
			for (int j = 0; j < 4; ++j)
			{
				cell += mat(i, j) *(*this)[j];
			}
			res[i] = cell;
		}
		return res ;
	}

	Vector3 Vector3::operator ^(Vector3 vec) // cross product
	{
		Vector3 res;
		res.X = Y * vec.Z - Z * vec.Y;
		res.Y = Z * vec.X - X * vec.Z;
		res.Z = X * vec.Y - Y * vec.X;
		return res;
	}
	Vector3 Vector3::operator/(float val)
	{
		return Vector3(X/val , Y/val , Z/val) ;
	}
	float Vector3::operator [] (int i) const
	{
		if (i == 0) return X;
		if (i == 1) return Y;
		if (i == 2) return Z;
		else return 1;
	}
	float& Vector3::operator [](int i) //'ll debug it
	{
		if (i == 0) return X;
		if (i == 1) return Y;
		if (i == 2) return Z;
		else 
			throw exception ("Accessing a wrong index");
	}

	
float Vector3::Magnitude() 
{
    return sqrtf (Dot(*this));
}

Vector3 Vector3::LERP(Vector3 pos1 , Vector3 pos2 , float Gamma)
{
	return(Vector3((1-Gamma) *pos1.X + Gamma*pos2.X , (1-Gamma) *pos1.Y + Gamma*pos2.Y , (1-Gamma) *pos1.Z + Gamma*pos2.Z) ) ;
}

float Vector3::Dot( Vector3 v) 
{
  return (*this) * v ;
}

Vector3 Vector3::Cross( Vector3 v) 
{
   return (*this) ^ v ;
}

Vector3 Vector3::Normalized()
{
	return (*this)/Magnitude();
}

Vector3 Vector3::CalculateNormal(Vector3 a , Vector3 b , Vector3 c)
{
	Vector3 v1 = b - a, v2 = c - a ;
	return (v1^v2).Normalized() ;
}
