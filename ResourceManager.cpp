#include "ResourceManager.h"
#include <iostream>
using namespace std ;
 int ResourceManager::Register(string name , Resource* resource)
	{
		if(Resources.find(name) == Resources.end())
	{
		Resources[name] = resource; // should save orginal data not pointer on it
		return 0 ;
		}
		else 
		{
		cout << "This Resource name already exist : " << name << endl;
		return -1 ;
		}
	}

 Resource* ResourceManager::Get(string name)
	{
		if(Resources.find(name) != Resources.end())
			return Resources[name] ;
		cout << "This Resource name is not exist : " << name <<endl;
		return NULL ;
	}
 // Load Resource 
 int ResourceManager::Delete(string name)
	{
		if(Resources.find(name) != Resources.end())
		{
			Resources.erase(name) ;
			return 0 ;
		}
		else 
		{
				cout << "This Resource name is not exist : " << name <<endl;
			return -1 ;
		}
	}
	