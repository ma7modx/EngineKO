#pragma once
#include <string>
using namespace std;

class Face
{
public :
	int FaceNum;
	bool Quad;
	int VerticesID[4];

	Face(int facenum, int v1, int v2, int v3): FaceNum(facenum)
	{
		Quad = false;
		VerticesID[0] = v1;
		VerticesID[1] = v2;
		VerticesID[2] = v3;
	}

	Face(int facenum, int v1, int v2, int v3 , int v4): FaceNum(facenum)
	{
		Quad = true;
		VerticesID[0] = v1;
		VerticesID[1] = v2;
		VerticesID[2] = v3;
		VerticesID[3] = v4;
	}

};

class MaterialFace : public Face
{
public :
	int TexcoordID[4];
	int MaterialID;

	MaterialFace(int facenum, int v1, int v2, int v3, int Texcoord1, int Texcoord2, int Texcoord3 ,  int MaterialID) : Face(facenum , v1 , v2 , v3)
	{
		TexcoordID[0] = Texcoord1;
		TexcoordID[1] = Texcoord2;
		TexcoordID[2] = Texcoord3;
		this->MaterialID = MaterialID;
	}

	MaterialFace(int facenum, int v1, int v2, int v3, int v4 , int Texcoord1, int Texcoord2, int Texcoord3, int Texcoord4, int MaterialID) : Face(facenum, v1, v2, v3)
	{
		TexcoordID[0] = Texcoord1;
		TexcoordID[1] = Texcoord2;
		TexcoordID[2] = Texcoord3;
		TexcoordID[3] = Texcoord4;
		this->MaterialID = MaterialID;
	}

};

class TexCoord
{
public :
	float U, V;
	TexCoord(float U, float V)
	{	
		this->U = U;
		this->V = V;
	}
};