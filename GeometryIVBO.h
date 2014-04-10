#pragma once
#include "ImmedientShapes.h"
#include "GraphicsManager.h"
#include "ModelHelpers.h"
#include "ImmedientShapes.h"
//#include "GameObject.h"

class GeometryIVBO : public Shape
{
public:
	GeometryIVBO(int numOfVerices, IVertex vertex[], int numOfIndices, int Indices[]);
	// void SetVertices 
	void Edit(int start, int end, float arr[]){}
	void Transform(Matrix Transformation){}
	void Update(){}
	void Draw(){ Draw(Shapes::TRIANGLE); }
	void Debug(){ Draw(Shapes::LINE); }
	void Draw(Shapes);
	void Draw(int shaderAttributesIndices[], Shapes);
	void Draw(int numOfShaderAttributes, int shaderAttributesIndices[], Shapes);
	void Draw(int numOfShaderAttributes, int shaderAttributesIndices[]);
	unsigned int GetNumOfVertices() { return numOfVertices; }
	int GetVBOID() { return vbo; }
	//void Delete();

	// does nothing but there's delete function to use instead
	~GeometryIVBO();
private:
	unsigned int vbo;
	unsigned int ibo;
	VertexData Mode;
	int vertexSize;
	int numOfVertices;
	int numOfIndices;
	void* Offsets[10]; // was offsets[];
	void DetermineOffset(IVertex *v);

};