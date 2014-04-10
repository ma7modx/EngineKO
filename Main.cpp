#pragma once
#include "GameController.h"
#include "OpenGL.h"
#include <iostream>
#include "MemoryManager.h"
#include "IBehavior.h"
#include "DrawBehavior.h"
#include "TryDrawBEhavior.h"

using namespace std ;

int main(int iArgc, char** cppArgv) 
{
	OpenGL* openGL = new  OpenGL(iArgc , cppArgv , Window("asd" , MColor(200,200,250,0) , 800 , 600 , Vector2(190,50) , 10, 0.00001,1000000,45) );
	GameController GC = GameController(openGL  , new MemoryManager(0) ) ;
	delete openGL;
	
	return 0 ;
}
