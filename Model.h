#pragma once
#include <vector>
#include <string>
#include "Material.h"
#include "ModelHelpers.h"
#include "MMath.h"

using namespace std ;
class Model 
{
public:
	Model()  {}
	Model(string ModelName);
	Model(bool IsNormal,bool IsTexture,bool IsMaterial);

	int Load(const char* Filename);
	void Draw();
	~Model();

private:
	unsigned int LoadTexture(const char* Filename);
	int ReadAndSaveValues();
	int LoadMaterial(int indx);
	void PushMaterialData(bool isMaterialloc, char loadedMaterial[200] , Material Data);
	void LoadFace(int indx, int CurrentMaterial);
	int internDraw() ;
	void Clean();

	vector<string*> coords; // text file lines
	vector<Vector3*> vertex, normals;
	vector<MaterialFace*> faces;
	vector<Material*> materials ;
	vector<TexCoord*> texcoordinates ;
	vector<unsigned int> texture , lists;
	bool IsNormal, IsTexture, IsMaterial;
	bool ControlNormal , ControlTexture , ControlMaterial ; 
	int ID ;

};