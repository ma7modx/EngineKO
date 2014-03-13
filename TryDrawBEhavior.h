#pragma once
#include "DrawBehavior.h"

class DrawTry : public DrawBehavior
{
public:
	DrawTry(){};

	void Draw()
	{
		std :: cout << "ZzZz" << std :: endl;
	}

	~DrawTry(){};

private:

};
