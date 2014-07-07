#pragma once
#include "IShader.h"
#include "Matrix.h"
#include "GraphicsHelpers.h"
enum BasicShaderUniforms
{
	TRANSFORMATION = 0 , SCALE = 1, VIEW = 2 , ISTEXTURE = 3 , PROJECTION = 4 
};
class BasicShader : public IShader // Singleton Later
{
public: 
	BasicShader();
	BasicShader(const char* shadername ,const char* vs ,const char* fs );
	void Begin();
	void End();
	void SetUniforms(BasicShaderUniforms uniform , Matrix matrix);
	void SetTrasnformationUniforms(Matrix proj , Matrix View , Matrix Transformation);
	void Customize(int vertexdata);
private:
	Matrix transformation , scale , view , projection;
	bool isTexture;
};