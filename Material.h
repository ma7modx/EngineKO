#pragma once
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include"Resource.h"
#include"Vector3.h"
#include "Texture.h"
using namespace std ;

class Material:public Resource{
public:
	string name;
	float alpha, ns, ni; // alpha = d , 
	Vector3 AmbLight, DifLight, SpecLight;// light
	int illum;
	int TextureID;
	Material():Resource(1)
	{name = "" ; alpha = ns = ni = -1 ; AmbLight = DifLight = SpecLight = Vector3::ZERO ; illum = TextureID = -1 ;}


	Material(string name, float alpha, float ns, float ni, Vector3 AmbLight , Vector3 DifLight , Vector3 SpecLight , int illum , int TextureID):Resource(1) 
	{
		Constructor( name,  alpha,  ns,  ni,  AmbLight ,  DifLight ,  SpecLight ,  illum ,  TextureID);
	}
	Material(string savedname , string name, float alpha, float ns, float ni, Vector3 AmbLight , Vector3 DifLight , Vector3 SpecLight , int illum , int TextureID):Resource(savedname , this) 
	{
		Constructor( name,  alpha,  ns,  ni,  AmbLight ,  DifLight ,  SpecLight ,  illum ,  TextureID);
	}
	void Constructor(string name, float alpha, float ns, float ni, Vector3 AmbLight , Vector3 DifLight , Vector3 SpecLight , int illum , int TextureID)
	{
		this->name = name;
		this->alpha = alpha;
		this->ns = ns;
		this->ni = ni;
		for (int i = 0; i < 2; ++i)
		{
			this->AmbLight[i] = AmbLight[i];
			this->DifLight[i] = DifLight[i];
			this->SpecLight[i] = SpecLight[i];
		}
		this->illum = illum;
		this->TextureID = TextureID;
	}
	// shader
	// void use
	// texture
	static vector<Material*> LoadMaterial(string FileName)
	{
		ifstream materialf (FileName);
		vector<Material*> materials;
		if(!materialf.is_open())
		{
			cout << "Can't load material file" <<endl ;
			//	Clean();
			return materials ;
		}	

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
		for(int i = 0 ; i < (int)materiaFile.size() ;++i)
		{
			if(materiaFile[i][0] == '#')
				continue ;
			else if (materiaFile[i][0] == 'n' && materiaFile[i][1] == 'e' && materiaFile[i][2] == 'w')
			{
				PushMaterialData(isMaterialloc , loadedMaterial , *Data , materials );
				isMaterialloc = false ;
				char dum[200] ;
				sscanf_s(materiaFile[i].c_str() , "newmtl %s" , dum ) ;
				Data->name = dum ;
			}
			else if (materiaFile[i][0] == 'N' && materiaFile[i][1] == 's')
			{
				sscanf_s(materiaFile[i].c_str() , "Ns %f" , &Data->ns);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'K' && materiaFile[i][1] == 'a')
			{
				sscanf_s(materiaFile[i].c_str() , "Ka %f %f %f" , &Data->AmbLight[0] , &Data->AmbLight[1] , &Data->AmbLight[2]);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'K' && materiaFile[i][1] == 'd')
			{
				sscanf_s(materiaFile[i].c_str() , "Kd %f %f %f" , &Data->DifLight[0] , &Data->DifLight[1] , &Data->DifLight[2]);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'K' && materiaFile[i][1] == 's')
			{
				sscanf_s(materiaFile[i].c_str() , "Ks %f %f %f" , &Data->SpecLight[0] , &Data->SpecLight[1] , &Data->SpecLight[2]);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'N' && materiaFile[i][1] == 'i')
			{
				sscanf_s(materiaFile[i].c_str() , "Ni %f" , &Data->ni);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'd' && materiaFile[i][1] == ' ')
			{
				sscanf_s(materiaFile[i].c_str() , "d %f" , &Data->alpha);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'i' && materiaFile[i][1] == 'l')
			{
				sscanf_s(materiaFile[i].c_str() , "illum %d" , &Data->illum);
				isMaterialloc = true ;
			}
			else if (materiaFile[i][0] == 'm' && materiaFile[i][1] == 'a')
			{
				sscanf_s(materiaFile[i].c_str() , "map_Kd %s" , &loadedMaterial);
				isMaterialloc = true ;
//					Texture tex = Texture("tex1" , loadedMaterial ) ;
	//				Data->TextureID = tex.GetID();
					///	texture.push_back(Data->TextureID) ; // should be handled <<--------------
						
			}
		}
		PushMaterialData(isMaterialloc , loadedMaterial , *Data , materials );
		delete Data ;
		return materials ;
	}
	static void PushMaterialData(bool isMaterialloc ,char loadedMaterial[200] , Material Data , vector<Material*>& materials)
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

	~Material()
	{}
	//Shader getShader();
	//void setShader(Shader shader);
private :
	//Shader* shader;
};
