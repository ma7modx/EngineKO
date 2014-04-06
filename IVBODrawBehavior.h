#include "DrawBehavior.h"
#include "GeometryIVBO.h"
#include "Vertex.h"
class IVBODrawBehavior : public DrawBehavior
{
public:
	IVBODrawBehavior(int numOfVertices , IVertex vertices[] , int numOfIndices , int indices[]) 
	{
		geometry = new GeometryIVBO (numOfVertices , vertices, numOfIndices , indices ) ;
	}

	~IVBODrawBehavior() 
	{
		delete geometry;
	}

	GeometryIVBO* GetGeometry()
	{
		return geometry;
	}
	void SetGeometry(GeometryIVBO* geometry)
	{
		this->geometry = geometry;
	}
	void Draw()
	{
		geometry->Draw();
	}

private:
	GeometryIVBO* geometry;
};
