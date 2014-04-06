#include "stb_image.h"
#include "Texture.h"
#include "GameController.h"
#include "GraphicsManager.h"


Texture::Texture(int ID) //:Resource(1)
	{
		this->ID = ID ;
	}
Texture::Texture(int ID , string name) //: Resource(name , this)
	{
		this->ID = ID ;
	}
Texture::Texture(string name , char* filename) //: Resource(name , this)
	{
		ID = LoadTexture(filename);
	}
unsigned int Texture::LoadTexture(const char *filename)
	{
		return GameController::GetGameController()->Graphicsmanager->LoadTexture(filename) ;
	}
void Texture::Use()
{
	GameController::GetGameController()->Graphicsmanager->BindTexture(ID);
}
Texture::~Texture()
{
	GameController::GetGameController()->Graphicsmanager->DeleteTexture(&ID);
}