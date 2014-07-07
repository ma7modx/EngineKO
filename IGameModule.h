#pragma once
#include "Vector3.h"
#include "Matrix.h"
#include "DrawBehavior.h"
#include "UpdateBehavior.h"
#include "DebugManager.h"
#include <vector>
class GameObject ;

class IGameModule
{
public:
	IGameModule(Vector3 pos )
	{
		position = pos ;
		parent = NULL ;
		behaviors.resize(2);
	}
	IGameModule(GameObject* parent , Vector3 pos ) // in 7-6-2014 after 5 months of writing this code i think parent should be IGameModule
	{
		position = pos ;
		this->parent = parent ;
		
	}
	GameObject* GetParent()
	{
		if(!parent)
			DepugManager::ShowMessage("getting Null Parent");
		return parent ;
	}
	Vector3 GetPosition()
	{
		return position ;
	}
	void SetParent(GameObject* x)
	{
		parent = x ;
	}
	Matrix GetTransform()
	{
		return transform ;
	}
	void SetTransform(Matrix m)
	{
		transform = m ;
	}
	UpdateBehavior* GetUpdateBhavior()
	{
		if(!behaviors[0])
			DepugManager::ShowMessage("getting Null UpdateBehavior");

		return ((UpdateBehavior*)behaviors[0]) ;
	}
	void SetUpdateBehavior(UpdateBehavior* update)
	{
		behaviors[0] = update ;
	}
	DrawBehavior* GetDrawBhavior()
	{
		if(!behaviors[1])
			DepugManager::ShowMessage("getting Null DrawBehavior");

		return ((DrawBehavior*)behaviors[1]) ; ;
	}
	void SetDrawBhavior(DrawBehavior* draw)
	{
		behaviors[1] = draw ;
	}
protected:
	Vector3 position ;
	Matrix transform ;
 	vector<IBehavior*> behaviors ;
private:
	GameObject* parent ;// in 7-6-2014 after 5 months of writing this code i think parent should be IGameModule
};