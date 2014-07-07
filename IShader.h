#pragma once 
#include "Shader.h"
#include "GraphicsHelpers.h"
#include <string>
using namespace std ;

class IShader : public Shader
{
public :
	IShader(string name , const char * vs , const char * fs) : Shader(name , vs , fs) 
	{
		attributes = new VertexAttributes();
	}
	virtual void Begin() = 0;
	virtual void End() = 0;
	int* GetAttributes()
	{
		return attributes->GetAttributes();
	}
	~IShader()
	{
		//Delete();
		delete attributes ;
	}

//protected:
	VertexAttributes* attributes ;
};