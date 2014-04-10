#pragma once
#include "IShader.h"
#include "Matrix.h"
enum BasicShaderUniforms
{
	TRANSFORMATION = 0 , SCALE = 1, VIEW = 2  
};
class BasicShader : public IShader // Singleton Later
{
public: 
	BasicShader();
	void Begin();
	void End();
	void SetUniforms(BasicShaderUniforms uniform , Matrix matrix);
private:
	Matrix transformation , scale , view ;
};