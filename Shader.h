#pragma once
#include "Resource.h"
#include <map>
class Vector2;
class Vector3;
class Matrix ;
class Shader// : public Resource
{
public :
	Shader(string name , const char *vertex_file_path,const char *fragment_file_path) ;
	void Active();
	void Deactive();
	int GetProgramID() { return programID ; }
	int GetAttribute(const char* attrib);
	int GetUniform(const char* uniform);
	void SetUniform(const char* uniform , float);
	void SetUniform(const char* uniform , Vector2);
	void SetUniform(const char* uniform , Vector3);
	void SetUniform(const char* uniform , Matrix);
	//void Delete();
	// does nothing but there's delete function
	~Shader();
protected :
	unsigned int programID , VS , FS ;// vertex , fragment shaders
};