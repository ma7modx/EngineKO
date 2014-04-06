#include "BasicShader.h"
#include "Matrix.h"
#include <GL\glew.h>
#include <GL\GL.h>

BasicShader::BasicShader() : IShader("BasicShader" , "TransofrmationShader.vs" , "SimpleFragmentShader.frag")
{
	transformation = scale = view = Matrix::Identity() ;
	cout << "MAtrices : ";
	cout << transformation (0,0) << " " ;
	cout << transformation (0,1) <<endl ;
}
void BasicShader::SetUniforms(BasicShaderUniforms uniform , Matrix matrix)
{
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
	//scale.Show();
	this->SetUniform("viewMatrix" , view );
	//view.Show();
	this->SetUniform("transformation" ,transformation ) ; // update
	//transformation.Show();
	this->SetUniform("tex" , GL_LINEAR) ;

	attributes->AddAttribute(this->GetAttribute("inVertex"), VertexData::VERTEX) ;
	attributes->AddAttribute(this->GetAttribute("inColor"),  VertexData::COLOR);
	attributes->AddAttribute(this->GetAttribute("inTexCoord"),  VertexData::TEXTURE);

}
void BasicShader::End()
{
	this->Deactive();
}