
#include <map>
#include <set>
#include "InputDevice.h"
using namespace std;
class KeyboardInput : public InputDevice
{
public:

	void GetStates();

private :
	int pressedKeys;
	//static bool*  keyStates;
	static set<int> SetOfPressedKeys;
	static void keyPressed(unsigned char key, int x, int y);
	static void keyUp(unsigned char key, int x, int y);
	unsigned char c(char letter); // convert 
};

