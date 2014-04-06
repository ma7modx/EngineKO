#pragma once 
#include "Mesh.h"
#include "GeometryList.h"
#include "ObjLoader.h"
#include "ModelHelpers.h"
#include "Vector3.h"
#include "Material.h"

Mesh::Mesh(string Name , const char * Filename)//:Resource(Name , this)
{
	//Geometry = new GeometryList();
	vector<string*> coords; // text file lines
	vector<Vector3*> vertex, normals;
	vector<Face*> faces;
	vector<Material*> materials ;
	ObjLoader::ReadFileLines(Filename , coords);
	ObjLoader::ReadVertices(coords , vertex);
	ObjLoader::ReadNormals(coords , normals);
	ObjLoader::ReadFaces(coords , faces) ;
	
	string MaterialName = ObjLoader::ReadMaterialFileName(coords) ;
	
	if(MaterialName.size() != 0)
		materials = Material::LoadMaterial(MaterialName) ;

	MakeDrawList( vertex,  normals , faces);
	
	ObjLoader::Delete(coords ,vertex,  normals ,  faces);
	
	// delete material
	for(int i = 0 ; i < (int)materials.size() ; ++i)
		delete materials[i];
	materials.clear();
}
int ID = -1 ;
void Mesh::Draw()
{
	glCallList(ID);
	//Geometry->Draw();
}

void Mesh::MakeDrawList(vector<Vector3*>& vertex, vector<Vector3*>& normals , vector<Face*>& faces)
{

	Quad *quad = new Quad();
	Triangle *triangle = new Triangle();
	VertexNormal *v[4] = {new VertexNormal(Vector3(0),Vector3(0)) ,new VertexNormal(Vector3(0),Vector3(0)),new VertexNormal(Vector3(0),Vector3(0)),new VertexNormal(Vector3(0),Vector3(0))} ;
	
	ID = glGenLists(1);
	glNewList(ID, GL_COMPILE);//--

	for (int i = 0; i < (int)faces.size(); ++i)
	{
		if (faces[i]->Quad)
		{
			glBegin(GL_QUADS);
			if(normals.size()!=0)
			{
			glNormal3f(normals[faces[i]->FaceNum - 1]->X, normals[faces[i]->FaceNum - 1]->Y, normals[faces[i]->FaceNum - 1]->Z);
			*v[1] = *v[2] = *v[3] = *v[0] ; // same normal
			}
			for (int j = 0; j < 4; ++j)// every face has 4 vertices 
			{
			glVertex3f(vertex[faces[i]->VerticesID[j] - 1]->X, vertex[faces[i]->VerticesID[j] - 1]->Y, vertex[faces[i]->VerticesID[j] - 1]->Z);
			//	Vector3 vec = (*vertex[faces[i]->VerticesID[j] - 1]);
			//	(*v[j]).Position = vec;
			}
			glEnd();//--//
			Vector3 ss = v[0]->Position ;
			ss = v[1]->Position ;
			ss = v[2]->Position ;
			
			quad->vertices[0] = v[0] ;
			quad->vertices[1] = v[1] ;
			quad->vertices[2] = v[2] ;
			quad->vertices[3] = v[3] ;
			Geometry->Add( quad );
		}
		else
		{
			if(normals.size()!=0)
			{
			v[0]->Normal = *normals[faces[1]->FaceNum - 1];
			*v[1] = *v[2] = *v[0] ;
			}
			for (int j = 0; j < 3; ++j)// every face has 3 vertices 
				v[j]->Position = *vertex[faces[i]->VerticesID[j] - 1];

			triangle->vertices[0] = v[0] ;
			triangle->vertices[1] = v[1] ;
			triangle->vertices[2] = v[2] ;
			Geometry->Add( triangle );
		}
	}

	glEndList();
	
	delete quad ;
	delete triangle ;
	
}

void Mesh::Delete()
{
	glDeleteLists(ID , 1);
}

Mesh::~Mesh()
{

}