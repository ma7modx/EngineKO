#pragma once
#include <vector>
#include "Vertex.h"
#include "Vector3.h"
#include "Matrix.h"
#include "GameObject.h"
#include "IGameModule.h"
using namespace std ;

class Shape //:IObject
{
public :
	Vector3 Position ;
	Shape()
	{
		Position = Vector3(0);
	}//: IObject(Vector3(0)) {} 
	virtual void Transform(Matrix Transformation) {};
	virtual void Draw() = 0 ;
	virtual void Debug() =0 ;
};

class VShape : public Shape  
{
public :
	vector<IVertex*> vertices ;
	int numOfVertices ;
	VShape(int numOfVertices) {  this->numOfVertices = numOfVertices ; vertices.resize(numOfVertices) ;} 
	void Transform(Matrix Transformation);
	void Debug();
	~VShape(){
		for(int i = 0 ; i < vertices.size() ; ++i)
		delete  vertices[i] ; 
		vertices.clear();
	} 
	
};


class Line : public VShape 
{
public :
	Line() : VShape(0) {}

	Line(IVertex *V1, IVertex *V2):VShape(2)
	{
		vertices[0] = V1;
		vertices[1] = V2;
	}
	
	void Draw();
};

class Triangle:public VShape
{
public:
	
	Triangle():VShape(0) {}

	Triangle(IVertex *V1, IVertex *V2, IVertex *V3):VShape(3)
	{
		vertices[0] = V1;
		vertices[1] = V2;
		vertices[2] = V3;
	}
	
	void Draw();
};


class GeometryIMT : public Shape
{
public :
	int NumOfTriangles ;
	GeometryIMT(int NumOfTriangles) { this->NumOfTriangles = NumOfTriangles ; Triangles.resize(NumOfTriangles) ; } 
	void Draw() ;
	void DrawRange(int start , int end) ;
	void Debug() ;
	void DebugRange(int start , int end) ;
	~GeometryIMT() 
	{ 
		for(int i = 0 ; i < Triangles.size() ; ++i)
			delete Triangles[i]  ; 
	} 
protected :
	vector<Triangle*> Triangles ;
	
private :
	void DebugSingleTriangle(int Index) ;
	void DrawSingleTriagle(int Index) ;
};

class Quad : public VShape
{
public :
	Quad():VShape(0){}
	Quad(IVertex*vertices [4]) : VShape(4)
	{
		this->vertices[0] = vertices[0] ;
this->vertices[1] = vertices[1] ;
this->vertices[2] = vertices[2] ;
this->vertices[3] = vertices[3] ;

	}
	Quad(IVertex *DL, IVertex *UL, IVertex *UR , IVertex *DR): VShape(4)
	{
		this->vertices[0] = DL;
this->vertices[1] = UL ;
this->vertices[2] = UR ;
this->vertices[3] = DR ;
	}
	void Transform(Matrix Transformation){}
	void Draw();
};
