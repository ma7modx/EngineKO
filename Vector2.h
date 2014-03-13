#pragma once
class Vector2
{
public:
	float X, Y;
public:
	Vector2(){};
	Vector2(float x , float y){this->X = x ; this->Y = y ;};
	Vector2 operator +(Vector2 vec)
	{
		Vector2 res;
		res.X = X + vec.X;
		res.Y = Y + vec.Y;
		return res;
	}
	
	void SetYaw(float Yaw)
	{
		 Y = Yaw ;
	}
	float GetYaw()
	{
		return Y ;
	}
	void SetPitch(float Pitch)
	{
		 X = Pitch ;
	}
	float GetPitch()
	{
		return X ;
	}
	
	Vector2 operator *(Vector2 vec)
	{
		Vector2 res;
		res.X = X * vec.X;
		res.Y = Y * vec.Y;
		return res;
	}
	~Vector2(){};
};
