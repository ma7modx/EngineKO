#include "BasicShader.h"
#include "Matrix.h"
#include <GL\glew.h>
#include <GL\GL.h>
#include "Vector3.h"

BasicShader::BasicShader() : IShader("BasicShader" , "TransofrmationShader.vs" , "LightFragShader.frag")
{
	transformation = scale = view = projection = Matrix::Identity() ;
	isTexture = false ;
}
BasicShader::BasicShader(const char* shadername ,const char* vs ,const char* fs ) : IShader(shadername , vs , fs)
{
	transformation = scale = view = projection = Matrix::Identity() ;
	isTexture = false ;
}
void BasicShader::SetUniforms(BasicShaderUniforms uniform , Matrix matrix)
{
	
	if(uniform == 0)
		transformation= matrix ;
	else if(uniform ==1)
		scale = matrix ;
	else if(uniform == 2)
		view = matrix ;
	else if(uniform == 3)
		if(matrix == 1)
			isTexture = true ;
		else
			isTexture = false ;
	else if(uniform == 4)
		projection = matrix;
	else
		throw exception ("not Exist") ;
}
void BasicShader::SetTrasnformationUniforms(Matrix proj , Matrix View , Matrix Transformation)
{
	SetUniforms(BasicShaderUniforms::PROJECTION ,proj ) ;
	SetUniforms(BasicShaderUniforms::VIEW ,  View );
	SetUniforms(BasicShaderUniforms::TRANSFORMATION , Transformation);
}
void BasicShader::Begin()
{
	this->Active();
	this->SetUniform("scale" ,scale);
	this->SetUniform("viewMatrix" , view);
	this->SetUniform("projection" , projection );
	this->SetUniform("transformation" ,transformation ) ; // update
	this->SetUniform("tex" , GL_LINEAR) ;
	
	this->SetUniform("LightSource" ,  Vector3(0,1,0)) ;

	this->SetUniform("IsTexture" ,(float)isTexture ) ;
	
	//glUniform1i( glGetUniformLocation(this->programID, "tex"), 0);
		
	attributes->AddAttribute(this->GetAttribute("inVertex"), VertexData::VERTEX) ;
	attributes->AddAttribute(this->GetAttribute("inColor"),  VertexData::COLOR);
	attributes->AddAttribute(this->GetAttribute("inTexCoord"),  VertexData::TEXTURE);
	attributes->AddAttribute(this->GetAttribute("inNormal"),  VertexData::NORMAL);
	
}
void BasicShader::End()
{
	this->Deactive();
}

void BasicShader::Customize(int vertexdata)
{
	if( (vertexdata & 1) == 0)
	attributes->AddAttribute(-1 , VertexData::VERTEX);
	
	if( (vertexdata & 2) == 0)
		attributes->AddAttribute(-1 , VertexData::COLOR);
	
	if( (vertexdata & 4) == 0)
		attributes->AddAttribute(-1 , VertexData::NORMAL);
	
	if( (vertexdata & 8) == 0)
			attributes->AddAttribute(-1 , VertexData::TEXTURE);
	
}