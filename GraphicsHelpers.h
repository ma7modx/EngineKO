#pragma once
class VertexData 
{
public :
	int Mode ;
	VertexData() {}
	VertexData(int Mode) { this->Mode = Mode ; } 
	static int VERTEX  , COLOR , NORMAL , TEXTURE ;
} ;
class VertexAttributes
{
public :
	VertexAttributes(int Size)
	{
		for(int i = 0 ; i < Size ; ++i)
			arr[i] = -1 ;
	}
	void AddAttribute(int value , VertexData Data)
	{
		if(Data.Mode == VertexData::VERTEX) // log base 2
			arr[0] = value ;
		else if(Data.Mode == VertexData::COLOR)
			arr[1] = value ;
		else if(Data.Mode == VertexData::NORMAL)
			arr[2] = value ;
		else if(Data.Mode == VertexData::TEXTURE)
			arr[3] = value ;
	}
	int *GetAttributes()
	{
		return arr ;
	}
private :
	int arr[] ;
};
enum GPUDrawMode { STATIC  , DYNAMIC  , STREAM } ;
enum Shapes { TRIANGLE , LINE , QUAD } ;
enum BufferType { ARRAY_BUFFER , ELEMENT_BUFFER };
