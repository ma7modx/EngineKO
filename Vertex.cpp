#pragma once
#include "Vertex.h"
#include "GameController.h"
#include "GraphicsManager.h"
#include "GraphicsHelpers.h"

VertexData IVertex::GetData()
{
	return VertexData::VERTEX;
}
Vertex::Vertex(Vector3 Position )
	{
		this->Position = Position ;
	}
void Vertex::SetVertex(Vector3 Position)
{
	this->Position = Position ;
	GameController::GetGameController()->Graphicsmanager->SetVertexPosition(Position);
}
void Vertex::SetVertex()
{
	SetVertex(Position) ;
}
VertexData Vertex::GetData() 
	{return VertexData::VERTEX ;}
///
VertexData VertexNormal::GetData()
{return VertexData::VERTEX | VertexData::NORMAL; }

void VertexNormal::SetVertex(Vector3 Position,Vector3 normal)
{
	this->Normal = normal ;
	GameController::GetGameController()->Graphicsmanager->SetVertexNormal(normal);
	Vertex::SetVertex(Position) ;
}
void VertexNormal::SetVertex()
{
	SetVertex(Position,  Normal);
}
void VertexColor::SetVertex(Vector3 Position, MColor color)
{
	this->color = color ;
	GameController::GetGameController()->Graphicsmanager->SetVertexColor(color);
	Vertex::SetVertex(Position) ;
	
}
void VertexColor::SetVertex()
{
	SetVertex(Position,  color);
}
VertexData VertexColor::GetData() 
	{return VertexData::VERTEX | VertexData::COLOR;}
	
///
void VertexTexture::SetVertex(Vector3 Position, Vector2 TexCoord )
{
	this->TexCoord = TexCoord ;
	GameController::GetGameController()->Graphicsmanager->SetVertexTexCoord(TexCoord) ;
	Vertex::SetVertex(Position) ;
	
}
void VertexTexture::SetVertex()
{
	SetVertex(Position , TexCoord) ;
}
VertexData VertexTexture::GetData() 
	{return VertexData::VERTEX | VertexData::TEXTURE ;}
	
///
	void VertexColorNormal::SetVertex()
	{
		SetVertex(Position , color , Normal);
	}
	void VertexColorNormal::SetVertex(Vector3 Position, MColor color, Vector3 Normal)
	{
		this->Normal = Normal ;
		GameController::GetGameController()->Graphicsmanager->SetVertexNormal(Normal);
		VertexColor::SetVertex(Position , color);
	}
	
VertexData VertexColorNormal::GetData() 
	{return VertexData::VERTEX | VertexData::COLOR | VertexData::NORMAL ;}
///
void VertexTextureNormal::SetVertex(Vector3 Position, Vector2 TexCoord, Vector3 Normal)
{
	this->TexCoord = TexCoord ;
	GameController::GetGameController()->Graphicsmanager->SetVertexTexCoord(TexCoord);
	VertexNormal::SetVertex(Position , Normal);
	
}
void VertexTextureNormal::SetVertex()
{
	SetVertex(Position , TexCoord , Normal);
}
VertexData VertexTextureNormal::GetData() 
	{return VertexData::VERTEX | VertexData::TEXTURE | VertexData::NORMAL ;}
	