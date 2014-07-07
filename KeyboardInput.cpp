#pragma once
#include "OpenGL.h"
#include "KeyboardInput.h"
#include <iostream>

using namespace std;


void KeyboardInput::GetStates() // make it in openGL header and call it frm here
{
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	//for()  .. pressedkey |= it 
}


void KeyboardInput::keyPressed(unsigned char key, int x, int y)
{
	cout <<(char) key << endl;
	if(key == 27)
		{
			OpenGL::ClosePrograme = true ;
			return ;
			glutExit();
	}
	//keyStates[key] = true;
	//SetOfPressedKeys.insert(key);
}
void KeyboardInput::keyUp(unsigned char key, int x, int y)
{
	//keyStates[key] = false; // Set the state of the current key to not pressed  
	//SetOfPressedKeys.erase(key);
}
unsigned char c(char letter)
{
	return (unsigned char)letter;
}