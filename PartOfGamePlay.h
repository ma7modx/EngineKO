#pragma once 
#include <vector>
using namespace std ;
class MemoryManager;
class PartOfGamePlay 
{
public :
	
	PartOfGamePlay();
	virtual void Initialize()=0 ;
//	virtual void Load()= 0 ;
	virtual void Update()=0 ;// no neeed later .. phys , AI
//	virtual void Unload() = 0 ;
	virtual void Draw()=0 ;// no need later .. render manager
	virtual bool Finished()=0 ;
	bool Initialized;
	MemoryManager* GetMemory(){return Memory ;}
private :
	MemoryManager* Memory ; // points on gamecontroller memory

};