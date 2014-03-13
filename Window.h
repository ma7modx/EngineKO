#pragma once 
#include "MColor.h"
#include "Vector2.h"
#include <string>
using namespace std ;
class Window 
{
public :
	string Title;
	MColor color ;
	int WindoWidth , Windowheight ;
	Vector2 Windowposition ;
	int FramesPerSec;
	double Near , Far , Angle ;
	Window()
	{
		Title = "" ;
		color = MColor::Black ;
		WindoWidth = Windowheight = 400 ;
		FramesPerSec = 10 ;
		Near = 0.00001;
		Far = 100000 ;
		Angle = 45 ;
	}
	Window(string Title,MColor color ,int WindoWidth , int Windowheight ,Vector2 Windowposition ,int FramesPerSec , double Near , double Far , double Angle )
	{
		this->Title = Title ;
		this->color = color ;
		this->WindoWidth = WindoWidth ;
		this->Windowheight = Windowheight ;
		this->Windowposition = Windowposition ;
		this->FramesPerSec = FramesPerSec ;
		this->Near = Near ;
		this->Far = Far ;
		this->Angle = Angle;
	}
};