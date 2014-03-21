#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "stb_image.h"
#include "Mouse.h"
#include <map>
#include <string>
using namespace std;
class Menu ;
class UIManager
{
public:
	void Update(){Mouse::Update();}
	void Show();
	void AddMenu(string ,Menu*);
	void DeleteMenu(string);
	void ActiveMenu(string);
	void DeactiveMenu(string);
	pair<string , int> GetAction() ;
protected:
private:
	map<string ,pair< Menu* , bool > > menus;
};