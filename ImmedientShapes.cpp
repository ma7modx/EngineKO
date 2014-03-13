#include "ImmedientShapes.h"
#include "GameController.h"
#include "GraphicsManager.h"


void VShape::Transform(Matrix Transformation)
{
	Position = Position * Transformation ;
	for(int i = 0 ; i < vertices.size() ; ++i)
		vertices[i]->Position =  vertices[i]->Position * Transformation ; 
}

void VShape::Debug()
{
	GameController::GetGameController()->Graphicsmanager->BeginLine();

	for(int i = 0 ; i < vertices.size() ; ++i)
		for(int j = i+1 ; j < vertices.size() ; ++j)
		{
			vertices[j]->SetVertex();
			vertices[i]->SetVertex();	
		}

	GameController::GetGameController()->Graphicsmanager->EndLine();
}


void Line::Draw()
{
	GameController::GetGameController()->Graphicsmanager->BeginLine();

		vertices[0]->SetVertex() ;
		vertices[1]->SetVertex() ;

	GameController::GetGameController()->Graphicsmanager->EndLine();
}

void Triangle::Draw()
{
	GameController::GetGameController()->Graphicsmanager->BeginTriangle();

		vertices[0]->SetVertex() ;
		vertices[1]->SetVertex() ;
		vertices[2]->SetVertex() ;

	GameController::GetGameController()->Graphicsmanager->EndTriangle();
}


void GeometryIMT::DebugSingleTriangle(int Index)
{
	Triangles[Index]->vertices[0]->SetVertex();	Triangles[Index]->vertices[1]->SetVertex();
	Triangles[Index]->vertices[1]->SetVertex();	Triangles[Index]->vertices[2]->SetVertex();
	Triangles[Index]->vertices[2]->SetVertex();	Triangles[Index]->vertices[0]->SetVertex();

}
void GeometryIMT::DrawSingleTriagle(int Index)
{
	Triangles[Index]->vertices[0]->SetVertex() ;
		Triangles[Index]->vertices[1]->SetVertex() ;
		Triangles[Index]->vertices[2]->SetVertex() ;

}
void GeometryIMT::DrawRange(int start , int end)
{
	GameController::GetGameController()->Graphicsmanager->BeginTriangle();

	for(int i = start ; i <= end ; ++i)
		DrawSingleTriagle(i) ;

	GameController::GetGameController()->Graphicsmanager->EndTriangle();
}
void GeometryIMT::DebugRange(int start , int end)
{
	GameController::GetGameController()->Graphicsmanager->BeginLine();

	for(int i = start ; i <= end ; ++i)
		DebugSingleTriangle(i) ;

	GameController::GetGameController()->Graphicsmanager->EndLine();
}
void GeometryIMT::Draw()
{
	DrawRange(0,NumOfTriangles-1) ;
}
void GeometryIMT::Debug()
{
	DebugRange(0,NumOfTriangles-1) ; 
}
void Quad::Draw()
{
	GameController::GetGameController()->Graphicsmanager->BeginQuad();

	vertices[0]->SetVertex();
	vertices[1]->SetVertex();
	vertices[2]->SetVertex();
	vertices[3]->SetVertex();

	GameController::GetGameController()->Graphicsmanager->EndQuad();
}