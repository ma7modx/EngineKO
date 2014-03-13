#pragma once 
#include "Shader.h"
#include "GraphicsHelpers.h"
#include <string>
using namespace std ;

class IShader // bfkr a5leh icomponent
{
public :
	IShader(string name , const char * vs , const char * fs) ;
	virtual void SetUniforms() = 0 ;
	virtual void Execute(void DrawFunPtr()) = 0;
	virtual VertexAttributes GetAttributes() = 0 ;
private :
	string name ;

};