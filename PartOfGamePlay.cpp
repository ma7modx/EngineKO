#include "PartOfGamePlay.h"
#include "GameplayManager.h"
#include "MemoryManager.h"
#include "GameController.h"

PartOfGamePlay::PartOfGamePlay()
	{
		Memory = GameController::GetGameController()->Memorymanager ;
		Initialized =  false ;
		GameController::GetGameController()->GamePlaymanager->Parts.push_back(this);
	}
