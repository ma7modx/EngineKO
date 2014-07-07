#pragma once 
#include "Vector2.h"
#include <map>
using namespace std;
enum MoveList // input list
{
	UP = (1<<0), DOWN = (1<<1), RIGHT = (1<<2), LEFT = (1<<3),
	I = (1<<4), J = (1<<5), K = (1<<6), L = (1<<7),	Q = (1<<8) , E = (1<<9) , R = (1<<10) , U = (1<<11) , O = (1<<12) ,
	P8 = (1<<13), P5 = (1<<14), P6 = (1<<15), P4 = (1<<16)
} ;
class InputDevice
{
public :
	long long InputValue;
	virtual pair<long long , int> GetCommand()
	{
		//command = 0 ;
		// if(keycode) 
		// command |= pair (inputlist[keycode] , 0) ;
		//return command ;
		
	}
protected:
	map<int , pair < long long , int > > inputList ; // keycode , ( command (enum movelist) ,factor (added or mult) usually 0 ) 
	// w = up 
	// s = down
	// return pair<long long , int> command ; // command , factor (added or mult) usually 0
};

