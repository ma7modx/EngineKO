#include "IShader.h"
#include "ResourceManager.h"
#include "GameController.h"

IShader::IShader(string name , const char * vs , const char * fs) 
{
	this->name = name ;
	new Shader(name , vs , fs) ; // register
}
	