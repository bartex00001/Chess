#include "Piece.h"

Piece::Piece(sf::Texture& tx, float posx, float posy, unsigned short id) {
	sprt.setTexture(tx);
	positionx = posx;
	positiony = posy;
	ID = id;
}

bool Piece::move(Square* sqr, sf::UdpSocket* sckt, sf::IpAddress IP, unsigned short PORT,sf::Packet* pck) {
	pck->clear();
	*pck << ID << sqr->getPositionx() << sqr->getPositiony();
	sf::IpAddress a;
	unsigned short b;
	bool moveValuability;
	if (sckt->send(*pck, IP, PORT) != sf::Socket::Done) {
		std::cout << "Failed to send a move to the server!" << std::endl;
		exit(5);
	}
	pck->clear();
	if(sckt->receive(*pck,a,b) != sf::Socket::Done) {
		std::cout << "Failed to receive a move from the server!" << std::endl;
		exit(5);
	}
	*pck >> moveValuability;
	pck->clear();
	if (moveValuability == true) {
		this->SetPosition(sqr);
		return(true);
	}
	return(false);
}

void Piece::SetPosition(Square* sqr) {
	this->sprt.setPosition(sqr->getPositionx(), sqr->getPositiony());
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(sprt, states);
}
