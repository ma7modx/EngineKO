#pragma once
#include <vector>
class GamePlayCaller
{
public :
	void CreateGameParts();
	void DeleteGameParts();
private :
	vector<PartOfGamePlay*> GameParts ;
};
// cpp file in source code that wats user deal wth