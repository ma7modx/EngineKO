#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "IGameModule.h"

class GameObject;

class GameComponent : public IGameModule
{
public :
	GameComponent(GameObject* parent , Vector3 pos) : IGameModule(parent , pos){}

};
