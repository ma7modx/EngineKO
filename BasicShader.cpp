#include "BasicShader.h"
#include "Matrix.h"
#include <GL\glew.h>
#include <GL\GL.h>
#include "Vector3.h"

BasicShader::BasicShader() : IShader("BasicShader" , "TransofrmationShader.vs" , "LightFragShader.frag")
{
	transformation = scale = view = Matrix::Identity() ;
}
void BasicShader::SetUniforms(BasicShaderUniforms uniform , Matrix matrix)
{
	float w = 1 , h = 1 ;
	glBegin(GL_QUADS);
	{
		glVertex3f(3+w/2,3+h/2,3);
		glVertex3f(3-w/2,3+h/2,3);
		glVertex3f(3-w/2,3-h/2,3);
		glVertex3f(3+w/2,3-h/2,3);
	};
	glEnd();
	if(uniform == 0)
		transformation= matrix ;
	else if(uniform ==1)
		scale = matrix ;
	else if(uniform == 2)
		view = matrix ;
	else
		throw exception ("not Exist") ;
}
void BasicShader::Begin()
{
	this->Active();
	this->SetUniform("scale" ,scale);
	this->SetUniform("viewMatrix" , view );
	this->SetUniform("transformation" ,transformation ) ; // update
	this->SetUniform("tex" , GL_LINEAR) ;
	
	this->SetUniform("LightSource" ,  Vector3(3,3,3)) ;

	attributes->AddAttribute(this->GetAttribute("inVertex"), VertexData::VERTEX) ;
	attributes->AddAttribute(this->GetAttribute("inColor"),  VertexData::COLOR);
	attributes->AddAttribute(this->GetAttribute("inTexCoord"),  VertexData::TEXTURE);
	attributes->AddAttribute(this->GetAttribute("inNormal"),  VertexData::NORMAL);
	
}
void BasicShader::End()
{
	this->Deactive();
}