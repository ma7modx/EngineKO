
#pragma once
#include "Vector2.h"
#include "Mouse.h"
class Button
{
public:
	Button(	const char*imageIcon , Vector2 pos , float width , float height);
	bool IsClicked();
	void Draw();
	~Button();

private:
	Vector2 position ;
	float width , height ;
	unsigned int texID ;
	unsigned int LoadTexture(const char*filename);
};
