#pragma once
#include <string>
#include "Window.h"
#include "GraphicsHelpers.h"
#include "Vector2.h"
#include "Vector3.h"

class GraphicsManager
{
public:
	Window widnow;
	int iArgc; char** cppArgv;

public:
	GraphicsManager(Window window){ this->widnow = window; }
	virtual void Start() = 0;
	virtual void LOOP() = 0;

	virtual unsigned int LoadTexture(const char*filename) = 0;
	virtual void BindTexture(unsigned int ID) = 0;
	virtual void DeleteTexture(int size , unsigned int* ptr) = 0;
	virtual void DeleteTexture(unsigned int* IDptr) = 0;

	// set vertex once using vertexdata .. problem wth casting no net
	//virtual void SetVertex(VertexData , IVertex) =0;
	virtual void SetVertexPosition(Vector3 pos) = 0;
	virtual void SetVertexColor(MColor color) = 0;
	virtual void SetVertexTexCoord(Vector2 texcoord) = 0;
	virtual void SetVertexNormal(Vector3 Normal) = 0;

	virtual void BeginTriangle() = 0;
	virtual void EndTriangle() = 0;
	virtual void BeginLine() = 0;
	virtual void EndLine() = 0;
	virtual void BeginQuad() = 0;
	virtual void EndQuad() = 0;

	virtual void BeginDrawList(int& ID) = 0;
	virtual void EndDrawList() = 0;
	virtual void DeleteDrawList(int ID) = 0;

	virtual unsigned int LoadShader(const char *vertex_file_path, const char *fragment_file_path , unsigned int& out_VS , unsigned int& out_FS )= 0;
	virtual void ActiveShader(unsigned int ID) = 0;
	virtual void DeactiveShader() = 0;
	virtual void DeleteShader(unsigned int programID, unsigned int VS , unsigned int FS) = 0;
	virtual int GetShaderAttrib(unsigned int ID, const char* attribName) = 0;
	virtual int GetShaderUniform(unsigned int ID, const char* attribName) = 0;
	virtual void ShaderUniformf(unsigned int Location, float f1) = 0;
	virtual void ShaderUniformf(unsigned int Location, Vector2) = 0;
	virtual void ShaderUniformf(unsigned int Location, Vector3) = 0;
	virtual void ShaderUniformMat(unsigned int Location, Matrix) = 0;
	
	virtual void FillBuffer(unsigned int BufID, void* data, int sizeOfarrayInBytes, GPUDrawMode Mode, BufferType BType) = 0;//allocate and bind and save data
	virtual void BindBuffer(BufferType Btype , unsigned int BufID) = 0;
	virtual void ReserveBuffer(unsigned int& BufID) = 0;
	virtual void DeleteBuffer(int size , unsigned int* ptr) = 0;
	virtual void DeleteBuffer(unsigned int* IDptr) = 0;
	
	virtual void VBOModeDraw(int numOfVertices, int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape) = 0;

	virtual void IVBOModeDraw(unsigned int ibo, int numOfIndices ,int numOfVertices , int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape) = 0;

	virtual void VBOShaderModeDraw(int numOfVertices, int numOfShaders, int ShaderAttributesindices[], int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape) = 0;

	virtual void IVBOShaderModeDraw(unsigned int ibo , int numOfIndices, int numOfShaders, int ShaderAttributesindices[], int strideBetweenVertices, void* pointerToTheBeginingOfData[], VertexData mode, Shapes shape) = 0;

	virtual void ListDrawBegin(int &ID) = 0;
	virtual void ListDrawEnd() = 0;
	virtual void ListDraw(int ID) = 0;
};