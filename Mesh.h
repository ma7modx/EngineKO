#pragma once 
#include "Resource.h"
#include <vector>
using namespace std; 

class GeometryList ;
class Vector3;
class Face;

class Mesh:public Resource
{
public :
	Mesh(string Name , const char * Filename) ;
	void Draw();
	
protected :
	GeometryList* Geometry ;
	
private :
	void MakeDrawList(vector<Vector3*>& vertex, vector<Vector3*>& normals , vector<Face*>& faces);

};