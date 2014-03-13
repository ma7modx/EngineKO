#pragma once
#include "IShader.h"
#include "Matrix.h"
#include "Shader.h"
class TransformationShader : public IShader
{
public :

	TransformationShader(Matrix matrix) : IShader("TransformationShader" , "TransofrmationShader.vs" , "SimpleVertexShader.vertexshader")
	{
		this->matrix = matrix ;
	}
	void SetMatrix(Matrix matrix)
	{
		this->matrix = matrix ;
	}
	void SetUniforms()
	{
	}
	VertexAttributes GetAttributes() 
	{

	}
	void Execute(void DrawFunPtr())
	{
		tranShader->Active();
	
		tranShader->SetUniform("projection" , Matrix::Translation(Vector3(r+= 0.01,0,0)) ) ; // updaete
	}
private :
	Matrix matrix ;
};