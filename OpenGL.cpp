//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "opengl32.lib")
// Project Properties -> Linker -> Input -> Additional Dependencies

#pragma once
#include "OpenGL.h"
#include <GL\glew.h>
#include <GL\glut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "GameController.h"
using namespace std;

void OpenGL::UpdateCall()
{
	updateFinished = false;
	if(!ClosePrograme)
	{
		calculateFPS();

		GameController::GetGameController()->GameUpdateLOOP();
		// calculate elapsed time
	}
	updateFinished = true ;
}
void OpenGL::DrawCALL()
{
	drawFinished = false ;
	if(!ClosePrograme)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameController::GetGameController()->GameDrawLOOP();
	
		if(!ClosePrograme)
			glutSwapBuffers();
		//draw finished && ..
		if(updateFinished&& !ClosePrograme)
			glutPostRedisplay();
		
	}
	drawFinished = true ;
}
void OpenGL::Close()
{
	ClosePrograme = true ;
	if(drawFinished && updateFinished)
	{

	glutLeaveMainLoop();
	
	/*
	while (true)
	{
		if(drawFinished && updateFinished)
			break;
	}
	*/

	GameController::GetGameController()->GameEnd();
	}	
}
void OpenGL::Timer(int iUnused)
{
	glutPostRedisplay();
	glutTimerFunc(GameController::GetGameController()->Graphicsmanager->widnow.FramesPerSec, Timer, 1);//1 to 30 to inf [very fast = 1] , 10
}
void OpenGL::LOOP()
{
	/*
	while(!ClosePrograme)
	{
	UpdateCall();
	DrawCALL();
	//glutMainLoopEvent();
	}
	*/
	
	try {
		glutCloseFunc(Close); 
		glutIdleFunc(UpdateCall);
		glutDisplayFunc(DrawCALL);
		glutMainLoop();
	}
	catch (exception x){cout << "darab" <<endl ;}
	
}

int OpenGL::frameCount = 0 ;
int OpenGL::previousTime = 0;
float OpenGL::angle = 0 ;
bool OpenGL::ClosePrograme = false ;
bool OpenGL::updateFinished = false ;
bool OpenGL::drawFinished = false ;

void OpenGL::DeleteBuffer(int size , unsigned int* ptr)
{
	glDeleteBuffers(size , ptr);
}
void OpenGL::DeleteBuffer(unsigned int* IDptr)
{
	DeleteBuffer(1,IDptr);
}

void OpenGL::DeleteTexture(int size , unsigned int* ptr)
{
	glBindTexture(GL_TEXTURE_2D , 0);
	glDeleteTextures(size , ptr);
}
void OpenGL::DeleteTexture(unsigned int* IDptr)
{
	DeleteTexture(1 ,IDptr);
}