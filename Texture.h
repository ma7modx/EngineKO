#pragma once
#include "Resource.h"

class Texture// : public Resource
{
public:
	Texture(int ID) ;
	Texture(int ID , string name) ;
	Texture(string name , char* filename) ;
	static unsigned int LoadTexture(const char *filename);
	unsigned int GetID(){return ID ;}
	void Use() ;
	// removes texture frm buffer
	~Texture();
private :
		unsigned int ID;
		
};