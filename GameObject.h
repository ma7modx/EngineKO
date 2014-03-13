#pragma once
#include <vector>
#include "GameComponent.h"
#include "UpdateBehavior.h"
#include "DrawBehavior.h"
#include "IGameModule.h"

class GameObject : public IGameModule
{
public :
	GameObject(GameObject* parent) : IGameModule(parent , Vector3::ZERO)
	{
	}
	GameObject(GameObject* parent , Vector3 pos) : IGameModule(parent , pos)
	{
	}
	void AddChild(GameObject x){ childs.push_back(x); }
	vector<GameObject> GetChilds(){return vector<GameObject>() ;}
	void AddComponents(GameComponent x){ components.push_back(x); }
	vector<GameComponent> GetComponents(){return vector<GameComponent>() ;}
	void SetUpdateBehavior (UpdateBehavior* Ubehavior)
	{
		updateBehavior = Ubehavior ;
	}
	void SetDrawBehavior (DrawBehavior*Dbehavior)
	{
		drawBehavior = Dbehavior ;
	}


private :
	UpdateBehavior* updateBehavior ;
	DrawBehavior* drawBehavior ;
	vector<GameObject> childs;
	vector<GameComponent> components;
};
