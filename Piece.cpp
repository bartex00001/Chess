#include "Piece.h"

Piece::Piece() {

}
Piece::Piece(sf::Texture& tx, unsigned short id, unsigned short tpe, unsigned short clr) {
	sprt.setTexture(tx);
	ID = id;
	type = tpe;
	color = clr;
}

void Piece::SetPosition(float x, float y) {
	sprt.setPosition(x, y); //tu  wypierdala
}


void Piece::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(sprt, states);
}

unsigned short Piece::getID() {
	return(ID);
}

unsigned short Piece::getType() {
	return(type);
}

unsigned short Piece::getColor() {
	return(color);
}

void Piece::setID(unsigned short id) {
	ID = id;
}

void Piece::setType(unsigned short tpe) {
	type = tpe;
}

void Piece::setColor(unsigned short clr) {
	color = clr;
}

void Piece::changeTexture(sf::Texture &tx) {
	this->sprt.setTexture(tx);
}
