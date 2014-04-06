#pragma once
#include "GameController.h"
#include "OpenGL.h"
#include <iostream>
#include "MemoryManager.h"
#include "IBehavior.h"
#include "DrawBehavior.h"
#include "TryDrawBEhavior.h"
using namespace std ;
class A
{
public: 
	~A(){cout << "s\n" ;}
};
class B : public A
{
public: 
	~B(){cout << "k\n" ;
	}
};
int main(int iArgc, char** cppArgv) 
{
	B* s = new B();
	delete s ;

	OpenGL* openGL = new  OpenGL(iArgc , cppArgv , Window("asd" , MColor(200,200,250,0) , 800 , 600 , Vector2(190,50) , 10, 0.00001,1000000,45) );
	GameController* GC = new GameController(openGL  , new MemoryManager(0) ) ;
	delete openGL;
	delete GC ;
	return 0 ;
}
