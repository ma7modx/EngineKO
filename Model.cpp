#pragma once
#include "Model.h"
#include "Texture.h"
#include <stdio.h>
#include <sstream>
// draw 

#include <fstream>
#include<iostream>
#include<GL\glew.h>
#include<assert.h>
#include<sstream>
#include<stack>
#include<GL\freeglut.h>
//
Model::Model(string ModelName)
{
	IsNormal = IsTexture = IsMaterial = false ; 
	ControlNormal = ControlTexture = ControlMaterial = true ;
	ID = -1 ;
}
Model::Model(bool Normal,bool Texture,bool Material)
{
	ControlNormal = Normal ;
	ControlTexture = Texture ;
	ControlMaterial = Material ;
	ID = -1 ;
}

int Model::Load(const char *filename)
{
	fstream in(filename);
	if (!in.is_open())
	{
		cout << "not opened \n"; 
		return -1;
	}
	char buf[256];
	while (!in.eof())// get the lines
	{
		in.getline(buf,256);
		coords.push_back(new string(buf));
	}

	// save values
	ReadAndSaveValues() ;
	//draw
	internDraw();
	//	int ModelID =  Draw(); //ModelID = glGenLists(1)

	return 0 ;//ModelID;
}

int Model::ReadAndSaveValues()
{
	int CurrentMaterial = 0 ;
	for (int i = 0; i < coords.size(); ++i)
	{
		if ( (*coords[i])[0] == '#')
			continue;
		else if ((*coords[i])[0] == 'v' && (*coords[i])[1] == ' ')//vertex
		{
			float x, y, z;
			sscanf_s(coords[i]->c_str(), "v %f %f %f", &x, &y, &z);
			vertex.push_back(new Vector3(x, y, z));
		}
		else if ((*coords[i])[0] == 'v' && (*coords[i])[1] == 'n' && ControlNormal)//normal
		{
			float x, y, z;
			sscanf_s(coords[i]->c_str(), "vn %f %f %f", &x, &y, &z);
			normals.push_back(new Vector3(x, y, z));
			IsNormal = true ;
		}
		else if ((*coords[i])[0] == 'f')//face
		{
			LoadFace(i, CurrentMaterial) ;
		}
		if(ControlMaterial)
		{
			if((*coords[i])[0] == 'u' && (*coords[i])[1] == 's' && (*coords[i])[2] == 'e') // search for material and make index equal to it 
			{
				char materialIndx[200] ;
				sscanf(coords[i]->c_str() , "usemtl %s" , materialIndx ) ;
				for(int j = 0 ; j < materials.size() ; ++j)
				{
					if(strcmp(materials[j]->name.c_str(), materialIndx) == 0 ) 
					{
						CurrentMaterial = j ;
						break ;
					}
				}
			}
			else if((*coords[i])[0] == 'm' && (*coords[i])[1] == 't' && (*coords[i])[2] == 'l' && (*coords[i])[3] == 'l') // load the materialfile
			{
				int Correct = LoadMaterial(i) ;
				if(Correct == -1) 
					return -1 ;
			}

		}
		if(ControlTexture)
			if((*coords[i])[0] == 'v' && (*coords[i])[0] == 't')
			{
				TexCoord* texloc = new TexCoord(0,0) ;
				scanf(coords[i]->c_str() , "vt %f %f" , &texloc->U , &texloc->V);
				texloc->V = 1- texloc->V ; // reverse it
				texcoordinates.push_back(texloc) ;
				IsTexture = true ;
				delete texloc ;
			}


			if(materials.size() == 0)
				IsMaterial = false ;
			else
				IsMaterial = true ;

	}
	return 0 ;
}

