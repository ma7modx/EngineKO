#include "stb_image.h"
#include "Texture.h"
#include "GameController.h"
#include "GraphicsManager.h"


Texture::Texture(int ID) :Resource(1)
	{
		this->ID = ID ;
	}

Texture::Texture(int ID , string name) : Resource(name , this)
	{
		this->ID = ID ;
	//	Resource::Resource(name , this) ; should be
	}
Texture::Texture(string name , char* filename) : Resource(name , this)
	{
		ID = LoadTexture(filename);
	}
unsigned int Texture::LoadTexture(const char *filename)
	{
		/*
		unsigned int texbufferID;
		
		GameController::GetGameController()->Graphicsmanager->AllocateTexture(&texbufferID);
		GameController::GetGameController()->Graphicsmanager->BindTexture(texbufferID);
		
		int width, height, dipth;
		auto load = stbi_load(filename, &width, &height, &dipth, 4); 

		GameController::GetGameController()->Graphicsmanager->AssignTexture(width , height , dipth , load) ;
		*/
		return GameController::GetGameController()->Graphicsmanager->LoadTexture(filename) ;
	}