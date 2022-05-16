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
	bool Isclicked(sf::Vector2f coords);
	void setMark(bool isSelected);
	void bindPiece(Piece* piece);
	Piece* pce=nullptr;

private:
	
	sf::RectangleShape fld;
	float positionx=0;
	float positiony=0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

