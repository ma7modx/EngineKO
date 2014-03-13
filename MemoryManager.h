typedef unsigned char byte;
#include <vector>
#include <string>
#include <iostream>
using namespace std ;

class MemorySector { 
public :
	string name ; long long size ; byte* offset ; byte*used ;
	MemorySector(string name , long long size , byte* offset) 
	{
		this->name = name ; this->size = size ; this->offset = offset ; used = offset ;
	}
};

class MemoryManager
{
public :
	MemoryManager(long long Size)
	{
		this->Size = Size ;
		Memory = new byte [Size] ;
		LstOffset = Memory ;
	}
	void AddSector (string name , long long Size) 
	{
		Sectors.push_back(MemorySector(name , Size , LstOffset)) ;
		LstOffset += Size ;
	}
	void DeleteSector(string name)
	{
		vector <MemorySector>::iterator it = find(name) ;

		long long prvSize = it->size ;			
		byte* deletedoffset = it->offset ;

		it = Sectors.erase(it) ;

		int z = 2 ;
		//it--;
		for( ; it != Sectors.end() ; it++)
		{
			it->offset -= prvSize ;
			prvSize = it->size ;
		}

		LstOffset -= prvSize ;
	}
	byte* RequestData(string sectorName , int ItemsizeInByte , int numOfdata = 1)
	{
		vector <MemorySector>::iterator it = find(sectorName) ;

		byte* tmp = it->used;
		it->used += ItemsizeInByte*numOfdata ; 
		return tmp ;
	}
	template <typename T>
	T* GetData(string sectorName , int offset , int ItemsizeInByte , int Many )
	{
		sizeof (T) ;
		vector <MemorySector>::iterator it = find(sectorName) ;
		T *Data = new T[Many] ;	/// fuck fuck fuck -_-
		byte* Offset = it->offset + offset ;
		int count = 0 ;
		for(byte* i = Offset ;count < Many;  i += ItemsizeInByte , count++)
		{
			Data[count] = offset[i];
		}
		return Data ;
	}
	void DeleteData(string sectorName , int sizeInBytesFrmLst) 
	{
		vector <MemorySector>::iterator it = find(sectorName) ;
		it->used -= sizeInBytesFrmLst ;
	}
	~MemoryManager()
	{
		delete [] Memory ;
	}
private :
	long long Size ;
	byte *Memory ;
	byte *LstOffset ;
	vector <MemorySector> Sectors ;

	vector <MemorySector>::iterator find (string name)
	{
		for(vector <MemorySector>::iterator it = Sectors.begin() ; it != Sectors.end() ; it++)
		{
			if(it->name == name)
				return it ;
		}
	}
};