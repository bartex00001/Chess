#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Square.h"
class Piece : public sf::Drawable
{
public:
	
	Piece(sf::Texture &tx, float posx, float posy, unsigned short id);
	bool move(Square* sqr, sf::UdpSocket* sckt, sf::IpAddress IP, unsigned short PORT, sf::Packet* pck);
	void SetPosition(Square* sqr);

	
	unsigned short ID;
private:
	//sf::Packet pack{};
	sf::Sprite sprt;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	float positionx;
	float positiony;


};

