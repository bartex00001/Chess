#pragma once
#include <SFML\Graphics.hpp>
#include "Piece.h"
class Square : public sf::Drawable
{
public:
	
	Square();
	Square(float posx, float posy, sf::Color clr);
	float getPositionx();
	float getPositiony();
	void setPID(unsigned short x);
	unsigned short getPID();
	bool Isclicked(sf::Vector2f coords);
	void setMark(bool isSelected);

	void bindPiece(Piece* piece);

private:
	Piece *pce;
	sf::RectangleShape fld;
	unsigned short PID=0;
	float positionx=0;
	float positiony=0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

