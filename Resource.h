#pragma once
#include <string>
using namespace std ;
class Resource 
{
public :
	string name ;
	Resource(int NotRegistered)
	{name = "" ;}
	Resource(string name , Resource* Data) ;
	~Resource();
};