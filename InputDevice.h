#include "Vector2.h"

class InputDevice
{
public :
	long long InputValue;
	virtual void GetStates(){}
};

class NormalInputDevice : public InputDevice
{
public :
	
	virtual int GetButtonStates(){}
	static long long I , J , K , L , Up , Right , Down , Left ;
	long long GetButton(){ return 0; } // comment it
};
class StickInputDevice : public NormalInputDevice
{
public :
	Vector2 thumbStick ;
	virtual Vector2 GetThumbStickState(){}
	static Vector2 StickUp , StickDown , StickRight, StickLeft;
};
