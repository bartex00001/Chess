#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
//typy: 0pawn 1bishop 2knight 3rook 4queen 5king
//kolory: 0bia³y 1czarny
//nie uzywam enumów ¿eby nie jebaæ siê z overloadami << do pakietów
class Piece : public sf::Drawable
{
public:
	Piece();
	Piece(sf::Texture &tx, unsigned short id, unsigned short tpe, unsigned short clr);
	void SetPosition(float x,float y);
	unsigned short getID();
	unsigned short getType();
	unsigned short getColor();
	void setID(unsigned short id);
	void setType(unsigned short tpe);
	void setColor(unsigned short clr); 
	void changeTexture(sf::Texture &tx);
	
private:
	sf::Sprite sprt;
	unsigned short ID;
	unsigned short type;
	unsigned short color;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;



};

