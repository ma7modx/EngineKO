#pragma once
#include "IBehavior.h"
#include <iostream>
class DrawBehavior : public IBehavior
{
public:
	virtual void Draw() {std :: cout << "success\n" ;}
private:
	void ExecuteBehavior()
	{
		Draw();
	}
};