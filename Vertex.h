#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "MColor.h"
class VertexData; 

class IVertex
{
public :
	Vector3 Position;
	virtual short GetSize() {return 0 ;};
	virtual short GetOffset(int index) {return 0 ;} //offset of data
	// 0 position
	// 1 color
	// 2 normal
	// 3 texture
	virtual VertexData GetData() ;
	virtual void SetVertex(){}; 
};

class Vertex : public IVertex
{
public:
	Vertex(){}
	Vertex(Vector3 Position );

	void SetVertex();
	void SetVertex(Vector3 Position);
	short GetSize() { return sizeof(Vector3) + sizeof(float) ; }
	short GetOffset(int index) 
	{ return sizeof (float) ; }
	VertexData GetData() ;
	
};

class VertexNormal : public Vertex
{
public:
	Vector3 Normal;

	VertexNormal(){}
	VertexNormal(Vector3 Position, Vector3 Normal) :Vertex(Position)
	{
		this->Normal = Normal;
	}
	
	void SetVertex();
	void SetVertex(Vector3 Position,Vector3 normal);
	short GetSize() { return sizeof(Vector3)+sizeof(Vector3)+sizeof(float) ; }
	short GetOffset(int index) 
	{ 
		if(index == 0)
			return sizeof (float) ; 
		else
			return 4+sizeof(Vector3);
	} 
	VertexData GetData() ;
};


class VertexColor : public Vertex
{
public:
	MColor color;

	VertexColor(){}
	VertexColor(Vector3 Position, MColor color) :Vertex(Position)
	{
		this->color = color;
	}
	
	void SetVertex();
	void SetVertex(Vector3 Position, MColor color);
	short GetSize() { return sizeof(Vector3)+sizeof(MColor)+sizeof(float) ; }
	short GetOffset(int index) 
	{ 
		if(index == 0)
			return sizeof (float) ; 
		else
			return 4+sizeof(Vector3);
	} 
	VertexData GetData() ;
};

class VertexTexture : public Vertex
{
public: 
	Vector2 TexCoord;
public :
	VertexTexture() {}
	VertexTexture(Vector3 Position, Vector2 TexCoord ) : Vertex(Position)
	{
		this->TexCoord = TexCoord;
	}

	void SetVertex(Vector3 Position, Vector2 TexCoord );
	void SetVertex();
	short GetSize() { return sizeof(Vector3)+sizeof(Vector2)+sizeof(float) ; } 
	short GetOffset(int index)
	{
		if(index == 0)
			return 4 ;
		if(index == 1)
			return -1 ;
		if(index == 2)
			return -1 ;
		else
			return 4+sizeof(Vector3) ;
	}
	VertexData GetData() ;
	
};

class VertexColorNormal : public VertexColor
{
public:
	Vector3 Normal;
public:
	VertexColorNormal(){}
	VertexColorNormal(Vector3 Position, MColor color, Vector3 Normal) : VertexColor(Position, color)
	{
		this->Normal = Normal;
		this->color = color;
	}
	
	void SetVertex();
	void SetVertex(Vector3 Position, MColor color, Vector3 Normal);
	short GetSize() { return sizeof(Vector3)+sizeof(MColor)+sizeof(Vector3)+sizeof(float) ; } 
	short GetOffset(int index) 
	{ 
		if(index == 0)
		return 4 ;
		if(index == 1)
			return 4+sizeof(Vector3) ;
		else
			return 4+sizeof(Vector3)+ sizeof(MColor) ;
	}
	VertexData GetData() ;
	
};

// has been edited from public VertexTexture to this in 4-11-2014
class VertexTextureNormal : public VertexNormal// : public VertexTexture
{
public :
	Vector2 TexCoord;
public:
	VertexTextureNormal() {}
	VertexTextureNormal(Vector3 Position, Vector2 TexCoord, Vector3 Normal) : VertexNormal(Position , Normal)
	{
		this->Normal = Normal;
		this->TexCoord = TexCoord;
	}

	void SetVertex(Vector3 Position, Vector2 TexCoord, Vector3 Normal);
	void SetVertex();
	short GetSize() {return sizeof(Vector3)+sizeof(Vector2)+sizeof(Vector3)+sizeof(float) ; } 
	short GetOffset(int index) 
	{ 
		if(index == 0)
		return 4 ;
		if(index == 1)
			return -1 ;
		if(index == 2)
			return 4+sizeof(Vector3) ;
		else
			return 4+sizeof(Vector3)+ sizeof(Vector3) ;
	}
	VertexData GetData() ;
	
};