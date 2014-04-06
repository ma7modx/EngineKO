#include "GameplayManager.h"
#include "PartOfGamePlay.h"
#include "GamePlayCaller.h"
#include "GameController.h"

GamePlayManager::GamePlayManager()
{		
	GameController::GetGameController()->GamePlaymanager = this ;
	CurrentPart = 0 ;
	Gameplay = new GamePlayCaller() ;
	Gameplay->CreateGameParts();
}
int GamePlayManager::GameUpdateLOOP()
{
	if(!Parts[CurrentPart]->Initialized)
	{
		Parts[CurrentPart]->Initialized = true ;
		Parts[CurrentPart]->Initialize();
	}
	else
	{
		Parts[CurrentPart]->Update();

		if(Parts[CurrentPart]->Finished())
		{
			delete Parts[CurrentPart];
			CurrentPart++;
			if(CurrentPart == Parts.size()-1) 
			{
				return -1 ;
			}
		}
	}
	return 0 ;
}

int  GamePlayManager::GameDrawLOOP()
{
	if(Parts[CurrentPart]->Initialized)
		Parts[CurrentPart]->Draw();
	return 0 ;
}

GamePlayManager::~GamePlayManager()
{
	delete Gameplay;
}