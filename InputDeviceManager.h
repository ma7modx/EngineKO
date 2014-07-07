#include "InputDevice.h"
#include <map>
using namespace std;



class InputExecution // make it inherit from behavior 
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
	void MakeActionList (int input , MoveList action)
	{

	}
private :
	InputExecution* inputExecution;
	InputDevice* device;
	map <int  , long long > ActionList ; // enum action , enum movelist
	// enum action made by user
	// hit1 , Q
};