void Model::LoadFace(int i , int CurrentMaterial)
{
	int facenum, v[4] ;
	if (count(coords[i]->begin(), coords[i]->end(), ' ') == 4) //quad
	{
		if(coords[i]->find("//") != string::npos)
		{
			sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d",
				&v[0],  &facenum, &v[1], &facenum, &v[2], &facenum, &v[3], &facenum);

			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2], v[3],0,0,0,0,CurrentMaterial));
		}
		else if(coords[i]->find("/") != string::npos)
		{
			int T[4]; 
			sscanf(coords[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&v[0],&T[0], &facenum, &v[1],&T[1] , &facenum, &v[2],&T[2], &facenum, &v[3],&T[3], &facenum);

			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2], v[3],T[0],T[1],T[2],T[3],CurrentMaterial));
		}
		else
		{
			sscanf(coords[i]->c_str(), "f %d %d %d %d",
				&v[0], &v[1], &v[2] , &v[3]);
			faces.push_back(new MaterialFace(-1, v[0], v[1], v[2], v[3],0,0,0,0,CurrentMaterial));
		}

	}
	else //triangle
	{
		if(coords[i]->find("//") != string::npos)
		{
			sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d",
				&v[0], &facenum, &v[1], &facenum, &v[2], &facenum);
			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2],0,0,0 , CurrentMaterial));
		}
		else if(coords[i]->find("/") != string::npos)
		{
			int T[3]; 
			sscanf(coords[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&v[0],&T[0], &facenum, &v[1],&T[1] , &facenum, &v[2],&T[2], &facenum);

			faces.push_back(new MaterialFace(facenum, v[0], v[1], v[2],T[0],T[1],T[2],CurrentMaterial));
		}
		else
		{
			sscanf(coords[i]->c_str(), "f %d %d %d",
				&v[0], &v[1], &v[2] );
			faces.push_back(new MaterialFace(-1, v[0], v[1], v[2],0,0,0,CurrentMaterial));
		}
	}
}

int Model::LoadMaterial(int indx)
{
	char fileInput[200] ;
	sscanf(coords[indx]->c_str() , "mtllib %s" , &fileInput) ;
	ifstream materialf (fileInput);

	if(!materialf.is_open())
	{
		cout << "Can't load the model's material file" <<endl ;
		Clean();
		return -1 ;
	}	
	IsMaterial = true ;
	vector<string> materiaFile ;
	char line[200] ;

	while(!materialf.eof())
	{
		materialf.getline(line , 200) ;
		materiaFile.push_back(line);
		if(materiaFile[materiaFile.size()-1][0] =='\t')
			materiaFile[materiaFile.size()-1].erase(0,1);
	}

	Material *Data = new Material() ;
	char loadedMaterial[200] ;
	strcpy(loadedMaterial , "\0") ;
	bool isMaterialloc = false ;
	for(int i = 0 ; i < materiaFile.size() ;++i)
	{
		if(materiaFile[i][0] == '#')
			continue ;
		else if (materiaFile[i][0] == 'n' && materiaFile[i][1] == 'e' && materiaFile[i][2] == 'w')
		{
			PushMaterialData(isMaterialloc , loadedMaterial , *Data );
			isMaterialloc = false ;
			char dum[200] ;
			sscanf(materiaFile[i].c_str() , "newmtl %s" , dum ) ;
			Data->name = dum ;
		}
		else if (materiaFile[i][0] == 'N' && materiaFile[i][1] == 's')
		{
			sscanf(materiaFile[i].c_str() , "Ns %f" , &Data->ns);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'K' && materiaFile[i][1] == 'a')
		{
			sscanf(materiaFile[i].c_str() , "Ka %f %f %f" , &Data->AmbLight[0] , &Data->AmbLight[1] , &Data->AmbLight[2]);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'K' && materiaFile[i][1] == 'd')
		{
			sscanf(materiaFile[i].c_str() , "Kd %f %f %f" , &Data->DifLight[0] , &Data->DifLight[1] , &Data->DifLight[2]);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'K' && materiaFile[i][1] == 's')
		{
			sscanf(materiaFile[i].c_str() , "Ks %f %f %f" , &Data->SpecLight[0] , &Data->SpecLight[1] , &Data->SpecLight[2]);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'N' && materiaFile[i][1] == 'i')
		{
			sscanf(materiaFile[i].c_str() , "Ni %f" , &Data->ni);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'N' && materiaFile[i][1] == 'i')
		{
			sscanf(materiaFile[i].c_str() , "Ni %f" , &Data->ni);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'd' && materiaFile[i][1] == ' ')
		{
			sscanf(materiaFile[i].c_str() , "d %f" , &Data->alpha);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'o' && materiaFile[i][1] == 'l')
		{
			sscanf(materiaFile[i].c_str() , "illum %d" , &Data->illum);
			isMaterialloc = true ;
		}
		else if (materiaFile[i][0] == 'm' && materiaFile[i][1] == 'a')
		{
			sscanf(materiaFile[i].c_str() , "map_Kd %s" , &loadedMaterial);
			isMaterialloc = true ;
			Texture tex = Texture("tex1" , loadedMaterial ) ;
			//Data->TextureID = tex.GetTexID() ;
			//texture.push_back(Data->TextureID) ;
			//Engine::getEngine()->resourceManager->Delete("text1");
		}
	}
	PushMaterialData(isMaterialloc , loadedMaterial , *Data );
	delete Data ;
	return 0 ;
}

