#include "InputDevice.h"

long long NormalInputDevice::K = 1;
long long NormalInputDevice::J = 2;
long long NormalInputDevice::L = 4;
long long NormalInputDevice::I = 8;
long long NormalInputDevice::Up = 16;
long long NormalInputDevice::Right = 32;
long long NormalInputDevice::Left = 64;
long long NormalInputDevice::Down = 128;


Vector2 StickInputDevice::StickUp = Vector2(0,1);
Vector2 StickInputDevice::StickRight = Vector2(1,0);
Vector2 StickInputDevice::StickDown = Vector2(0,-1);
Vector2 StickInputDevice::StickLeft = Vector2(-1,0);