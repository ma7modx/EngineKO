#include "ImmedientShapes.h"

class GeometryList : public Shape 
{
public :
	GeometryList(){ this->ID = -1 ;}
	void BeginList();
	void EndList();
	void Add(Shape* v);
	void Draw();
	void Transform(Matrix){}
	void Debug(){}
	~GeometryList();
private :
	int ID ; 
};