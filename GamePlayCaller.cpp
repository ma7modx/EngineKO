#include "_Game1.h"
#include "GamePlayCaller.h"

void GamePlayCaller::CreateGameParts()
	{
		GameParts.push_back( new _Game1() ) ;
	}
/// <summary>
/// Deletes the game parts.
/// </summary>
void GamePlayCaller::DeleteGameParts()
	{
		GameParts[0]->Delete();
		delete GameParts[0] ;
	}