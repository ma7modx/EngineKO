#pragma once
#include "GeometryIVBO.h"
#include "GameController.h"
#include "GraphicsManager.h"

GeometryIVBO::GeometryIVBO(int numOfVerices , IVertex vertex[] , int numOfIndices , int Indices[])//:GameObject()// this
{
	this->numOfVertices = numOfVerices ;
	this->numOfIndices = numOfIndices;
	GameController::GetGameController()->Graphicsmanager->ReserveBuffer(vbo);
	GameController::GetGameController()->Graphicsmanager->ReserveBuffer(ibo);

	cout <<"Size Of Vertex : "<<vertex[0].GetSize()<<endl ;
	DetermineOffset(&vertex[0]) ;
	vertexSize =vertex[0].GetSize() ;
	Mode = vertex[0].GetData();	
	cout <<Indices[2];
	GameController::GetGameController()->Graphicsmanager->FillBuffer(ibo, Indices, numOfIndices* sizeof (int), GPUDrawMode::STATIC, BufferType::ELEMENT_BUFFER);
	GameController::GetGameController()->Graphicsmanager->FillBuffer(vbo, vertex, numOfVerices*vertex[0].GetSize(), GPUDrawMode::STATIC, BufferType::ARRAY_BUFFER);
}
void GeometryIVBO::DetermineOffset(IVertex* v)
{
	for(int i = 0 ; i<10 ; ++i)
	{
		if(v->GetOffset(i) == -1)
			continue ;
		if(v->GetOffset(i) >= 0 )
			Offsets[i] = (void*)v->GetOffset(i);
		else 
			break ;
		if(v->GetOffset(i) == v->GetOffset(i+1))
			break ;
	}
}
void GeometryIVBO::Draw(Shapes shapes = Shapes::TRIANGLE)
{
	GameController::GetGameController()->Graphicsmanager->BindBuffer(BufferType::ARRAY_BUFFER ,vbo) ;

	GameController::GetGameController()->Graphicsmanager->IVBOModeDraw(ibo , numOfIndices , numOfVertices,vertexSize, Offsets , Mode, shapes) ;

	GameController::GetGameController()->Graphicsmanager->BindBuffer(BufferType::ARRAY_BUFFER,0) ;
}
void GeometryIVBO::Draw(int numOfShaderAttributes , int shaderAttributesIndices[] , Shapes shapes = Shapes::TRIANGLE)
{
	GameController::GetGameController()->Graphicsmanager->BindBuffer(BufferType::ARRAY_BUFFER,vbo) ;

	GameController::GetGameController()->Graphicsmanager->IVBOShaderModeDraw(ibo ,  numOfIndices , numOfShaderAttributes , shaderAttributesIndices , vertexSize , Offsets , Mode , shapes);

	GameController::GetGameController()->Graphicsmanager->BindBuffer(BufferType::ARRAY_BUFFER,0) ;
}
void GeometryIVBO::Draw(int numOfShaderAttributes , int shaderAttributesIndices[] )
{
	Draw(numOfShaderAttributes ,shaderAttributesIndices , Shapes::TRIANGLE);
}
void GeometryIVBO::Delete()
{
GameController::GetGameController()->Graphicsmanager->DeleteBuffer(1 , &ibo);
GameController::GetGameController()->Graphicsmanager->DeleteBuffer(1 , &vbo);
}

// does nothing but there's delete function
GeometryIVBO::~GeometryIVBO()
{

}