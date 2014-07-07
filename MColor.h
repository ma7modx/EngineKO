#pragma once
class MColor
{
public:
	float R, G, B, A;

	MColor(){}
	
	MColor(float R, float G, float B)
	{
		if(!(R > 1 || G > 1 || B > 1))// float
		{this->R = R; this->G = G; this->B = B;this->A =1;}
		else
		{this->R = (float)R/255; this->G = (float)G/255; this->B = (float)B/255; this->A =1;}
	}
	
	MColor(float R, float G, float B, float A)
	{
		if(!(R > 1 || G > 1 || B > 1 || A > 1))// float
		{this->R = R; this->G = G; this->B = B;this->A =A;}
		else
		{this->R = (float)R/255; this->G = (float)G/255; this->B = (float)B/255; this->A =A;}
	}

	static MColor Black;
	static MColor White;
	static MColor Red;
	static MColor Green;
	static MColor Blue;
	static MColor Gray;
	static MColor Yellow;
};