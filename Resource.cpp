#include "Resource.h"
#include "GameController.h"
#include "ResourceManager.h"
Resource::Resource(string name , Resource* Data)
{
	this->name = name ;
	int handle = GameController::GetGameController()->Resourcemanager->Register(name  , Data) ;
	if(handle == -1)
	{
		delete Data ;
		Data = GameController::GetGameController()->Resourcemanager->Get(name) ;
	}
}
Resource::~Resource()
{
	//if(name != "")
	//GameController::GetGameController()->Resourcemanager->Delete(name) ;
}