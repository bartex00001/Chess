#include "Square.h"
#include "Piece.h"
Square::Square() {

}
Square::Square(float posx, float posy, sf::Color clr) {
	positionx = posx;
	positiony = posy;
	fld.setSize(sf::Vector2f(100, 100));
	fld.setPosition(posx, posy);
	fld.setFillColor(clr);
	fld.setOutlineColor(sf::Color::Red);
}
float Square::getPositionx() {
	return(positionx);
}

float Square::getPositiony() {
	return(positiony); 
}

bool Square::Isclicked(sf::Vector2f coords) {
	sf::FloatRect bounds = fld.getGlobalBounds();
	if (bounds.contains(coords))
		return true;

	else
		return false;
}


void Square::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(fld, states);
}

void Square::setMark(bool isSelected) {
	if (isSelected) 
		fld.setOutlineThickness(-4);

	else 
		fld.setOutlineThickness(0);
}

void Square::bindPiece(Piece* piece) {
	pce = piece;

}

