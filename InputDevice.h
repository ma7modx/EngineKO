#include "Vector2.h"
#include <map>
using namespace std;
class InputDevice
{
public :
	long long InputValue;
	virtual pair<long long , int> GetCommand()
	{
		return command ;
		// if(keycode) 
		// command = pair (inputlist[keycode] , 0) ;
	}
protected:
	map<int , long long> inputList ; // keycode , command (enum movelist)
	pair<long long , int> command ; // command , factor usually 0
};

