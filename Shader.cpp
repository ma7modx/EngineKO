#include "Shader.h"
#include "GameController.h"
#include "GraphicsManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"

Shader::Shader(string name , const char *vertex_file_path,const char *fragment_file_path) //:Resource(name , this)
	{
		programID = GameController::GetGameController()->Graphicsmanager->LoadShader(vertex_file_path , fragment_file_path , VS , FS) ;
	}
void Shader::Active()
{
	GameController::GetGameController()->Graphicsmanager->ActiveShader(programID);
}
void Shader::Deactive()
{
	GameController::GetGameController()->Graphicsmanager->DeactiveShader();
}
int Shader::GetAttribute(const char* attrib)
{
	return GameController::GetGameController()->Graphicsmanager->GetShaderAttrib(programID , attrib) ;
}
int Shader::GetUniform(const char* uniform)
{
	return GameController::GetGameController()->Graphicsmanager->GetShaderUniform(programID , uniform);
}
void Shader::SetUniform(const char* uniform , float f)
{
	GameController::GetGameController()->Graphicsmanager->ShaderUniformf(GetUniform(uniform) , f) ;
}
void Shader::SetUniform(const char* uniform , Vector2 f)
{
	GameController::GetGameController()->Graphicsmanager->ShaderUniformf(GetUniform(uniform) , f) ;
}
void Shader::SetUniform(const char* uniform , Vector3 f)
{
	GameController::GetGameController()->Graphicsmanager->ShaderUniformf(GetUniform(uniform) , f) ;
}
void Shader::SetUniform(const char* uniform , Matrix f)
{
	GameController::GetGameController()->Graphicsmanager->ShaderUniformMat(GetUniform(uniform) , f) ;
}
/*
void Shader::Delete()
{
	GameController::GetGameController()->Graphicsmanager->DeleteShader(programID , VS , FS) ;
}
*/
Shader::~Shader()
{
	GameController::GetGameController()->Graphicsmanager->DeleteShader(programID , VS , FS) ;
}