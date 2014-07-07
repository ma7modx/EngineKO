#pragma once 
#include "MMath.h"
#include "GameObject.h"

class Camera : public GameComponent
{
public :
	Camera(Vector3 position , Vector3 eyeDirection_Angle_Deg) : GameComponent(NULL , position)
	{
		 this->eyeDirection = eyeDirection_Angle_Deg ; rotation = Vector2(0,0) ;
	}
	Matrix GetCameraMatrixLookAt()
	{
		return Matrix::LookAtDirection (position , eyeDirection) ;
	}
	
	void MoveCameraDirection(Vector3 eyeDirection_Angle_Deg)
	{
		this->eyeDirection = eyeDirection_Angle_Deg ;
	}
	
	void MoveCameraPosition(Vector3 pos)
	{
		this->position = pos ;
	}
	int excuteCameraCommand() 
	{
		
	}


//protected :
Vector3 eyeDirection ;
Vector2 rotation ; //pitch arround the x  (up or down), yaw arround the y
virtual void LockCamera()
{
	if(rotation.GetPitch() > 90)
		rotation.SetPitch(90) ;
	if(rotation.GetPitch() < -90)
		rotation.SetPitch(90) ;
	if(rotation.GetYaw() > 360)
		rotation.SetPitch(rotation.GetYaw() - 360) ;
	if(rotation.GetYaw() < 0)
		rotation.SetPitch(rotation.GetYaw() + 360) ;
}
};