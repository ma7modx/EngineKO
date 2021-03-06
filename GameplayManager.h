#pragma once
#include <vector>
using namespace std ;

class PartOfGamePlay;
class GamePlayCaller;

class GamePlayManager
{
public :
	vector<PartOfGamePlay*> Parts ;

	GamePlayManager();

	GamePlayCaller* GetGamePlay()
	{
		return Gameplay;
	}
	
	int GameUpdateLOOP();
	int GameDrawLOOP();
	// delete GameplayCaller Gameplay
	~GamePlayManager();
private :
	GamePlayCaller* Gameplay ;
	int CurrentPart ;
};