void Model::PushMaterialData(bool isMaterialloc, char loadedMaterial[200] , Material Data)
{
	if(isMaterialloc)
	{

		//if(strcmp(loadedMaterial , "\0")!= 0 )//no tex
		if(loadedMaterial[0] != '\0')
		{
			materials.push_back(new Material( Data.name , Data.alpha , Data.ns , Data.ni , Data.AmbLight , Data.DifLight , Data.SpecLight , Data.illum , Data.TextureID) ) ;
			strcpy(loadedMaterial , "\0") ;
		}
		else
			materials.push_back(new Material( Data.name , Data.alpha , Data.ns , Data.ni , Data.AmbLight , Data.DifLight , Data.SpecLight , Data.illum , -1) );

	}
}


int Model::internDraw()
{
	int ModelID = glGenLists(1);
	glNewList(ModelID, GL_COMPILE);//--
	int last = -1 ;
	for (int i = 0; i < faces.size(); ++i)
	{
		if(last != faces[i]->MaterialID && IsMaterial) 
		{
			float diff[4] = {materials[i]->DifLight[0],materials[i]->DifLight[1],materials[i]->DifLight[2],1} ;
			float amb[4] = {materials[i]->AmbLight[0] , materials[i]->AmbLight[1] ,materials[i]->AmbLight[2],1};
			float spec[4] = {materials[i]->SpecLight[0],materials[i]->SpecLight[1],materials[i]->SpecLight[2],1} ;
			glMaterialfv(GL_FRONT , GL_DIFFUSE, diff) ;
			glMaterialfv(GL_FRONT , GL_AMBIENT, amb) ;
			glMaterialfv(GL_FRONT , GL_SPECULAR, spec) ;
			glMaterialf(GL_FRONT , GL_SHININESS , materials[faces[i]->MaterialID]->ns);
			last = faces[i]->MaterialID ;
			if(materials[faces[i]->MaterialID]->TextureID == -1) // no tex
				glDisable(GL_TEXTURE_2D);
			else
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, materials[faces[i]->MaterialID]->TextureID); 
			}
		}
		if (faces[i]->Quad)
		{
			glBegin(GL_QUADS);//--

			if(ControlNormal)
				glNormal3f(normals[faces[i]->FaceNum - 1]->X, normals[faces[i]->FaceNum - 1]->Y, normals[faces[i]->FaceNum - 1]->Z);

			for (int j = 0; j < 4; ++j)// every face has 4 vertices 
				glVertex3f(vertex[faces[i]->VerticesID[j] - 1]->X, vertex[faces[i]->VerticesID[j] - 1]->Y, vertex[faces[i]->VerticesID[j] - 1]->Z);

			glEnd();//--//
		}
		else
		{
			glBegin(GL_TRIANGLES);//--

			if(ControlNormal)
				glNormal3f(normals[faces[i]->FaceNum - 1]->X, normals[faces[i]->FaceNum - 1]->Y, normals[faces[i]->FaceNum - 1]->Z);

			for (int j = 0; j < 3; ++j)// every face has 3 vertices 
				glVertex3f(vertex[faces[i]->VerticesID[j] - 1]->X, vertex[faces[i]->VerticesID[j] - 1]->Y, vertex[faces[i]->VerticesID[j] - 1]->Z);

			glEnd();//--//
		}
	}

	glEndList();//--//
	Clean() ;
	lists.push_back(ModelID) ;

	return ID = ModelID;
}

void Model::Clean()
{
	for (int i = 0; i < coords.size(); ++i)
		delete coords[i];
	for (int i = 0; i < vertex.size(); ++i)
		delete vertex[i];
	for (int i = 0; i < normals.size(); ++i)
		delete normals[i];
	for (int i = 0; i < faces.size(); ++i)
		delete faces[i];
	for (int i = 0; i < materials.size(); ++i)
		delete materials[i];
	for(int i = 0 ; i < texcoordinates.size() ; ++i)
		delete texcoordinates[i];

	coords.clear();
	vertex.clear();
	normals.clear();
	faces.clear();
	materials.clear();
	texcoordinates.clear();

}

void Model::Draw()
{
	glCallList(ID) ;
}

Model::~Model()
{
	for(vector<unsigned int>::iterator it = texture.begin() ; it!= texture.end() ; it++)
		glDeleteTextures(1,&(*it)) ;
	for(vector<unsigned int>::iterator it = lists.begin() ; it!= lists.end() ; it++)
		glDeleteLists(1,*it);
	Clean();
}