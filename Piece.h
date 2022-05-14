#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Square.h"
//typy: 0pawn 1bishop 2knight 3rook 4queen
//kolory: 0bia³y 1czarny
//nie uzywam enumów ¿eby nie jebaæ siê z overloadami << do pakietów
class Piece : public sf::Drawable
{
public:
	Piece();
	Piece(sf::Texture &tx, unsigned short id, unsigned short tpe, unsigned short clr);
	bool move(Square* sqr, sf::UdpSocket* sckt, sf::IpAddress IP, unsigned short PORT, sf::Packet* pck);
	void SetPosition(Square* sqr);
	unsigned short getID();
	unsigned short getType();
	unsigned short getColor();
	void setID(unsigned short id);
	void setType(unsigned short tpe);
	void setColor(unsigned short clr);
	
private:
	unsigned short ID;
	unsigned short type;
	unsigned short color;
	sf::Sprite sprt;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;



};

