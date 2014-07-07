#include "Vector4.h"
#include "Matrix.h"

Vector4 Vector4::operator* (Matrix m)
{
	Vector4 v ;
	for(int i = 0 ; i < 4 ; ++i)
		v.X += m(0,i);
	for(int i = 0 ; i < 4 ; ++i)
		v.Y += m(1,i);
	for(int i = 0 ; i < 4 ; ++i)
		v.Z += m(2,i);
	for(int i = 0 ; i < 4 ; ++i)
		v.W += m(3,i);
	return v;
}