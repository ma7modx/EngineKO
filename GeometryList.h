#include "ImmedientShapes.h"

class GeometryList : public Shape 
{
public :
	GeometryList(){ ID = 0 ;}
	void BeginList();
	void EndList();
	void Add(Shape* v);
	void Draw();
	void Transform(Matrix){}
	void Debug(){}
private :
	int ID ; 
};