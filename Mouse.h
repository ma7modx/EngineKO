#pragma once
#include "Vector2.h"
class Mouse
{
public:
	static void Update();
	static Vector2 position ;
	static int button ;
private:
	
	static void processMouse(int button, int state, int x, int y);
};