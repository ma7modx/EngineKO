#pragma once
#include "IBehavior.h"

class UpdateBehavior : public IBehavior
{
public:
	virtual void Update() {}
private:
	void ExecuteBehavior()
	{
		Update();
	}
};