#include "InputDevice.h"
#include <map>
using namespace std;

enum MoveList
{
	UP = (1<<0), DOWN = (1<<1), RIGHT = (1<<2), LEFT = (1<<3),
	I = (1<<4), J = (1<<5), K = (1<<6), L = (1<<7),	Q = (1<<8) , E = (1<<9) , R = (1<<10) , U = (1<<11) , O = (1<<12) ,
	P8 = (1<<13), P5 = (1<<14), P6 = (1<<15), P4 = (1<<16)
} ;

class InputExecution
{
public:
	void Execute();
};

class InputDeviceManager
{
public :
	InputDeviceManager(InputDevice* device , InputExecution* inputExecution)
	{
		this->device = device;
		this->inputExecution = inputExecution ;
	}
	void ExecuteInput() 
	{
		inputExecution->Execute() ;
	}

private :
	InputExecution* inputExecution;
	InputDevice* device;
	map <int  , MoveList> InputList ;

};