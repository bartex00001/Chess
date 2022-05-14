#include "Piece.h"
#include "Square.h"
Piece::Piece() {

}
Piece::Piece(sf::Texture& tx, unsigned short id, unsigned short tpe, unsigned short clr) {
	sprt.setTexture(tx);
	ID = id;
	type = tpe;
	color = clr;
}

bool Piece::move(Square* sqr, sf::UdpSocket* sckt, sf::IpAddress IP, unsigned short PORT,sf::Packet* pck) { //sqr to pole docelowe
	pck->clear();
	*pck << ID << type << color <<sqr->getPositionx() << sqr->getPositiony();
	sf::IpAddress a;// do zapchania
	unsigned short b;// do zapchania
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
		sqr->setPID(this->ID);
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
