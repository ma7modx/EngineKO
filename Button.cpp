#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "stb_image.h"

#include "Button.h"
#include <iostream>

#include "GameController.h"
#include "GraphicsManager.h"

const float Zdimension = -1 ;

Button::Button(	const char*imageIcon , Vector2 pos , float width , float height)
{
	texID = LoadTexture(imageIcon);
	this->position = pos ;
	this->width = width ;
	this->height = height ;
}
bool Button::IsClicked()
{
//	std :: cout << Mouse::position.X << " " <<  position.X <<std :: endl; 
		
		if( Mouse::position.X < position.X + width/2  && 
		Mouse::position.Y < position.Y + height/2 &&
		Mouse::position.X > position.X - width/2  &&
		Mouse::position.Y > position.Y - height/2 
		)
	{
		//std :: cout << "Clicked !!\n";
		return true ;
	}
		return false ;
}

void Button::Draw()
{
	glBindTexture(GL_TEXTURE_2D, texID) ;
	glBegin(GL_QUADS);
	{
		glVertex3f(position.X + width/2 , position.Y + height/2 , Zdimension);	glTexCoord2f(1,0);
		glVertex3f(position.X - width/2 , position.Y + height/2 , Zdimension);	glTexCoord2f(1,1);
		glVertex3f(position.X - width/2 , position.Y - height/2 , Zdimension);	glTexCoord2f(0,1);
		glVertex3f(position.X + width/2 , position.Y - height/2 , Zdimension);	glTexCoord2f(0,0);
	}
	glEnd();
}

 unsigned int Button::LoadTexture(const char*filename)
{
	unsigned int texbufferID;

	glGenTextures(1, &texbufferID);
	glBindTexture(GL_TEXTURE_2D, texbufferID);

	int width = -1, height, dipth;
	auto load = stbi_load(filename, &width, &height, &dipth, 4);

	if(width == -1) std :: cout << "Wrong TexturePath " << filename << std :: endl ;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, load);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texbufferID;
}

