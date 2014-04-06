#include "GameController.h"
#include "GameplayManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "MemoryManager.h"
#include "GamePlayCaller.h"
#include "KeyboardInput.h"
#include <iostream>

GameController* GameController::Controller = NULL;

GameController::GameController(GraphicsManager* Graphicsmanager , MemoryManager* Memorymanager = new MemoryManager(1))
	{
		Graphicsmanager->Start();
		
		Controller = this ;

		this->Memorymanager = Memorymanager ;
	
		(this->Graphicsmanager) = (Graphicsmanager) ;
		
		Resourcemanager = new ResourceManager() ;

		GamePlaymanager = new GamePlayManager() ;

		Graphicsmanager->LOOP();
	}
void GameController::GameUpdateLOOP()
	{
		keyboard->GetStates();

		int Exit = GamePlaymanager->GameUpdateLOOP() ;
		
		if(Exit == -1)
			GameEnd();

	}
void GameController::GameDrawLOOP()
	{
		// scene
		 GamePlaymanager->GameDrawLOOP() ;
	}
void GameController::GameEnd()
	{
		GamePlaymanager->GetGamePlay()->DeleteGameParts();
	}

  GameController::~GameController()
  {
	  delete Memorymanager ;
	  delete Resourcemanager ;
	  delete GamePlaymanager ;
  }