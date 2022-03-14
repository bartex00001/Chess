#pragma once
#include <SFML\Graphics.hpp>
class Square
{
public:
	//Square() = delete;
	Square();
	Square(float posx, float posy);
	float getPositionx();
	float getPositiony();



private:
	float positionx;
	float positiony;
};

