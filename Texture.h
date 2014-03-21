#pragma once
#include "Resource.h"
class Texture : public Resource
{
public:
	Texture(int ID) ;
Texture(int ID , string name) ;
	Texture(string name , char* filename) ;
	static unsigned int LoadTexture(const char *filename);
	int GetID(){return ID ;}
	~Texture(){}
private :
		int ID;
		
};