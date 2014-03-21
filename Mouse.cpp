#pragma once
#include "Mouse.h"

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <iostream>
#include "stb_image.h"
#include "GameController.h"
#include "GraphicsManager.h"
void Mouse::Update()
{
	glutMouseFunc(processMouse);
}

void Mouse::processMouse(int button, int state, int x, int y)
{
	position.X = x;
	position.Y = y; //GameController::GetGameController()->Graphicsmanager->widnow.Windowheight - y;

	//position.X = x / GameController::GetGameController()->Graphicsmanager->widnow.WindoWidth ;
	//position.Y = y / GameController::GetGameController()->Graphicsmanager->widnow.Windowheight ;
	//std :: cout << x << " " << y << std :: endl;
	Mouse::button = 0 ;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) Mouse::button = 1 ;
	//else if(button == GLUT_RIGHT_BUTTON) Mouse::button = 1 ;

}

int Mouse::button = 0 ;
Vector2 Mouse::position = Vector2(0,0);